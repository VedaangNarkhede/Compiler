%{
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#include <string>

#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Constants.h"
#include "llvm/Support/raw_ostream.h"

using namespace std;

extern int yylex();
void yyerror(const char *s);

extern llvm::LLVMContext context;
extern llvm::Module *module;
extern llvm::IRBuilder<> *builder;
extern std::map<std::string, llvm::Value*> symbolTable;
std::map<std::string, std::pair<llvm::StructType*, std::map<std::string, unsigned>>> structTypes;

struct FieldInfo
{
  llvm::Type* type;
  std::string name;
  llvm::Value* initValue;
};

std::map<std::string, std::map<std::string, llvm::Value*>> structInitValues;
std::map<std::string, bool> stringVariables;
int temp = 0;
%}

%{
#include "llvm/IR/Type.h"
#include "llvm/IR/Value.h"
#include "llvm/IR/Constants.h"
#include <vector>
static std::vector<llvm::BasicBlock*> BreakTargets;
llvm::SwitchInst* yy_switch_inst;
llvm::BasicBlock* yy_default_bb;
llvm::BasicBlock* yy_end_bb;
llvm::Function*  yy_func;

llvm::Type* returnType;
std::map<std::string, llvm::Value*> oldSymbolTable;

llvm::BasicBlock* mainBB;
llvm::Function* mainFunction = nullptr;

void initializeMain()
{
  if(mainFunction != nullptr)
    return;

  auto* mainTy = llvm::FunctionType::get(llvm::Type::getVoidTy(context), false);
  mainFunction = llvm::Function::Create(mainTy, llvm::Function::ExternalLinkage, "main", module);
  mainBB = llvm::BasicBlock::Create(context, "entry", mainFunction);
  builder->SetInsertPoint(mainBB);
}
%}

%union
{
  int num;
  int op;
  char ch;
  char* identifier;
  char* string;
  void* llvm_ptr;
    
  void* basic_block;
  struct
  {
    void* then_bb;
    void* else_bb;
    void* merge_bb;
  } if_blocks;

  struct
  {
    void* cond_bb;
    void* body_bb;
    void* after_bb;
  } while_blocks;

  struct 
  {
    char*   var_name;
    void*   init_val;
    void*   end_val;
    void*   step_val;
    void*   cond_bb;
    void*   body_bb;
    void*   inc_bb;
    void*   after_bb;
  } for_blocks;

  struct
  {
    void* switch_inst;
    void* default_bb;
    void* end_bb;
    void* func;
  } switch_blocks;

  struct
  {
    char* name;
    void* param_types;
    void* param_names;
    void* return_type;
  } function_decl;

  struct
  {
    char* name;
    void* args;
  } function_call;

  struct
  {
    void* field_types;
    void* field_names;
  } field_decls;
}

%token <num> NUMBER
%token <ch> CHAR_LITERAL
%token <string> STRING_LITERAL
%token <identifier> IDENTIFIER
%token INT CHAR ASSIGN STRING SEMICOLON PRINT LPAREN RPAREN LBRACKET RBRACKET COMMA IF ELSE LESSTHAN GREATERTHAN EQUAL NOTEQUAL LBRACE RBRACE END WHILE LESSEQUAL GREATEREQUAL BREAK
%token <op> OPERATOR PLUS MINUS MUL DIV
%token <op> ADDSUB INCREMENT DECREMENT
%token <op> AND OR PTR AMPERSAND
%token SWITCH CASE DEFAULT FOR TO STEP
%token FUNCTION RETURN VOID DYN
%token STRUCT DOT

%type <llvm_ptr> type literal expression if_statement pointer_exp pointer_retrieve
%type <llvm_ptr> declaration assignment print_statement
%type <llvm_ptr> program statement statements init_main fini_main block
%type <if_blocks> if_condition
%type <basic_block> if_then_part

%type <while_blocks> while_condition while_start
%type <basic_block> while_statement break_statement
%type <llvm_ptr> addsub_statement

%type <basic_block> switch_statement

%type <for_blocks> for_start for_header
%type <basic_block> for_statement

%type <function_decl> function_declaration
%type <function_call> function_call
%type <llvm_ptr> return_statement
%type <function_decl> parameter_list
%type <function_call> argument_list

%type <llvm_ptr> dyn_allocation structure_definition
%type <field_decls> field_declarations

%%

program: init_main statements fini_main
    {
      // No need to add return here as it's handled in fini_main
    }
  ;

block: statements
    {
      // Just pass through the statements without adding fini_main
    }
  ;

init_main:
    { 
      initializeMain();
    }
  ;

fini_main:
    {
      if (builder->GetInsertBlock()->getParent() == mainFunction) {
        llvm::BasicBlock* currentBB = builder->GetInsertBlock();
        if (!currentBB->getTerminator()) {
          builder->CreateRetVoid();
        }
      }
    }
  ;

statements:
    | statements statement
  ;

statement:
      declaration { $$ = $1; }
    | assignment { $$ = $1; }
    | print_statement { $$ = $1; }
    | if_statement { $$ = $1; }
    | while_statement { $$ = nullptr; }
    | addsub_statement { $$ = $1; }
    | break_statement { $$ = nullptr; }
    | for_statement { $$ = nullptr; }
    | switch_statement { $$ = nullptr; }
    | function_declaration
    | return_statement
    | function_call_statement
    | structure_definition { $$ = $1; }
    ;

type:
      INT   { $$ = (void*)builder->getInt32Ty(); }
    | CHAR  { $$ = (void*)builder->getInt8Ty(); }
    | STRING { $$ = llvm::PointerType::get(llvm::Type::getInt8Ty(context), 0); }
    | PTR   { $$ = (void*)llvm::PointerType::get(llvm::Type::getInt8Ty(context), 0); temp = 1; }
    | VOID { $$ = llvm::Type::getVoidTy(context); }
    | STRUCT IDENTIFIER
      {
        std::string structName = $2;
        if (structTypes.find(structName) == structTypes.end()) {
          yyerror("Undefined structure type");
          exit(1);
        }
        $$ = (void*)structTypes[structName].first;
        free($2);
      }
    ;

structure_definition:
    STRUCT IDENTIFIER LBRACE field_declarations RBRACE SEMICOLON
    {
        std::string structName = $2;
        if(structTypes.find(structName) != structTypes.end())
        {
            yyerror("Structure already defined");
            exit(1);
        }
        auto* fieldInfos = static_cast<std::vector<FieldInfo>*>($4.field_types);
        auto* fieldNames = static_cast<std::vector<std::string>*>($4.field_names);
        std::map<std::string, unsigned> fieldMap;
        std::vector<llvm::Type*> fieldTypes;
        std::map<std::string, llvm::Value*> fieldInitValues;
        
        for(size_t i = 0; i < fieldNames->size(); ++i)
        {
          std::string fieldName = (*fieldNames)[i];
          if(fieldMap.find(fieldName) != fieldMap.end())
          {
            yyerror("Duplicate field name in structure");
            exit(1);
          }
          fieldMap[fieldName] = i;
          fieldTypes.push_back((*fieldInfos)[i].type);
          fieldInitValues[fieldName] = (*fieldInfos)[i].initValue;
        }
        
        llvm::StructType* structTy = llvm::StructType::create(context, fieldTypes, structName);
        structTypes[structName] = std::make_pair(structTy, fieldMap);
        
        structInitValues[structName] = fieldInitValues;
        
        delete fieldInfos;
        delete fieldNames;
        free($2);
        $$ = nullptr;
    }
;

field_declarations:
    {
      $$.field_types = new std::vector<FieldInfo>();
      $$.field_names = new std::vector<std::string>();
    }
    | field_declarations type IDENTIFIER SEMICOLON
    {
      $$.field_types = $1.field_types;
      $$.field_names = $1.field_names;
      FieldInfo info;
      info.type = static_cast<llvm::Type*>($2);
      info.name = $3;
      if (info.type == llvm::PointerType::get(llvm::Type::getInt8Ty(context), 0)) {
        // For string type, initialize with null pointer
        info.initValue = llvm::ConstantPointerNull::get(llvm::cast<llvm::PointerType>(info.type));
      } else {
        info.initValue = llvm::ConstantInt::get(info.type, 0);
      }
      static_cast<std::vector<FieldInfo>*>($$.field_types)->push_back(info);
      static_cast<std::vector<std::string>*>($$.field_names)->push_back($3);
      free($3);
    }
    | field_declarations type IDENTIFIER ASSIGN literal SEMICOLON
    {
      $$.field_types = $1.field_types;
      $$.field_names = $1.field_names;
      FieldInfo info;
      info.type = static_cast<llvm::Type*>($2);
      info.name = $3;
      info.initValue = static_cast<llvm::Value*>($5);
      static_cast<std::vector<FieldInfo>*>($$.field_types)->push_back(info);
      static_cast<std::vector<std::string>*>($$.field_names)->push_back($3);
      free($3);
    }
    | field_declarations type IDENTIFIER ASSIGN STRING_LITERAL SEMICOLON
    {
      $$.field_types = $1.field_types;
      $$.field_names = $1.field_names;
      FieldInfo info;
      info.type = static_cast<llvm::Type*>($2);
      info.name = $3;
      info.initValue = builder->CreateGlobalStringPtr($5);
      static_cast<std::vector<FieldInfo>*>($$.field_types)->push_back(info);
      static_cast<std::vector<std::string>*>($$.field_names)->push_back($3);
      free($3);
      free($5);
    }
;

print_statement:
    PRINT LPAREN expression RPAREN SEMICOLON
    {
      llvm::Value *exprVal = static_cast<llvm::Value*>($3);
      llvm::Type  *valType = exprVal->getType();

      llvm::Function *printfFunc = module->getFunction("printf");
      if(!printfFunc)
      {
        std::vector<llvm::Type*> printfArgs;
        printfArgs.push_back(llvm::PointerType::get(context, 0));
        llvm::FunctionType *printfType = llvm::FunctionType::get(builder->getInt32Ty(), printfArgs, true);
        printfFunc = llvm::Function::Create(printfType, llvm::Function::ExternalLinkage, "printf", module);
      }

      if(!llvm::isa<llvm::ConstantPointerNull>(exprVal))
      {
        llvm::Value *formatStr = nullptr;

        if(valType->isIntegerTy(8))
        {
          formatStr = builder->CreateGlobalStringPtr("%c\n");
        }
        else if(valType->isIntegerTy(32))
        {
          formatStr = builder->CreateGlobalStringPtr("%d\n");
        }
        else if(valType->isPointerTy())
        {
          if(llvm::isa<llvm::AllocaInst>(exprVal))
          {
            llvm::AllocaInst* allocInst = llvm::cast<llvm::AllocaInst>(exprVal);
            bool isStringVar = false;
            for(const auto& pair : stringVariables)
            {
              if (symbolTable[pair.first] == exprVal)
              {
                isStringVar = true;
                break;
              }
            }
                
            if(isStringVar)
            {
              llvm::Value* loadedPtr = builder->CreateLoad(allocInst->getAllocatedType(), exprVal, "load_str");
              formatStr = builder->CreateGlobalStringPtr("%s\n");
              exprVal = loadedPtr;
            }
            else
            {
              formatStr = builder->CreateGlobalStringPtr("%p\n");
            }
          }
          else
          {
            formatStr = builder->CreateGlobalStringPtr("%p\n");
          }
        }
        else
        {
          yyerror("Unsupported print type.\n");
          exit(1);
        }

      builder->CreateCall(printfFunc, { formatStr, exprVal });
    }
  }
  | PRINT LPAREN STRING_LITERAL RPAREN SEMICOLON
    {
      printf("%s\n", $3);
      free($3);
    
      llvm::Function *printfFunc = module->getFunction("printf");
      if(!printfFunc)
      {
        std::vector<llvm::Type*> printfArgs;
        printfArgs.push_back(llvm::PointerType::get(context, 0));
        llvm::FunctionType *printfType = llvm::FunctionType::get(builder->getInt32Ty(), printfArgs, true);
        printfFunc = llvm::Function::Create(printfType, llvm::Function::ExternalLinkage, "printf", module);
      }
    
      llvm::Value *formatStr = builder->CreateGlobalStringPtr("%s\n");
      llvm::Value *strVal = builder->CreateGlobalStringPtr($3);
      builder->CreateCall(printfFunc, { formatStr, strVal });
    }
  | PRINT LPAREN pointer_retrieve RPAREN SEMICOLON
    {
      llvm::Value* loaded = static_cast<llvm::Value*>($3);
        
      llvm::Function* printfFunc = module->getFunction("printf");
      if(!printfFunc)
      {
        std::vector<llvm::Type*> printfArgs;
        printfArgs.push_back(llvm::PointerType::get(context, 0));
        llvm::FunctionType* printfType = llvm::FunctionType::get(builder->getInt32Ty(), printfArgs, true);
        printfFunc = llvm::Function::Create(printfType, llvm::Function::ExternalLinkage, "printf", module);
      }

      llvm::Value* formatStr;
      if(loaded->getType()->isIntegerTy(8))
      {
        formatStr = builder->CreateGlobalStringPtr("%c\n");
      }
      else
      {
        formatStr = builder->CreateGlobalStringPtr("%d\n");
      }
      builder->CreateCall(printfFunc, { formatStr, loaded });
    }
;

declaration:
  type IDENTIFIER SEMICOLON
  {
    auto* ty = static_cast<llvm::Type*>($1);
    llvm::AllocaInst* alloc = builder->CreateAlloca(ty, nullptr, $2);

    if(ty->isIntegerTy(32))
    {
      builder->CreateStore(llvm::ConstantInt::get(ty, 0), alloc);
    }
    else if(ty->isIntegerTy(8))
    {
      builder->CreateStore(llvm::ConstantInt::get(ty, 0), alloc);
    }
    else if(ty->isStructTy())
    {
      llvm::StructType* structTy = llvm::cast<llvm::StructType>(ty);
      std::string structName = structTy->getName().str();
      auto it = structTypes.find(structName);
      if(it != structTypes.end())
      {
        auto& fieldMap = it->second.second;
        auto& initValues = structInitValues[structName];
        for(const auto& field : fieldMap)
        {
          llvm::Value* fieldPtr = builder->CreateStructGEP(structTy, alloc, field.second, "fieldptr");
          llvm::Type* fieldTy = structTy->getElementType(field.second);
          if(initValues.find(field.first) != initValues.end())
          {
            builder->CreateStore(initValues[field.first], fieldPtr);
          }
          else if(fieldTy->isIntegerTy(32) || fieldTy->isIntegerTy(8))
          {
            builder->CreateStore(llvm::ConstantInt::get(fieldTy, 0), fieldPtr);
          }
        }
      }
    }
    symbolTable[$2] = alloc;
    printf("Allocated %s at %p\n", $2, (void*)alloc);
    free($2);
  }
  | type IDENTIFIER ASSIGN literal SEMICOLON
    {
      auto* ty = static_cast<llvm::Type*>($1);
      auto* val = static_cast<llvm::Value*>($4);
    
      llvm::AllocaInst* alloc = builder->CreateAlloca(ty, nullptr, $2);
      builder->CreateStore(val, alloc);
      symbolTable[$2] = alloc;
    
      if(auto* ci = llvm::dyn_cast<llvm::ConstantInt>(val))
      {
        if (ty->isIntegerTy(32))
          printf("Initialized %s = %d at %p\n", $2, ci->getSExtValue(), (void*)alloc);
        else
          printf("Initialized %s = '%c' at %p\n", $2, (char)ci->getSExtValue(), (void*)alloc);
      }
      free($2);
    }
  | type IDENTIFIER ASSIGN STRING_LITERAL SEMICOLON
    {
      auto* ty = static_cast<llvm::Type*>($1);
      llvm::Value* strVal = builder->CreateGlobalStringPtr($4);
      llvm::AllocaInst* alloc = builder->CreateAlloca(ty, nullptr, $2);
      builder->CreateStore(strVal, alloc);
      symbolTable[$2] = alloc;
      stringVariables[$2] = true;
      printf("Initialized %s = \"%s\" at %p\n", $2, $4, (void*)alloc);
      free($2);
      free($4);
    }
  | type IDENTIFIER ASSIGN expression SEMICOLON
    {
      auto *ty  = static_cast<llvm::Type*>($1);
      auto *val = static_cast<llvm::Value*>($4);

      if(ty->isPointerTy() && !val->getType()->isPointerTy())
      {
        yyerror("Right-hand side is not a pointer");
        exit(1);
      }
    
      llvm::AllocaInst* alloc = builder->CreateAlloca(ty, nullptr, $2);
      builder->CreateStore(val, alloc);
      symbolTable[$2] = alloc;
    
      if (auto* ci = llvm::dyn_cast<llvm::ConstantInt>(val))
      {
        if (ty->isIntegerTy(32))
          printf("Initialized %s = %d at %p\n", $2, ci->getSExtValue(), (void*)alloc);
        else
          printf("Initialized %s = '%c' at %p\n", (char)ci->getSExtValue(), (void*)alloc);
      }
      else
      {
        printf("Initialized %s with a computed expression at %p\n", $2, (void*)alloc);
      }
      free($2);
    }
  | type IDENTIFIER LBRACKET NUMBER RBRACKET SEMICOLON
    {
      auto* ty = static_cast<llvm::Type*>($1);
      llvm::ArrayType* arrayType = llvm::ArrayType::get(ty, $4);
      llvm::AllocaInst* alloc = builder->CreateAlloca(arrayType, nullptr, $2);
      symbolTable[$2] = alloc;
      printf("Allocated array %s[%d] at %p\n", $2, $4, (void*)alloc);
      free($2);
    }
  | type IDENTIFIER ASSIGN pointer_exp SEMICOLON
    {
      llvm::Type* ty = static_cast<llvm::Type*>($1);
      llvm::Value* val = static_cast<llvm::Value*>($4);
      llvm::AllocaInst* alloc = builder->CreateAlloca(ty, nullptr, $2);
      builder->CreateStore(val, alloc);
      symbolTable[$2] = alloc;
      printf("Initialized pointer %s at %p\n", $2, (void*)alloc);
      free($2);
    }
  | type IDENTIFIER ASSIGN pointer_retrieve SEMICOLON
    {
      llvm::Type* ty  = static_cast<llvm::Type*>($1);
      llvm::Value* val = static_cast<llvm::Value*>($4);

      if(!ty->isIntegerTy(32) && !ty->isIntegerTy(8))
      {
        yyerror("Cannot assign dereferenced pointer to non-int/char");
        exit(1);
      }

      llvm::AllocaInst* alloc = builder->CreateAlloca(ty, nullptr, $2);
      builder->CreateStore(val, alloc);
      symbolTable[$2] = alloc;

      free($2);
    }
  | type IDENTIFIER ASSIGN dyn_allocation SEMICOLON
    {
      if(temp == 1)
      {
        temp = 0;
        llvm::Type* ty = static_cast<llvm::Type*>($1);
        llvm::Value* val = static_cast<llvm::Value*>($4);
        llvm::AllocaInst* alloc = builder->CreateAlloca(ty, nullptr, $2);
        builder->CreateStore(val, alloc);
        symbolTable[$2] = alloc;
        printf("Dynamically allocated %s at %p\n", $2, (void*)val);
        free($2);
      }
      else
      {
        yyerror("Non pointer type variables can't be assigned dynamically");
        exit(1);
      }
    }
;

pointer_exp:
    AMPERSAND IDENTIFIER
    {
      auto it = symbolTable.find($2);
      if (it == symbolTable.end())
      {
        yyerror("Undefined variable");
        exit(1);
      }
      llvm::Value* alloc = it->second;

      if (!llvm::isa<llvm::AllocaInst>(alloc))
      {
        yyerror("Can only take address of local variables");
        exit(1);
      }
      llvm::AllocaInst* allocaInst = llvm::cast<llvm::AllocaInst>(alloc);

      llvm::Type* elemTy = allocaInst->getAllocatedType();

      llvm::Type* i8PtrTy = llvm::PointerType::get(llvm::Type::getInt8Ty(context), 0);
      $$ = (void*)builder->CreateBitCast(alloc, i8PtrTy);
      printf("Created pointer to %s\n", $2);
      free($2);
    }
  ;

pointer_retrieve:
    OPERATOR expression
    {
      if($1 == MUL)
      {
        llvm::Value* ptrVal = static_cast<llvm::Value*>($2);
        llvm::Type* ptrTy   = ptrVal->getType();
        if(!ptrTy->isPointerTy())
        {
          yyerror("Cannot dereference non-pointer");
          exit(1);
        }

        llvm::Value* loaded = builder->CreateLoad(llvm::Type::getInt32Ty(context), ptrVal, "deref");
        $$ = (void*)loaded;
      }
      else if($1 == MINUS)
      {
        llvm::Value* val = static_cast<llvm::Value*>($2);
        if (llvm::ConstantInt* CI = llvm::dyn_cast<llvm::ConstantInt>(val))
        {
          $$ = (void*)llvm::ConstantInt::get(builder->getInt32Ty(), -CI->getSExtValue());
        }
        else
        {
          $$ = (void*)builder->CreateNeg(val, "neg");
        }
      }
      else
      {
        yyerror("Star operator must be used to access a pointer");
        exit(1);
      }
    }
  | OPERATOR expression OPERATOR expression
    {
      if($1 == MUL)
      {
        llvm::Value* ptrVal = static_cast<llvm::Value*>($2);
        llvm::Value* opVal = static_cast<llvm::Value*>($4);
        llvm::Type* ptrTy   = ptrVal->getType();
          
        if(!ptrTy->isPointerTy())
        {
          yyerror("Cannot dereference non-pointer");
          exit(1);
        }

        llvm::Value* loaded = builder->CreateLoad(llvm::Type::getInt32Ty(context), ptrVal, "deref");
          
        llvm::Value* result = nullptr;
        if($3 == PLUS)
          result = builder->CreateAdd(loaded, opVal, "add");
        else if($3 == MINUS)
          result = builder->CreateSub(loaded, opVal, "sub");
        else if($3 == MUL)
          result = builder->CreateMul(loaded, opVal, "mul");
        else if($3 == DIV)
        {
          if(llvm::ConstantInt* CI = llvm::dyn_cast<llvm::ConstantInt>(opVal))
          {
            if(CI->getSExtValue() == 0)
            {
              yyerror("Error: Division by zero!");
              exit(1);
            }
          }
          result = builder->CreateSDiv(loaded, opVal, "div");
        }
        else
        {
          yyerror("Invalid operation on dereferenced pointer");
          exit(1);
        }
          
        $$ = (void*)result;
      }
      else
      {
        yyerror("Invalid pointer arithmetic");
        exit(1);
      }
    }
  | OPERATOR expression OPERATOR NUMBER
    {
      if($1 == MUL)
      {
        llvm::Value* ptrVal = static_cast<llvm::Value*>($2);
        llvm::Type* ptrTy   = ptrVal->getType();
          
        if(!ptrTy->isPointerTy())
        {
          yyerror("Cannot dereference non-pointer");
          exit(1);
        }

        llvm::Value* loaded = builder->CreateLoad(llvm::Type::getInt32Ty(context), ptrVal, "deref");
          
        llvm::Value* opVal = llvm::ConstantInt::get(builder->getInt32Ty(), $4);
          
        llvm::Value* result = nullptr;
        if($3 == PLUS)
          result = builder->CreateAdd(loaded, opVal, "add");
        else if($3 == MINUS)
          result = builder->CreateSub(loaded, opVal, "sub");
        else if($3 == MUL)
          result = builder->CreateMul(loaded, opVal, "mul");
        else if ($3 == DIV)
        {
          if ($4 == 0)
          {
            yyerror("Error: Division by zero!");
            exit(1);
          }
          result = builder->CreateSDiv(loaded, opVal, "div");
        }
        else
        {
          yyerror("Invalid operation on dereferenced pointer");
          exit(1);
        }
          
        $$ = (void*)result;
      }
      else
      {
        yyerror("Invalid pointer arithmetic");
        exit(1);
      }
    }
;

literal:
    NUMBER       { $$ = (void*)llvm::ConstantInt::get(builder->getInt32Ty(), $1);  }
  | MINUS NUMBER { $$ = (void*)llvm::ConstantInt::get(builder->getInt32Ty(), -$2); }
  | CHAR_LITERAL { $$ = (void*)llvm::ConstantInt::get(builder->getInt8Ty(), $1);   }
;

expression:
    literal                   { $$ = $1; }
  | MINUS NUMBER              { $$ = (void*)llvm::ConstantInt::get(builder->getInt32Ty(), -$2); }
  | IDENTIFIER
    {
      auto* var = symbolTable[$1];
      if(!var)
      {
        yyerror("Undefined variable");
        exit(1);
      }
      llvm::PointerType *ptrType = llvm::dyn_cast<llvm::PointerType>(var->getType());
      if(!ptrType)
      {
        yyerror("Invalid pointer type");
        exit(1);
      }
      llvm::AllocaInst* allocInst = llvm::cast<llvm::AllocaInst>(var);
      llvm::Type* varType = allocInst->getAllocatedType();
        
      if(stringVariables.find($1) != stringVariables.end())
      {
          $$ = (void*)var;
      }
      else
      {
        $$ = (void*)builder->CreateLoad(varType, var);
      }
      free($1);
    }
  | IDENTIFIER DOT IDENTIFIER
    {
      auto* var = symbolTable[$1];
      if(!var)
      {
        yyerror("Undefined variable");
        exit(1);
      }
      llvm::Type* varTy = llvm::cast<llvm::AllocaInst>(var)->getAllocatedType();
      if(!varTy->isStructTy())
      {
        yyerror("Not a structure type");
        exit(1);
      }
      llvm::StructType* structTy = llvm::cast<llvm::StructType>(varTy);
      std::string structName = structTy->getName().str();
      auto it = structTypes.find(structName);
      if(it == structTypes.end())
      {
        yyerror("Structure type not found");
        exit(1);
      }
      auto& fieldMap = it->second.second;
      std::string fieldName = $3;
      if(fieldMap.find(fieldName) == fieldMap.end())
      {
        yyerror("Field not found in structure");
        exit(1);
      }
      unsigned fieldIndex = fieldMap[fieldName];
      llvm::Value* fieldPtr = builder->CreateStructGEP(structTy, var, fieldIndex, "fieldptr");
      llvm::Value* fieldVal = builder->CreateLoad(structTy->getElementType(fieldIndex), fieldPtr, "fieldload");
      $$ = (void*)fieldVal;
      free($1);
      free($3);
    }
  | pointer_retrieve
    {
      llvm::Value* loaded = static_cast<llvm::Value*>($1);
      $$ = (void*)loaded;
    }
  | function_call
    {
      auto* func = module->getFunction($1.name);
      if(!func)
      {
        yyerror("Undefined function");
        exit(1);
      }
        
      auto* args = static_cast<std::vector<llvm::Value*>*>($1.args);
      std::vector<llvm::Value*> callArgs;
      for(auto* arg : *args)
      {
        callArgs.push_back(static_cast<llvm::Value*>(arg));
      }
        
      if(func->getReturnType()->isVoidTy())
      {
        fprintf(stderr, "Warning: Using void function '%s' in expression. Using 0 instead.\n", func->getName().str().c_str());
        $$ = (void*)llvm::ConstantInt::get(builder->getInt32Ty(), 0);
        builder->CreateCall(func, callArgs);
      }
      else 
      {
        $$ = (void*)builder->CreateCall(func, callArgs, "calltmp");
      }
        
      delete args;
      free($1.name);
    }
  | IDENTIFIER LBRACKET expression RBRACKET
    {
      auto* var = symbolTable[$1];
      if(!var)
      {
        yyerror("Undefined array");
        exit(1);
      }

      llvm::Value* indexVal = static_cast<llvm::Value*>($3);

      llvm::AllocaInst* allocInst = llvm::cast<llvm::AllocaInst>(var);
      llvm::ArrayType* arrType = llvm::cast<llvm::ArrayType>(allocInst->getAllocatedType());
      unsigned arraySize = arrType->getNumElements();

      llvm::Value* lowerBound = llvm::ConstantInt::get(builder->getInt32Ty(), 0);
      llvm::Value* upperBound = llvm::ConstantInt::get(builder->getInt32Ty(), arraySize);
      llvm::Value* geLower = builder->CreateICmpSGE(indexVal, lowerBound, "ge_lower");
      llvm::Value* ltUpper = builder->CreateICmpSLT(indexVal, upperBound, "lt_upper");
      llvm::Value* inBounds = builder->CreateAnd(geLower, ltUpper, "in_bounds");

      llvm::Function* func = builder->GetInsertBlock()->getParent();
      llvm::BasicBlock* errorBB = llvm::BasicBlock::Create(context, "array_out_of_bounds", func);
      llvm::BasicBlock* continueBB = llvm::BasicBlock::Create(context, "array_in_bounds", func);

      builder->CreateCondBr(inBounds, continueBB, errorBB);

      builder->SetInsertPoint(errorBB);
      llvm::Function* printfFunc = module->getFunction("printf");
      if(!printfFunc)
      {
        std::vector<llvm::Type*> printfArgs;
        printfArgs.push_back(llvm::PointerType::get(context, 0));
        llvm::FunctionType* printfType = llvm::FunctionType::get(builder->getInt32Ty(), printfArgs, true);
        printfFunc = llvm::Function::Create(printfType, llvm::Function::ExternalLinkage, "printf", module);
      }
      llvm::Value* errStr = builder->CreateGlobalStringPtr("Error: Array index out of bounds!\n");
      builder->CreateCall(printfFunc, { errStr });
      llvm::Function* exitFunc = module->getFunction("exit");
      if(!exitFunc)
      {
        std::vector<llvm::Type*> exitArgs { builder->getInt32Ty() };
        llvm::FunctionType* exitType = llvm::FunctionType::get(builder->getVoidTy(), exitArgs, false);
        exitFunc = llvm::Function::Create(exitType, llvm::Function::ExternalLinkage, "exit", module);
      }
      builder->CreateCall(exitFunc, { llvm::ConstantInt::get(builder->getInt32Ty(), 1) });
      builder->CreateUnreachable();

      builder->SetInsertPoint(continueBB);
      llvm::Value* elemPtr = builder->CreateInBoundsGEP(allocInst->getAllocatedType(), var, { llvm::ConstantInt::get(builder->getInt32Ty(), 0), indexVal }, "arrayelem");
      $$ = (void*)builder->CreateLoad(arrType->getElementType(), elemPtr, "arrayload");
      free($1);
    }
  | IDENTIFIER ADDSUB
    {
      auto* var = symbolTable[$1];
      if(!var)
      {
        yyerror("Undefined variable");
        exit(1);
      }
      llvm::PointerType *ptrType = llvm::dyn_cast<llvm::PointerType>(var->getType());
      if(!ptrType)
      {
        yyerror("Invalid pointer type");
        exit(1);
      }
        
      llvm::Value* currentVal = builder->CreateLoad(llvm::cast<llvm::AllocaInst>(var)->getAllocatedType(), var);
        
      llvm::Value* one = llvm::ConstantInt::get(currentVal->getType(), 1);
      llvm::Value* newVal;

      if($2 == INCREMENT)
      {
        newVal = builder->CreateAdd(currentVal, one, "increment");
      }
      else if($2 == DECREMENT)
      {
        newVal = builder->CreateSub(currentVal, one, "decrement");
      }
      builder->CreateStore(newVal, var);
        
      $$ = (void*)newVal;
      free($1);
    }
  | expression AND expression
    {
      auto* lhs = static_cast<llvm::Value*>($1);
      auto* rhs = static_cast<llvm::Value*>($3);

      if (lhs->getType() != llvm::Type::getInt1Ty(context))
      {
        lhs = builder->CreateICmpNE(lhs, llvm::ConstantInt::get(lhs->getType(), 0), "bool_lhs");
      }
      if(rhs->getType() != llvm::Type::getInt1Ty(context))
      {
        rhs = builder->CreateICmpNE(rhs, llvm::ConstantInt::get(rhs->getType(), 0), "bool_rhs");
      }
       
      llvm::Value* result = builder->CreateAnd(lhs, rhs, "and");

      $$ = (void*)builder->CreateZExt(result, builder->getInt32Ty(), "and_result");
    }
  | expression OR expression
    {
      auto* lhs = static_cast<llvm::Value*>($1);
      auto* rhs = static_cast<llvm::Value*>($3);
      
      if (lhs->getType() != llvm::Type::getInt1Ty(context))
      {
        lhs = builder->CreateICmpNE(lhs, llvm::ConstantInt::get(lhs->getType(), 0), "bool_lhs");
      }
      if (rhs->getType() != llvm::Type::getInt1Ty(context))
      {
        rhs = builder->CreateICmpNE(rhs, llvm::ConstantInt::get(rhs->getType(), 0), "bool_rhs");
      }
      
      llvm::Value* result = builder->CreateOr(lhs, rhs, "OR");
      $$ = (void*)builder->CreateZExt(result, builder->getInt32Ty(), "or_result");
    }
  | expression OPERATOR expression
    {
      auto* lhs = static_cast<llvm::Value*>($1);
      auto* rhs = static_cast<llvm::Value*>($3);
      llvm::Type* lhsType = lhs->getType();
      llvm::Type* rhsType = rhs->getType();
      bool isCharOp = lhsType->isIntegerTy(8) || rhsType->isIntegerTy(8);
      bool isStringOp = false;

      if (llvm::isa<llvm::AllocaInst>(lhs) || llvm::isa<llvm::AllocaInst>(rhs))
      {
        for(const auto& pair : stringVariables)
        {
          if (symbolTable[pair.first] == lhs || symbolTable[pair.first] == rhs)
          {
            isStringOp = true;
            break;
          }
        }
      }
      
      if(isStringOp)
      {
        if($2 == PLUS)
        {
          llvm::Function *printfFunc = module->getFunction("printf");
          if(!printfFunc)
          {
            std::vector<llvm::Type*> printfArgs;
            printfArgs.push_back(llvm::PointerType::get(context, 0));
            llvm::FunctionType *printfType = llvm::FunctionType::get(builder->getInt32Ty(), printfArgs, true);
            printfFunc = llvm::Function::Create(printfType, llvm::Function::ExternalLinkage, "printf", module);
          }
          llvm::Value* lhsVal = lhs;
          llvm::Value* rhsVal = rhs;
              
          if(llvm::isa<llvm::AllocaInst>(lhs))
          {
            lhsVal = builder->CreateLoad(llvm::cast<llvm::AllocaInst>(lhs)->getAllocatedType(), lhs, "load_lhs");
          }
          if(llvm::isa<llvm::AllocaInst>(rhs))
          {
            rhsVal = builder->CreateLoad(llvm::cast<llvm::AllocaInst>(rhs)->getAllocatedType(), rhs, "load_rhs");
          }
          llvm::Value *formatStr = builder->CreateGlobalStringPtr("%s%s\n");

          builder->CreateCall(printfFunc, { formatStr, lhsVal, rhsVal });
          $$ = (void*)llvm::ConstantPointerNull::get(llvm::PointerType::get(context, 0));
        }
        else
        {
            yyerror("Invalid operation on string type");
            exit(1);
        }
    }
    else
    {
      if(lhsType->isIntegerTy(8) && rhsType->isIntegerTy(32))
      {
        lhs = builder->CreateZExt(lhs, builder->getInt32Ty(), "charToInt");
        isCharOp = false;
      }
      if(lhsType->isIntegerTy(32) && rhsType->isIntegerTy(8))
      {
        rhs = builder->CreateZExt(rhs, builder->getInt32Ty(), "charToInt");
        isCharOp = false;
      }
      if(lhsType->isPointerTy() && !lhs->getName().str().empty() && lhs->getName().str() != "deref")
      {
        lhs = builder->CreateLoad(llvm::Type::getInt32Ty(context), lhs, "load_ptr");
      }
      if(rhsType->isPointerTy() && !rhs->getName().str().empty() && rhs->getName().str() != "deref")
      {
        rhs = builder->CreateLoad(llvm::Type::getInt32Ty(context), rhs, "load_ptr");
      }
      
      llvm::Value* result = nullptr;
      
      if($2 == PLUS)
        result = builder->CreateAdd(lhs, rhs, "add");
      else if($2 == MINUS)
        result = builder->CreateSub(lhs, rhs, "sub");
      else if($2 == MUL)
        result = builder->CreateMul(lhs, rhs, "mul");
      else if($2 == DIV)
      {
        if(llvm::ConstantInt* CI = llvm::dyn_cast<llvm::ConstantInt>(rhs))
        {
          if(CI->getSExtValue() == 0)
          {
            yyerror("Error: Division by zero!");
            exit(1);
          }
        }
        result = builder->CreateSDiv(lhs, rhs, "div");
      }
      else if($2 == LESSTHAN)
      {
        result = builder->CreateZExt(builder->CreateICmpSLT(lhs, rhs, "lt"), llvm::Type::getInt32Ty(context), "lt_ext");
      }
      else if($2 == GREATERTHAN)
      {
        result = builder->CreateZExt(builder->CreateICmpSGT(lhs, rhs, "gt"), llvm::Type::getInt32Ty(context), "gt_ext");
      }
      else if ($2 == LESSEQUAL)
      {
        result = builder->CreateZExt(builder->CreateICmpSLE(lhs, rhs, "le"), llvm::Type::getInt32Ty(context), "le_ext");
      }
      else if ($2 == GREATEREQUAL)
      {
        result = builder->CreateZExt(builder->CreateICmpSGE(lhs, rhs, "ge"), llvm::Type::getInt32Ty(context), "ge_ext");
      }
      else if ($2 == EQUAL)
      {
        result = builder->CreateZExt(builder->CreateICmpEQ(lhs, rhs, "eq"), llvm::Type::getInt32Ty(context), "eq_ext");
      }
      else if ($2 == NOTEQUAL)
      {
        result = builder->CreateZExt(builder->CreateICmpNE(lhs, rhs, "neq"), llvm::Type::getInt32Ty(context), "neq_ext");
      }
      
      if (isCharOp && result && ($2 == PLUS || $2 == MINUS || $2 == MUL || $2 == DIV))
      {
          if (result->getType()->isIntegerTy(32))
          {
            if (lhsType->isIntegerTy(8) && rhsType->isIntegerTy(8))
            {
              result = builder->CreateTrunc(result, builder->getInt8Ty(), "intToChar");
            }
          }
      }
      
      if (result && result->getType()->isIntegerTy(8))
      {
        result = builder->CreateZExt(result, builder->getInt32Ty(), "result_to_int");
      }
      
      $$ = (void*)result;
    }
  }   
;

assignment:
    IDENTIFIER ASSIGN expression SEMICOLON
    {
      auto* var = symbolTable[$1];
      auto* val = static_cast<llvm::Value*>($3);
      
      if (auto* callInst = llvm::dyn_cast<llvm::CallInst>(val))
      {
          if (callInst->getFunctionType()->getReturnType()->isVoidTy())
          {
            fprintf(stderr, "Warning: Attempting to assign void function '%s' to variable '%s'. Assigning 0 instead.\n", callInst->getCalledFunction()->getName().str().c_str(), $1);
            val = llvm::ConstantInt::get(builder->getInt32Ty(), 0);
          }
      }
      builder->CreateStore(val, var);
      
      if (auto* ci = llvm::dyn_cast<llvm::ConstantInt>(val))
      {
        llvm::PointerType *ptrType = llvm::dyn_cast<llvm::PointerType>(var->getType());
        if (!ptrType)
        {
          if (llvm::cast<llvm::AllocaInst>(var)->getAllocatedType()->isIntegerTy(32))
            printf("Stored %d at %p\n", ci->getSExtValue(), (void*)var);
          else
            printf("Stored '%c' at %p\n", (char)ci->getSExtValue(), (void*)var);
        }
      }
      else
      {
        printf("Stored computed value at %p\n", (void*)var);
      }
      
      free($1);
    }
  | IDENTIFIER LBRACKET expression RBRACKET ASSIGN expression SEMICOLON
    {
      auto* var = symbolTable[$1];
      if (!var)
      {
        yyerror("Undefined array");
        exit(1);
      }
      llvm::AllocaInst* allocInst = llvm::cast<llvm::AllocaInst>(var);
      llvm::ArrayType* arrType = llvm::cast<llvm::ArrayType>(allocInst->getAllocatedType());
      unsigned arraySize = arrType->getNumElements();

      llvm::Value* indexVal = static_cast<llvm::Value*>($3);

      llvm::Value* lowerBound = llvm::ConstantInt::get(builder->getInt32Ty(), 0);
      llvm::Value* upperBound = llvm::ConstantInt::get(builder->getInt32Ty(), arraySize);
      llvm::Value* geLower = builder->CreateICmpSGE(indexVal, lowerBound, "ge_lower");
      llvm::Value* ltUpper = builder->CreateICmpSLT(indexVal, upperBound, "lt_upper");
      llvm::Value* inBounds = builder->CreateAnd(geLower, ltUpper, "in_bounds");
      llvm::Function* func = builder->GetInsertBlock()->getParent();
      llvm::BasicBlock* errorBB = llvm::BasicBlock::Create(context, "array_out_of_bounds", func);
      llvm::BasicBlock* continueBB = llvm::BasicBlock::Create(context, "array_in_bounds", func);
      builder->CreateCondBr(inBounds, continueBB, errorBB);

      builder->SetInsertPoint(errorBB);
      llvm::Function* printfFunc = module->getFunction("printf");
      if (!printfFunc)
      {
        std::vector<llvm::Type*> printfArgs;
        printfArgs.push_back(llvm::PointerType::get(context, 0));
        llvm::FunctionType* printfType = llvm::FunctionType::get(builder->getInt32Ty(), printfArgs, true);
        printfFunc = llvm::Function::Create(printfType, llvm::Function::ExternalLinkage, "printf", module);
      }
      llvm::Value* errStr = builder->CreateGlobalStringPtr("Error: Array index out of bounds!\n");
      builder->CreateCall(printfFunc, { errStr });
      llvm::Function* exitFunc = module->getFunction("exit");
      if (!exitFunc)
      {
        std::vector<llvm::Type*> exitArgs { builder->getInt32Ty() };
        llvm::FunctionType* exitType = llvm::FunctionType::get(builder->getVoidTy(), exitArgs, false);
        exitFunc = llvm::Function::Create(exitType, llvm::Function::ExternalLinkage, "exit", module);
      }
      builder->CreateCall(exitFunc, { llvm::ConstantInt::get(builder->getInt32Ty(), 1) });
      builder->CreateUnreachable();

      builder->SetInsertPoint(continueBB);
      llvm::Value* elemPtr = builder->CreateInBoundsGEP(allocInst->getAllocatedType(), var, { llvm::ConstantInt::get(builder->getInt32Ty(), 0), indexVal }, "arrayindex");
      llvm::Value* val = static_cast<llvm::Value*>($6);
      builder->CreateStore(val, elemPtr);
      printf("Stored value in array %s at computed index\n", $1);
      free($1);
    }
  | OPERATOR expression ASSIGN expression SEMICOLON
    {
      if ($1 == MUL)
      {
        llvm::Value* ptr = static_cast<llvm::Value*>($2);
        llvm::Type* ptrTy = ptr->getType();
        if (!ptrTy->isPointerTy())
        {
          yyerror("Cannot assign to non-pointer dereference");
          exit(1);
        }
        llvm::Value* val = static_cast<llvm::Value*>($4);
        builder->CreateStore(val, ptr);
      }
      else
      {
        yyerror("Invalid l-value in assignment");
        exit(1);
      }
    } 
  | IDENTIFIER ASSIGN pointer_exp SEMICOLON
    {
      auto* var = symbolTable[$1];
      if (!var)
      {
        yyerror("Undefined variable");
        exit(1);
      }
      
      llvm::Value* val = static_cast<llvm::Value*>($3);
      if (!val->getType()->isPointerTy())
      {
        yyerror("Right-hand side is not a pointer");
        exit(1);
      }
      
      builder->CreateStore(val, var);
      printf("Reassigned pointer %s\n", $1);
      free($1);
    }
  | IDENTIFIER DOT IDENTIFIER ASSIGN expression SEMICOLON
    {
      auto* var = symbolTable[$1];
      if (!var)
      {
        yyerror("Undefined variable");
        exit(1);
      }
      llvm::Type* varTy = llvm::cast<llvm::AllocaInst>(var)->getAllocatedType();
      if (!varTy->isStructTy())
      {
        yyerror("Not a structure type");
        exit(1);
      }
      llvm::StructType* structTy = llvm::cast<llvm::StructType>(varTy);
      std::string structName = structTy->getName().str();
      auto it = structTypes.find(structName);
      if (it == structTypes.end())
      {
        yyerror("Structure type not found");
        exit(1);
      }
      auto& fieldMap = it->second.second;
      std::string fieldName = $3;
      if (fieldMap.find(fieldName) == fieldMap.end())
      {
        yyerror("Field not found in structure");
        exit(1);
      }
      unsigned fieldIndex = fieldMap[fieldName];
      llvm::Value* fieldPtr = builder->CreateStructGEP(structTy, var, fieldIndex, "fieldptr");
      llvm::Value* val = static_cast<llvm::Value*>($5);
      builder->CreateStore(val, fieldPtr);
      printf("Stored value in %s.%s\n", $1, $3);
      free($1);
      free($3);
    }
  | IDENTIFIER ASSIGN STRING_LITERAL SEMICOLON
    {
      auto* var = symbolTable[$1];
      if (!var)
      {
        yyerror("Undefined variable");
        exit(1);
      }
      
      llvm::Value* strVal = builder->CreateGlobalStringPtr($3);
      builder->CreateStore(strVal, var);
      stringVariables[$1] = true;
      printf("Stored string \"%s\" at %p\n", $3, (void*)var);
      free($1);
      free($3);
    }
  | IDENTIFIER DOT IDENTIFIER ASSIGN STRING_LITERAL SEMICOLON
    {
      auto* var = symbolTable[$1];
      if (!var) {
        yyerror("Undefined variable");
        exit(1);
      }
      llvm::Type* varTy = llvm::cast<llvm::AllocaInst>(var)->getAllocatedType();
      if (!varTy->isStructTy()) {
        yyerror("Not a structure type");
        exit(1);
      }
      llvm::StructType* structTy = llvm::cast<llvm::StructType>(varTy);
      std::string structName = structTy->getName().str();
      auto it = structTypes.find(structName);
      if (it == structTypes.end()) {
        yyerror("Structure type not found");
        exit(1);
      }
      auto& fieldMap = it->second.second;
      std::string fieldName = $3;
      if (fieldMap.find(fieldName) == fieldMap.end()) {
        yyerror("Field not found in structure");
        exit(1);
      }
      unsigned fieldIndex = fieldMap[fieldName];
      llvm::Type* fieldTy = structTy->getElementType(fieldIndex);
      if (fieldTy != llvm::PointerType::get(llvm::Type::getInt8Ty(context), 0)) {
        yyerror("Field is not of string type");
        exit(1);
      }
      llvm::Value* fieldPtr = builder->CreateStructGEP(structTy, var, fieldIndex, "fieldptr");
      llvm::Value* strVal = builder->CreateGlobalStringPtr($5);
      builder->CreateStore(strVal, fieldPtr);
      free($1);
      free($3);
      free($5);
    }
;

if_condition:
    IF LPAREN expression RPAREN
    {
      llvm::Value* cond = static_cast<llvm::Value*>($3);
      llvm::Function* func = builder->GetInsertBlock()->getParent();
      
      llvm::BasicBlock* thenBB = llvm::BasicBlock::Create(context, "then", func);
      llvm::BasicBlock* elseBB = llvm::BasicBlock::Create(context, "else");
      llvm::BasicBlock* mergeBB = llvm::BasicBlock::Create(context, "merge");
      
      if(cond->getType() != llvm::Type::getInt1Ty(context))
      {
        cond = builder->CreateICmpNE(cond, llvm::ConstantInt::get(cond->getType(), 0),"ifcond");
      }
      
      builder->CreateCondBr(cond, thenBB, elseBB);
      builder->SetInsertPoint(thenBB);
      
      $$.then_bb = (void*)thenBB;
      $$.else_bb = (void*)elseBB;
      $$.merge_bb = (void*)mergeBB;
    }
;

if_then_part:
    if_condition LBRACE block RBRACE
    {
      llvm::BasicBlock* thenBB = static_cast<llvm::BasicBlock*>($1.then_bb);
      llvm::BasicBlock* elseBB = static_cast<llvm::BasicBlock*>($1.else_bb);
      llvm::BasicBlock* mergeBB = static_cast<llvm::BasicBlock*>($1.merge_bb);
      
      if (!builder->GetInsertBlock()->getTerminator())
      {
        builder->CreateBr(mergeBB);
      }
      
      llvm::Function* func = builder->GetInsertBlock()->getParent();
      elseBB->insertInto(func);
      
      builder->SetInsertPoint(elseBB);
      
      llvm::BasicBlock* elseBodyBB = llvm::BasicBlock::Create(context, "else.body", func);
      builder->CreateBr(elseBodyBB);
      builder->SetInsertPoint(elseBodyBB);
      
      $$ = (void*)mergeBB;
    }
;

if_statement:
    if_then_part
    {
      llvm::BasicBlock* mergeBB = static_cast<llvm::BasicBlock*>($1);
      
      if (!builder->GetInsertBlock()->getTerminator())
      {
        builder->CreateBr(mergeBB);
      }
      
      llvm::Function* func = builder->GetInsertBlock()->getParent();
      mergeBB->insertInto(func);
      
      builder->SetInsertPoint(mergeBB);
    }
  | if_then_part ELSE LBRACE block RBRACE
    {
      llvm::BasicBlock* mergeBB = static_cast<llvm::BasicBlock*>($1);
      
      llvm::Function* func = builder->GetInsertBlock()->getParent();
      llvm::BasicBlock* elseBodyBB = llvm::BasicBlock::Create(context, "else.body", func);
      
      if (!builder->GetInsertBlock()->getTerminator())
      {
        builder->CreateBr(elseBodyBB);
      }
      
      builder->SetInsertPoint(elseBodyBB);
      
      if (!builder->GetInsertBlock()->getTerminator())
      {
        builder->CreateBr(mergeBB);
      }
      
      mergeBB->insertInto(func);
      builder->SetInsertPoint(mergeBB);
    }
  | if_then_part ELSE if_statement
    {
      $$ = $3;
    }
;

while_start:
    WHILE LPAREN
    {
      llvm::Function* func = builder->GetInsertBlock()->getParent();
      
      llvm::BasicBlock* entryBB = builder->GetInsertBlock();
      llvm::BasicBlock* condBB = llvm::BasicBlock::Create(context, "while.cond", func);
      llvm::BasicBlock* bodyBB = llvm::BasicBlock::Create(context, "while.body", func);
      llvm::BasicBlock* afterBB = llvm::BasicBlock::Create(context, "while.end", func);
      
      BreakTargets.push_back(afterBB);
      builder->CreateBr(condBB);
      builder->SetInsertPoint(condBB);
      
      $$.cond_bb = (void*)condBB;
      $$.body_bb = (void*)bodyBB;
      $$.after_bb = (void*)afterBB;
    }
;

while_condition:
    while_start expression RPAREN
    {
      llvm::Value* cond = static_cast<llvm::Value*>($2);
      llvm::BasicBlock* bodyBB = static_cast<llvm::BasicBlock*>($1.body_bb);
      llvm::BasicBlock* afterBB = static_cast<llvm::BasicBlock*>($1.after_bb);
      
      if(cond->getType() != llvm::Type::getInt1Ty(context))
      {
        cond = builder->CreateICmpNE(cond, llvm::ConstantInt::get(cond->getType(), 0), "whilecond");
      }
      
      builder->CreateCondBr(cond, bodyBB, afterBB);
      
      builder->SetInsertPoint(bodyBB);
      
      $$.cond_bb = $1.cond_bb;
      $$.body_bb = $1.body_bb;
      $$.after_bb = $1.after_bb;
    }
;

while_statement:
    while_condition LBRACE block RBRACE
    {
      llvm::BasicBlock* condBB = static_cast<llvm::BasicBlock*>($1.cond_bb);
      llvm::BasicBlock* afterBB = static_cast<llvm::BasicBlock*>($1.after_bb);
      
      if (!builder->GetInsertBlock()->getTerminator())
      {
          builder->CreateBr(condBB);
      }
      
      builder->SetInsertPoint(afterBB);
      
      BreakTargets.pop_back();
      
      $$ = (void*)afterBB;
    }
;

for_start:
    FOR INT IDENTIFIER ASSIGN expression TO expression COMMA expression
    {
      $$.var_name = strdup($3);
      $$.init_val = (void*)$5;
      $$.end_val  = (void*)$7;
      $$.step_val = (void*)$9;

      $$.cond_bb  = nullptr;
      $$.body_bb  = nullptr;
      $$.inc_bb   = nullptr;
      $$.after_bb = nullptr;
    }
;

for_header:
    for_start
    {
      llvm::Function *func = builder->GetInsertBlock()->getParent();

      llvm::BasicBlock *condBB  = llvm::BasicBlock::Create(context, "for.cond", func);
      llvm::BasicBlock *bodyBB  = llvm::BasicBlock::Create(context, "for.body", func);
      llvm::BasicBlock *incBB   = llvm::BasicBlock::Create(context, "for.inc",  func);
      llvm::BasicBlock *afterBB = llvm::BasicBlock::Create(context, "for.end",  func);

      llvm::AllocaInst *varAlloc = builder->CreateAlloca(builder->getInt32Ty(), nullptr, $1.var_name);

      builder->CreateStore((llvm::Value*)$1.init_val, varAlloc);

      builder->CreateBr(condBB);
      builder->SetInsertPoint(condBB);

      $$.var_name = $1.var_name;
      $$.init_val = $1.init_val;
      $$.end_val  = $1.end_val;
      $$.step_val = $1.step_val;

      $$.cond_bb  = (void*)condBB;
      $$.body_bb  = (void*)bodyBB;
      $$.inc_bb   = (void*)incBB;
      $$.after_bb = (void*)afterBB;

      symbolTable[$1.var_name] = varAlloc;
    }
;

for_statement:
    for_header
    {
      auto *condBB   = static_cast<llvm::BasicBlock*>($1.cond_bb);
      auto *bodyBB   = static_cast<llvm::BasicBlock*>($1.body_bb);
      auto *incBB    = static_cast<llvm::BasicBlock*>($1.inc_bb);
      auto *afterBB  = static_cast<llvm::BasicBlock*>($1.after_bb);

      llvm::AllocaInst *varAlloc = llvm::cast<llvm::AllocaInst>(symbolTable[$1.var_name]);

      llvm::Value *endVal  = static_cast<llvm::Value*>($1.end_val);
      llvm::Value *stepVal = static_cast<llvm::Value*>($1.step_val);

      builder->SetInsertPoint(condBB);
      llvm::Value *cur = builder->CreateLoad(varAlloc->getAllocatedType(), varAlloc, "for.load");

      bool positiveStep = true;
      if (auto *stepCI = llvm::dyn_cast<llvm::ConstantInt>(stepVal))
        positiveStep = stepCI->getSExtValue() >= 0;

      llvm::Value *exitCond = positiveStep ? builder->CreateICmpSGE(cur, endVal, "for.exit") : builder->CreateICmpSLE(cur, endVal, "for.exit");

      builder->CreateCondBr(exitCond, afterBB, bodyBB);
      builder->SetInsertPoint(bodyBB);
      BreakTargets.push_back(afterBB);
    }
    block
    {
      auto *incBB = static_cast<llvm::BasicBlock*>($1.inc_bb);
      if (!builder->GetInsertBlock()->getTerminator())
      {
        builder->CreateBr(incBB);
      }
    }
    END
    {
      auto *condBB  = static_cast<llvm::BasicBlock*>($1.cond_bb);
      auto *incBB   = static_cast<llvm::BasicBlock*>($1.inc_bb);
      auto *afterBB = static_cast<llvm::BasicBlock*>($1.after_bb);

      llvm::AllocaInst *varAlloc = llvm::cast<llvm::AllocaInst>(symbolTable[$1.var_name]);

      llvm::Value *stepVal = static_cast<llvm::Value*>($1.step_val);

      builder->SetInsertPoint(incBB);
      llvm::Value *next = builder->CreateAdd(builder->CreateLoad(varAlloc->getAllocatedType(), varAlloc), stepVal, "for.step");
      builder->CreateStore(next, varAlloc);
      builder->CreateBr(condBB);

      BreakTargets.pop_back();
      builder->SetInsertPoint(afterBB);
      
      llvm::Function* func = builder->GetInsertBlock()->getParent();
      llvm::BasicBlock* continueBB = llvm::BasicBlock::Create(context, "continue", func);
      
      if (!builder->GetInsertBlock()->getTerminator())
      {
        builder->CreateBr(continueBB);
      }
      
      builder->SetInsertPoint(continueBB);
      
      if (func == mainFunction)
      {
        mainBB = continueBB;
      }
      
      $$ = (void*)continueBB;
    }
;

break_statement:
    BREAK SEMICOLON
    {
      if(BreakTargets.empty())
      {
        yyerror("'break' used outside of any loop");
      }
      else
      {
        builder->CreateBr(BreakTargets.back());
        llvm::BasicBlock* cont =
        llvm::BasicBlock::Create(context, "after.break", builder->GetInsertBlock()->getParent());
        builder->SetInsertPoint(cont);
      }
    }
;

addsub_statement:
    IDENTIFIER ADDSUB SEMICOLON
    {
      auto* var = symbolTable[$1];
      if (!var)
      {
        yyerror("Undefined variable");
        exit(1);
      }
      llvm::PointerType *ptrType = llvm::dyn_cast<llvm::PointerType>(var->getType());
      if (!ptrType)
      {
        yyerror("Invalid pointer type");
        exit(1);
      }
      
      llvm::Value* currentVal = builder->CreateLoad(llvm::cast<llvm::AllocaInst>(var)->getAllocatedType(), var);
      llvm::Value* one = llvm::ConstantInt::get(currentVal->getType(), 1);
      llvm::Value* newVal;
      
      if($2 == INCREMENT)
      {
          newVal = builder->CreateAdd(currentVal, one, "increment");
      }
      else if($2 == DECREMENT)
      {
          newVal = builder->CreateSub(currentVal, one, "decrement");
      }
      
      builder->CreateStore(newVal, var);
      
      $$ = (void*)newVal;
      free($1);
    }
    ;

case_list:
  | case_list CASE literal LBRACE
    {
        auto caseVal = llvm::dyn_cast<llvm::ConstantInt>(static_cast<llvm::Value*>($3));
        auto *caseBB  = llvm::BasicBlock::Create(context, "switch.case", yy_func);

        yy_switch_inst->addCase(caseVal, caseBB);
        builder->SetInsertPoint(caseBB);
    }
    statements RBRACE
    {
        if (!builder->GetInsertBlock()->getTerminator())
        {
            builder->CreateBr(yy_end_bb);
        }
    }
  ;

switch_statement:
    SWITCH LPAREN expression RPAREN
    {
        llvm::Value* cond = static_cast<llvm::Value*>($3);
        yy_func = builder->GetInsertBlock()->getParent();
        yy_default_bb = llvm::BasicBlock::Create(context, "switch.default", yy_func);
        yy_end_bb = llvm::BasicBlock::Create(context, "switch.end",     yy_func);
        yy_switch_inst = builder->CreateSwitch(cond, yy_default_bb, 0);
    }
    LBRACE case_list DEFAULT LBRACE
    {
        builder->SetInsertPoint(yy_default_bb);
    }
    statements RBRACE
    {
        if (!builder->GetInsertBlock()->getTerminator())
        {
            builder->CreateBr(yy_end_bb);
        }
    }
    RBRACE
    {
        builder->SetInsertPoint(yy_end_bb);
    }
  ;

function_declaration:
    FUNCTION type IDENTIFIER LPAREN parameter_list RPAREN LBRACE
    {
      if (strcmp($3, "main") == 0)
      {
        yyerror("The main function is already defined.");
        exit(1);
      }
      returnType = static_cast<llvm::Type*>($2);
      auto* paramTs = static_cast<std::vector<llvm::Type*>*>($5.param_types);
      auto* paramNs = static_cast<std::vector<std::string>*>($5.param_names);

      llvm::FunctionType* fnTy = llvm::FunctionType::get(returnType, *paramTs, false);
      llvm::Function* fn = llvm::Function::Create(fnTy, llvm::Function::ExternalLinkage, $3, module);

      llvm::BasicBlock* entryBB = llvm::BasicBlock::Create(context, "entry", fn);
      builder->SetInsertPoint(entryBB);

      oldSymbolTable = symbolTable;
      symbolTable.clear();
      for (size_t i = 0; i < fn->arg_size(); ++i)
      {
        llvm::Argument& arg = *std::next(fn->arg_begin(), i);
        const std::string& name = paramNs->at(i);
        arg.setName(name);
        llvm::AllocaInst* alloc = builder->CreateAlloca(arg.getType(), nullptr, name);
        builder->CreateStore(&arg, alloc);
        symbolTable[name] = alloc;
      }

      delete paramTs;
      delete paramNs;
      free($3);
    }
    block RBRACE
    {
      if (!builder->GetInsertBlock()->getTerminator())
      {
        if (returnType->isVoidTy())
          builder->CreateRetVoid();
        else
          builder->CreateRet(llvm::Constant::getNullValue(returnType));
      }
      symbolTable = oldSymbolTable;
      builder->SetInsertPoint(mainBB);
    }
  ;

parameter_list:
    {
        $$.param_types = new std::vector<llvm::Type*>();
        $$.param_names = new std::vector<std::string>();
    }
    | type IDENTIFIER
    {
        $$.param_types = new std::vector<llvm::Type*>();
        $$.param_names = new std::vector<std::string>();
        static_cast<std::vector<llvm::Type*>*>($$.param_types)->push_back(static_cast<llvm::Type*>($1));
        static_cast<std::vector<std::string>*>($$.param_names)->push_back($2);
        free($2);
    }
    | parameter_list COMMA type IDENTIFIER
    {
        $$.param_types = $1.param_types;
        $$.param_names = $1.param_names;
        static_cast<std::vector<llvm::Type*>*>($$.param_types)->push_back(static_cast<llvm::Type*>($3));
        static_cast<std::vector<std::string>*>($$.param_names)->push_back($4);
        free($4);
    }
    ;

function_call:
    IDENTIFIER LPAREN argument_list RPAREN
    {
        $$.name = $1;
        $$.args = $3.args;
    }
    ;

argument_list:
    {
        $$.args = new std::vector<llvm::Value*>();
    }
    | expression
    {
        $$.args = new std::vector<llvm::Value*>();
        static_cast<std::vector<llvm::Value*>*>($$.args)->push_back(static_cast<llvm::Value*>($1));
    }
    | argument_list COMMA expression
    {
        $$.args = $1.args;
        static_cast<std::vector<llvm::Value*>*>($$.args)->push_back(static_cast<llvm::Value*>($3));
    }
    ;

return_statement:
    RETURN expression SEMICOLON
    {
        llvm::Value* retVal = static_cast<llvm::Value*>($2);
        llvm::Function* currentFunc = builder->GetInsertBlock()->getParent();
        llvm::Type* retType = currentFunc->getReturnType();

        if (retVal->getType() != retType)
        {
            if (retType->isIntegerTy(32) && retVal->getType()->isIntegerTy(8))
            {
                retVal = builder->CreateZExt(retVal, retType, "ret_ext");
            } 
            else if (retType->isIntegerTy(8) && retVal->getType()->isIntegerTy(32))
            {
                retVal = builder->CreateTrunc(retVal, retType, "ret_trunc");
            }
        }

        builder->CreateRet(retVal);
        $$ = (void*)retVal;
    }
  | RETURN SEMICOLON
    {
        llvm::Function* currentFunc = builder->GetInsertBlock()->getParent();
        if (!currentFunc->getReturnType()->isVoidTy()) {
            yyerror("Non-void function must return a value");
            exit(1);
        }
        builder->CreateRetVoid();
        $$ = nullptr;
    }
    ;

function_call_statement:
    function_call SEMICOLON
    {
        auto* func = module->getFunction($1.name);
        if (!func)
        {
            yyerror("Undefined function");
            exit(1);
        }
        
        auto* args = static_cast<std::vector<llvm::Value*>*>($1.args);
        std::vector<llvm::Value*> callArgs;
        for (auto* arg : *args)
        {
            callArgs.push_back(static_cast<llvm::Value*>(arg));
        }
        
        if (func->getReturnType()->isVoidTy())
        {
            builder->CreateCall(func, callArgs);
        }
        else
        {
            builder->CreateCall(func, callArgs, "calltmp");
        }
        
        delete args;
        free($1.name);
    }
    ;

dyn_allocation:
    DYN LPAREN STRING_LITERAL RPAREN
    {
        llvm::Type* allocTy;
        if (strcmp($3, "number") == 0)
        {
            allocTy = builder->getInt32Ty();
        } else if (strcmp($3, "letter") == 0)
        {
            allocTy = builder->getInt8Ty();
        }
        else
        {
            yyerror("Invalid type in dyn allocation. Use 'number' or 'letter'");
            exit(1);
        }

        llvm::Value* size;
        if (allocTy == builder->getInt32Ty())
        {
            size = llvm::ConstantInt::get(builder->getInt32Ty(), 4);
        }
        else
        {
            size = llvm::ConstantInt::get(builder->getInt32Ty(), 1);
        }

        llvm::Function* mallocFunc = module->getFunction("malloc");
        if (!mallocFunc)
        {
            std::vector<llvm::Type*> mallocArgs;
            mallocArgs.push_back(builder->getInt32Ty());
            llvm::FunctionType* mallocType = llvm::FunctionType::get(llvm::PointerType::get(builder->getInt8Ty(), 0), mallocArgs, false);
            mallocFunc = llvm::Function::Create(mallocType, llvm::Function::ExternalLinkage, "malloc", module);
        }

        llvm::Value* ptr = builder->CreateCall(mallocFunc, size, "malloccall");
        llvm::Value* typedPtr = builder->CreateBitCast(ptr, llvm::PointerType::get(allocTy, 0), "castptr");
        llvm::Value* zeroVal = llvm::ConstantInt::get(allocTy, 0);
        builder->CreateStore(zeroVal, typedPtr);
        $$ = (void*)typedPtr;
        free($3);
    }
  | DYN LPAREN STRING_LITERAL COMMA expression RPAREN
    {
        llvm::Type* allocTy;
        if (strcmp($3, "number") == 0)
        {
            allocTy = builder->getInt32Ty();
        }
        else if (strcmp($3, "letter") == 0)
        {
            allocTy = builder->getInt8Ty();
        }
        else
        {
            yyerror("Invalid type in dyn allocation. Use 'number' or 'letter'");
            exit(1);
        }

        llvm::Value* initVal = static_cast<llvm::Value*>($5);
        if (initVal->getType() != allocTy)
        {
            yyerror("Initialization type mismatch in dyn allocation");
            exit(1);
        }

        llvm::Value* size;
        if (allocTy == builder->getInt32Ty())
        {
            size = llvm::ConstantInt::get(builder->getInt32Ty(), 4);
        }
        else
        {
            size = llvm::ConstantInt::get(builder->getInt32Ty(), 1);
        }

        llvm::Function* mallocFunc = module->getFunction("malloc");
        if (!mallocFunc)
        {
            std::vector<llvm::Type*> mallocArgs;
            mallocArgs.push_back(builder->getInt32Ty());
            llvm::FunctionType* mallocType = llvm::FunctionType::get(llvm::PointerType::get(builder->getInt8Ty(), 0), mallocArgs, false);
            mallocFunc = llvm::Function::Create(mallocType, llvm::Function::ExternalLinkage, "malloc", module);
        }

        llvm::Value* ptr = builder->CreateCall(mallocFunc, size, "malloccall");
        llvm::Value* typedPtr = builder->CreateBitCast(ptr, llvm::PointerType::get(allocTy, 0), "castptr");
        builder->CreateStore(initVal, typedPtr);
        $$ = (void*)typedPtr;
        free($3);
    }
    ;

%%

void yyerror(const char *s)
{
  fprintf(stderr, "Error: %s\n", s);
}