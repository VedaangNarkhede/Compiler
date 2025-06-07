/* A Bison parser, made by GNU Bison 2.7.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2012 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.7"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
/* Line 371 of yacc.c  */
#line 1 "proj.y"

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
/* Line 371 of yacc.c  */
#line 37 "proj.y"

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

/* Line 371 of yacc.c  */
#line 133 "proj.tab.c"

# ifndef YY_NULL
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULL nullptr
#  else
#   define YY_NULL 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "proj.tab.h".  */
#ifndef YY_YY_PROJ_TAB_H_INCLUDED
# define YY_YY_PROJ_TAB_H_INCLUDED
/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     NUMBER = 258,
     CHAR_LITERAL = 259,
     STRING_LITERAL = 260,
     IDENTIFIER = 261,
     INT = 262,
     CHAR = 263,
     ASSIGN = 264,
     STRING = 265,
     SEMICOLON = 266,
     PRINT = 267,
     LPAREN = 268,
     RPAREN = 269,
     LBRACKET = 270,
     RBRACKET = 271,
     COMMA = 272,
     IF = 273,
     ELSE = 274,
     LESSTHAN = 275,
     GREATERTHAN = 276,
     EQUAL = 277,
     NOTEQUAL = 278,
     LBRACE = 279,
     RBRACE = 280,
     END = 281,
     WHILE = 282,
     LESSEQUAL = 283,
     GREATEREQUAL = 284,
     BREAK = 285,
     OPERATOR = 286,
     PLUS = 287,
     MINUS = 288,
     MUL = 289,
     DIV = 290,
     ADDSUB = 291,
     INCREMENT = 292,
     DECREMENT = 293,
     AND = 294,
     OR = 295,
     PTR = 296,
     AMPERSAND = 297,
     SWITCH = 298,
     CASE = 299,
     DEFAULT = 300,
     FOR = 301,
     TO = 302,
     STEP = 303,
     FUNCTION = 304,
     RETURN = 305,
     VOID = 306,
     DYN = 307,
     STRUCT = 308,
     DOT = 309
   };
#endif


#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{
/* Line 387 of yacc.c  */
#line 67 "proj.y"

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


/* Line 387 of yacc.c  */
#line 295 "proj.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */

#endif /* !YY_YY_PROJ_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

/* Line 390 of yacc.c  */
#line 323 "proj.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(N) (N)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   314

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  55
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  44
/* YYNRULES -- Number of rules.  */
#define YYNRULES  103
/* YYNRULES -- Number of states.  */
#define YYNSTATES  224

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   309

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     7,     9,    10,    11,    12,    15,    17,
      19,    21,    23,    25,    27,    29,    31,    33,    35,    37,
      39,    41,    43,    45,    47,    49,    51,    54,    61,    62,
      67,    74,    81,    87,    93,    99,   103,   109,   115,   121,
     128,   134,   140,   146,   149,   152,   157,   162,   164,   167,
     169,   171,   174,   176,   180,   182,   184,   189,   192,   196,
     200,   204,   209,   217,   223,   228,   235,   240,   247,   252,
     257,   259,   265,   269,   272,   276,   281,   291,   293,   294,
     295,   301,   304,   308,   309,   310,   318,   319,   320,   321,
     336,   337,   348,   349,   352,   357,   362,   363,   365,   369,
     373,   376,   379,   384
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      56,     0,    -1,    58,    60,    59,    -1,    60,    -1,    -1,
      -1,    -1,    60,    61,    -1,    66,    -1,    71,    -1,    65,
      -1,    74,    -1,    77,    -1,    84,    -1,    83,    -1,    80,
      -1,    87,    -1,    91,    -1,    96,    -1,    97,    -1,    63,
      -1,     7,    -1,     8,    -1,    10,    -1,    41,    -1,    51,
      -1,    53,     6,    -1,    53,     6,    24,    64,    25,    11,
      -1,    -1,    64,    62,     6,    11,    -1,    64,    62,     6,
       9,    69,    11,    -1,    64,    62,     6,     9,     5,    11,
      -1,    12,    13,    70,    14,    11,    -1,    12,    13,     5,
      14,    11,    -1,    12,    13,    68,    14,    11,    -1,    62,
       6,    11,    -1,    62,     6,     9,    69,    11,    -1,    62,
       6,     9,     5,    11,    -1,    62,     6,     9,    70,    11,
      -1,    62,     6,    15,     3,    16,    11,    -1,    62,     6,
       9,    67,    11,    -1,    62,     6,     9,    68,    11,    -1,
      62,     6,     9,    98,    11,    -1,    42,     6,    -1,    31,
      70,    -1,    31,    70,    31,    70,    -1,    31,    70,    31,
       3,    -1,     3,    -1,    33,     3,    -1,     4,    -1,    69,
      -1,    33,     3,    -1,     6,    -1,     6,    54,     6,    -1,
      68,    -1,    94,    -1,     6,    15,    70,    16,    -1,     6,
      36,    -1,    70,    39,    70,    -1,    70,    40,    70,    -1,
      70,    31,    70,    -1,     6,     9,    70,    11,    -1,     6,
      15,    70,    16,     9,    70,    11,    -1,    31,    70,     9,
      70,    11,    -1,     6,     9,    67,    11,    -1,     6,    54,
       6,     9,    70,    11,    -1,     6,     9,     5,    11,    -1,
       6,    54,     6,     9,     5,    11,    -1,    18,    13,    70,
      14,    -1,    72,    24,    57,    25,    -1,    73,    -1,    73,
      19,    24,    57,    25,    -1,    73,    19,    74,    -1,    27,
      13,    -1,    75,    70,    14,    -1,    76,    24,    57,    25,
      -1,    46,     7,     6,     9,    70,    47,    70,    17,    70,
      -1,    78,    -1,    -1,    -1,    79,    81,    57,    82,    26,
      -1,    30,    11,    -1,     6,    36,    11,    -1,    -1,    -1,
      85,    44,    69,    24,    86,    60,    25,    -1,    -1,    -1,
      -1,    43,    13,    70,    14,    88,    24,    85,    45,    24,
      89,    60,    25,    90,    25,    -1,    -1,    49,    62,     6,
      13,    93,    14,    24,    92,    57,    25,    -1,    -1,    62,
       6,    -1,    93,    17,    62,     6,    -1,     6,    13,    95,
      14,    -1,    -1,    70,    -1,    95,    17,    70,    -1,    50,
      70,    11,    -1,    50,    11,    -1,    94,    11,    -1,    52,
      13,     5,    14,    -1,    52,    13,     5,    17,    70,    14,
      -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   169,   169,   175,   182,   188,   198,   199,   203,   204,
     205,   206,   207,   208,   209,   210,   211,   212,   213,   214,
     215,   219,   220,   221,   222,   223,   224,   237,   277,   281,
     298,   310,   326,   392,   410,   437,   478,   496,   508,   536,
     545,   555,   572,   594,   621,   654,   703,   753,   754,   755,
     759,   760,   761,   788,   824,   829,   859,   912,   945,   963,
     980,  1123,  1156,  1208,  1228,  1248,  1285,  1301,  1342,  1366,
    1391,  1405,  1427,  1434,  1454,  1476,  1495,  1510,  1542,  1567,
    1541,  1612,  1629,  1664,  1666,  1665,  1684,  1692,  1696,  1683,
    1710,  1709,  1757,  1761,  1769,  1780,  1788,  1791,  1796,  1804,
    1825,  1838,  1869,  1911
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "NUMBER", "CHAR_LITERAL",
  "STRING_LITERAL", "IDENTIFIER", "INT", "CHAR", "ASSIGN", "STRING",
  "SEMICOLON", "PRINT", "LPAREN", "RPAREN", "LBRACKET", "RBRACKET",
  "COMMA", "IF", "ELSE", "LESSTHAN", "GREATERTHAN", "EQUAL", "NOTEQUAL",
  "LBRACE", "RBRACE", "END", "WHILE", "LESSEQUAL", "GREATEREQUAL", "BREAK",
  "OPERATOR", "PLUS", "MINUS", "MUL", "DIV", "ADDSUB", "INCREMENT",
  "DECREMENT", "AND", "OR", "PTR", "AMPERSAND", "SWITCH", "CASE",
  "DEFAULT", "FOR", "TO", "STEP", "FUNCTION", "RETURN", "VOID", "DYN",
  "STRUCT", "DOT", "$accept", "program", "block", "init_main", "fini_main",
  "statements", "statement", "type", "structure_definition",
  "field_declarations", "print_statement", "declaration", "pointer_exp",
  "pointer_retrieve", "literal", "expression", "assignment",
  "if_condition", "if_then_part", "if_statement", "while_start",
  "while_condition", "while_statement", "for_start", "for_header",
  "for_statement", "$@1", "$@2", "break_statement", "addsub_statement",
  "case_list", "$@3", "switch_statement", "$@4", "$@5", "$@6",
  "function_declaration", "$@7", "parameter_list", "function_call",
  "argument_list", "return_statement", "function_call_statement",
  "dyn_allocation", YY_NULL
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    55,    56,    57,    58,    59,    60,    60,    61,    61,
      61,    61,    61,    61,    61,    61,    61,    61,    61,    61,
      61,    62,    62,    62,    62,    62,    62,    63,    64,    64,
      64,    64,    65,    65,    65,    66,    66,    66,    66,    66,
      66,    66,    66,    67,    68,    68,    68,    69,    69,    69,
      70,    70,    70,    70,    70,    70,    70,    70,    70,    70,
      70,    71,    71,    71,    71,    71,    71,    71,    72,    73,
      74,    74,    74,    75,    76,    77,    78,    79,    81,    82,
      80,    83,    84,    85,    86,    85,    88,    89,    90,    87,
      92,    91,    93,    93,    93,    94,    95,    95,    95,    96,
      96,    97,    98,    98
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     3,     1,     0,     0,     0,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     6,     0,     4,
       6,     6,     5,     5,     5,     3,     5,     5,     5,     6,
       5,     5,     5,     2,     2,     4,     4,     1,     2,     1,
       1,     2,     1,     3,     1,     1,     4,     2,     3,     3,
       3,     4,     7,     5,     4,     6,     4,     6,     4,     4,
       1,     5,     3,     2,     3,     4,     9,     1,     0,     0,
       5,     2,     3,     0,     0,     7,     0,     0,     0,    14,
       0,    10,     0,     2,     4,     4,     0,     1,     3,     3,
       2,     2,     4,     6
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       4,     0,     6,     1,     5,     0,    21,    22,    23,     0,
       0,     0,     0,     0,    24,     0,     0,     0,     0,    25,
       0,     2,     7,     0,    20,    10,     8,     9,     0,    70,
      11,     0,     0,    12,    77,    78,    15,    14,    13,    16,
      17,     0,    18,    19,     0,    96,     0,     0,     0,     0,
       0,    73,    81,    47,    49,    52,     0,     0,    54,    50,
       0,    55,     0,     0,     0,     0,   100,     0,    26,     0,
       6,     0,     0,     6,     6,   101,     0,     0,     0,     0,
      97,     0,     0,    82,     0,     0,    54,     0,     0,     0,
      57,     0,    44,    48,     0,     0,     0,     0,     0,     0,
      26,     0,    99,    28,     0,    35,     0,     0,     3,     6,
      72,    74,     0,    79,    66,    43,    64,    61,    95,     0,
       0,     0,     0,     0,     0,    68,     0,    53,     0,     0,
      60,    58,    59,    86,     0,    92,     0,     0,     0,     0,
      54,    50,     0,     0,     0,    69,     0,    75,     0,    98,
       0,     0,     0,    33,    34,    32,    56,    46,    45,    63,
       0,     0,     0,     0,     0,     0,    37,     0,    40,    41,
      36,    38,    42,     0,    71,    80,     0,    67,    65,    83,
       0,    93,     0,     0,    27,     0,     0,    39,    62,     0,
       0,    90,     0,     0,    29,   102,     0,     0,     0,     0,
       6,    94,     0,     0,     0,     0,     0,    87,    76,     0,
      31,    48,    30,   103,    84,     6,    91,     6,     0,     0,
      88,    85,     0,    89
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,   107,     2,    21,   108,    22,    23,    24,   136,
      25,    26,    78,    58,    59,    60,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    74,   148,    37,    38,
     189,   217,    39,   160,   215,   222,    40,   200,   163,    61,
      81,    42,    43,   143
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -104
static const yytype_int16 yypact[] =
{
    -104,    25,  -104,  -104,   190,    30,  -104,  -104,  -104,    31,
      36,    41,    26,   223,  -104,    62,    52,    14,   201,  -104,
      47,  -104,  -104,   100,  -104,  -104,  -104,  -104,    83,    94,
    -104,   223,    95,  -104,  -104,  -104,  -104,  -104,  -104,  -104,
    -104,   115,  -104,  -104,   124,   223,   223,   126,   132,   168,
     223,  -104,  -104,  -104,  -104,    35,   223,   139,  -104,  -104,
      43,  -104,   223,   143,   145,   147,  -104,   136,   130,    61,
    -104,    40,    46,  -104,  -104,  -104,   148,   152,   167,   224,
      -8,     2,   146,  -104,   173,   176,   178,    85,   121,   223,
    -104,   187,   249,  -104,   223,   223,   223,   223,   244,   185,
    -104,   182,  -104,  -104,     5,  -104,   200,   181,   190,  -104,
    -104,  -104,   184,  -104,  -104,  -104,  -104,  -104,  -104,   223,
     202,   219,   199,   208,   217,  -104,   263,  -104,   241,   226,
      -8,    -8,    -8,  -104,   223,    14,    10,   227,   233,   238,
     258,   274,   231,   279,   197,  -104,   205,  -104,   265,    -8,
     223,   281,   237,  -104,  -104,  -104,  -104,  -104,    -8,  -104,
     269,   220,   289,    78,   285,   291,  -104,   293,  -104,  -104,
    -104,  -104,  -104,   288,  -104,  -104,   242,  -104,  -104,  -104,
     223,  -104,   276,    14,  -104,    82,    97,  -104,  -104,    24,
      70,  -104,   295,     9,  -104,  -104,   223,    23,   280,   223,
    -104,  -104,   294,   303,   296,   247,   284,  -104,    -8,   286,
    -104,  -104,  -104,  -104,  -104,  -104,  -104,  -104,    90,   138,
    -104,  -104,   287,  -104
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -104,  -104,   -68,  -104,  -104,     1,  -104,   -13,  -104,  -104,
    -104,  -104,   206,   -42,  -103,   -16,  -104,  -104,  -104,   243,
    -104,  -104,  -104,  -104,  -104,  -104,  -104,  -104,  -104,  -104,
    -104,  -104,  -104,  -104,  -104,  -104,  -104,  -104,  -104,    -4,
    -104,  -104,  -104,  -104
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      41,   141,    67,     4,    65,   112,   113,    86,    53,    54,
     137,    55,    53,    54,   202,    72,   118,     6,     7,   119,
       8,     6,     7,    95,     8,     3,    53,    54,    79,    80,
      82,    96,    97,    87,    88,   164,    56,    52,    57,    44,
      92,   146,   203,    45,    49,    46,    98,    77,    45,    50,
      89,    14,    94,    68,    51,    14,   203,   138,    10,    63,
     111,    19,   140,    64,   109,    19,    47,    64,   197,   198,
     104,    90,   105,   126,    95,    62,   106,    95,   129,   130,
     131,   132,    96,    97,    48,    96,    97,   199,   142,    91,
     204,   193,   182,   194,   206,   183,     5,     6,     7,   124,
       8,    95,     9,   149,    41,   152,    69,    70,    10,    96,
      97,   195,   158,    71,   196,   220,    95,    11,   161,    73,
      12,    13,   162,   165,    96,    97,    75,    53,    54,    76,
      55,    14,   209,    15,   176,   125,    16,    83,    84,    17,
      18,    19,    93,    20,     5,     6,     7,   102,     8,    99,
       9,   100,    95,   101,   103,    56,    10,    57,   115,   114,
      96,    97,   120,   221,   190,    11,    77,    95,    12,    13,
     192,    53,    54,    85,    55,    96,    97,    95,   116,    14,
     205,    15,   121,   208,    16,    96,    97,    17,    18,    19,
     122,    20,   123,   127,   134,   135,     5,     6,     7,    56,
       8,    57,     9,   144,    53,    54,   145,    55,    10,   147,
     153,   150,    66,   173,    41,    41,   218,    11,   219,   154,
      12,    13,    53,    54,   151,    55,    53,    54,   155,    55,
     174,    14,    56,    15,    57,   117,    16,   159,   166,    17,
      18,    19,   171,    20,   157,    54,   167,    55,   178,   168,
      56,    95,    57,   188,    56,    95,    57,    95,   133,    96,
      97,   213,    95,    96,    97,    96,    97,   180,    95,   169,
      96,    97,    56,    95,    57,    95,    96,    97,    95,   156,
     128,    96,    97,    96,    97,   170,    96,    97,    96,    97,
     172,   175,   177,   179,    95,   181,   184,   185,   186,   187,
     191,   201,    96,    97,   207,   210,   211,   212,   214,     0,
     139,   216,   223,     0,   110
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-104)))

#define yytable_value_is_error(Yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
       4,   104,    18,     2,    17,    73,    74,    49,     3,     4,
       5,     6,     3,     4,     5,    31,    14,     7,     8,    17,
      10,     7,     8,    31,    10,     0,     3,     4,    44,    45,
      46,    39,    40,    49,    50,    25,    31,    11,    33,     9,
      56,   109,    33,    13,    13,    15,    62,    42,    13,    13,
      15,    41,     9,     6,    13,    41,    33,    52,    18,     7,
      14,    51,   104,    53,    24,    51,    36,    53,    44,    45,
       9,    36,    11,    89,    31,    13,    15,    31,    94,    95,
      96,    97,    39,    40,    54,    39,    40,    17,   104,    54,
     193,     9,    14,    11,   197,    17,     6,     7,     8,    14,
      10,    31,    12,   119,   108,   121,     6,    24,    18,    39,
      40,    14,   128,    19,    17,    25,    31,    27,   134,    24,
      30,    31,   135,   136,    39,    40,    11,     3,     4,     5,
       6,    41,   200,    43,   150,    14,    46,    11,     6,    49,
      50,    51,     3,    53,     6,     7,     8,    11,    10,     6,
      12,     6,    31,     6,    24,    31,    18,    33,     6,    11,
      39,    40,    16,    25,   180,    27,    42,    31,    30,    31,
     183,     3,     4,     5,     6,    39,    40,    31,    11,    41,
     196,    43,     9,   199,    46,    39,    40,    49,    50,    51,
      14,    53,    14,     6,     9,    13,     6,     7,     8,    31,
      10,    33,    12,     3,     3,     4,    25,     6,    18,    25,
      11,     9,    11,    16,   218,   219,   215,    27,   217,    11,
      30,    31,     3,     4,     5,     6,     3,     4,    11,     6,
      25,    41,    31,    43,    33,    11,    46,    11,    11,    49,
      50,    51,    11,    53,     3,     4,    13,     6,    11,    11,
      31,    31,    33,    11,    31,    31,    33,    31,    14,    39,
      40,    14,    31,    39,    40,    39,    40,    47,    31,    11,
      39,    40,    31,    31,    33,    31,    39,    40,    31,    16,
      31,    39,    40,    39,    40,    11,    39,    40,    39,    40,
      11,    26,    11,    24,    31,     6,    11,     6,     5,    11,
      24,     6,    39,    40,    24,    11,     3,    11,    24,    -1,
     104,    25,    25,    -1,    71
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    56,    58,     0,    60,     6,     7,     8,    10,    12,
      18,    27,    30,    31,    41,    43,    46,    49,    50,    51,
      53,    59,    61,    62,    63,    65,    66,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    83,    84,    87,
      91,    94,    96,    97,     9,    13,    15,    36,    54,    13,
      13,    13,    11,     3,     4,     6,    31,    33,    68,    69,
      70,    94,    13,     7,    53,    62,    11,    70,     6,     6,
      24,    19,    70,    24,    81,    11,     5,    42,    67,    70,
      70,    95,    70,    11,     6,     5,    68,    70,    70,    15,
      36,    54,    70,     3,     9,    31,    39,    40,    70,     6,
       6,     6,    11,    24,     9,    11,    15,    57,    60,    24,
      74,    14,    57,    57,    11,     6,    11,    11,    14,    17,
      16,     9,    14,    14,    14,    14,    70,     6,    31,    70,
      70,    70,    70,    14,     9,    13,    64,     5,    52,    67,
      68,    69,    70,    98,     3,    25,    57,    25,    82,    70,
       9,     5,    70,    11,    11,    11,    16,     3,    70,    11,
      88,    70,    62,    93,    25,    62,    11,    13,    11,    11,
      11,    11,    11,    16,    25,    26,    70,    11,    11,    24,
      47,     6,    14,    17,    11,     6,     5,    11,    11,    85,
      70,    24,    62,     9,    11,    14,    17,    44,    45,    17,
      92,     6,     5,    33,    69,    70,    69,    24,    70,    57,
      11,     3,    11,    14,    24,    89,    25,    86,    60,    60,
      25,    25,    90,    25
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))

/* Error token number */
#define YYTERROR	1
#define YYERRCODE	256


/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */
#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
        break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULL, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULL;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULL, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
        break;
    }
}




/* The lookahead symbol.  */
int yychar;


#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval YY_INITIAL_VALUE(yyval_default);

/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
/* Line 1792 of yacc.c  */
#line 170 "proj.y"
    {
      // No need to add return here as it's handled in fini_main
    }
    break;

  case 3:
/* Line 1792 of yacc.c  */
#line 176 "proj.y"
    {
      // Just pass through the statements without adding fini_main
    }
    break;

  case 4:
/* Line 1792 of yacc.c  */
#line 182 "proj.y"
    { 
      initializeMain();
    }
    break;

  case 5:
/* Line 1792 of yacc.c  */
#line 188 "proj.y"
    {
      if (builder->GetInsertBlock()->getParent() == mainFunction) {
        llvm::BasicBlock* currentBB = builder->GetInsertBlock();
        if (!currentBB->getTerminator()) {
          builder->CreateRetVoid();
        }
      }
    }
    break;

  case 8:
/* Line 1792 of yacc.c  */
#line 203 "proj.y"
    { (yyval.llvm_ptr) = (yyvsp[(1) - (1)].llvm_ptr); }
    break;

  case 9:
/* Line 1792 of yacc.c  */
#line 204 "proj.y"
    { (yyval.llvm_ptr) = (yyvsp[(1) - (1)].llvm_ptr); }
    break;

  case 10:
/* Line 1792 of yacc.c  */
#line 205 "proj.y"
    { (yyval.llvm_ptr) = (yyvsp[(1) - (1)].llvm_ptr); }
    break;

  case 11:
/* Line 1792 of yacc.c  */
#line 206 "proj.y"
    { (yyval.llvm_ptr) = (yyvsp[(1) - (1)].llvm_ptr); }
    break;

  case 12:
/* Line 1792 of yacc.c  */
#line 207 "proj.y"
    { (yyval.llvm_ptr) = nullptr; }
    break;

  case 13:
/* Line 1792 of yacc.c  */
#line 208 "proj.y"
    { (yyval.llvm_ptr) = (yyvsp[(1) - (1)].llvm_ptr); }
    break;

  case 14:
/* Line 1792 of yacc.c  */
#line 209 "proj.y"
    { (yyval.llvm_ptr) = nullptr; }
    break;

  case 15:
/* Line 1792 of yacc.c  */
#line 210 "proj.y"
    { (yyval.llvm_ptr) = nullptr; }
    break;

  case 16:
/* Line 1792 of yacc.c  */
#line 211 "proj.y"
    { (yyval.llvm_ptr) = nullptr; }
    break;

  case 20:
/* Line 1792 of yacc.c  */
#line 215 "proj.y"
    { (yyval.llvm_ptr) = (yyvsp[(1) - (1)].llvm_ptr); }
    break;

  case 21:
/* Line 1792 of yacc.c  */
#line 219 "proj.y"
    { (yyval.llvm_ptr) = (void*)builder->getInt32Ty(); }
    break;

  case 22:
/* Line 1792 of yacc.c  */
#line 220 "proj.y"
    { (yyval.llvm_ptr) = (void*)builder->getInt8Ty(); }
    break;

  case 23:
/* Line 1792 of yacc.c  */
#line 221 "proj.y"
    { (yyval.llvm_ptr) = llvm::PointerType::get(llvm::Type::getInt8Ty(context), 0); }
    break;

  case 24:
/* Line 1792 of yacc.c  */
#line 222 "proj.y"
    { (yyval.llvm_ptr) = (void*)llvm::PointerType::get(llvm::Type::getInt8Ty(context), 0); temp = 1; }
    break;

  case 25:
/* Line 1792 of yacc.c  */
#line 223 "proj.y"
    { (yyval.llvm_ptr) = llvm::Type::getVoidTy(context); }
    break;

  case 26:
/* Line 1792 of yacc.c  */
#line 225 "proj.y"
    {
        std::string structName = (yyvsp[(2) - (2)].identifier);
        if (structTypes.find(structName) == structTypes.end()) {
          yyerror("Undefined structure type");
          exit(1);
        }
        (yyval.llvm_ptr) = (void*)structTypes[structName].first;
        free((yyvsp[(2) - (2)].identifier));
      }
    break;

  case 27:
/* Line 1792 of yacc.c  */
#line 238 "proj.y"
    {
        std::string structName = (yyvsp[(2) - (6)].identifier);
        if(structTypes.find(structName) != structTypes.end())
        {
            yyerror("Structure already defined");
            exit(1);
        }
        auto* fieldInfos = static_cast<std::vector<FieldInfo>*>((yyvsp[(4) - (6)].field_decls).field_types);
        auto* fieldNames = static_cast<std::vector<std::string>*>((yyvsp[(4) - (6)].field_decls).field_names);
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
        free((yyvsp[(2) - (6)].identifier));
        (yyval.llvm_ptr) = nullptr;
    }
    break;

  case 28:
/* Line 1792 of yacc.c  */
#line 277 "proj.y"
    {
      (yyval.field_decls).field_types = new std::vector<FieldInfo>();
      (yyval.field_decls).field_names = new std::vector<std::string>();
    }
    break;

  case 29:
/* Line 1792 of yacc.c  */
#line 282 "proj.y"
    {
      (yyval.field_decls).field_types = (yyvsp[(1) - (4)].field_decls).field_types;
      (yyval.field_decls).field_names = (yyvsp[(1) - (4)].field_decls).field_names;
      FieldInfo info;
      info.type = static_cast<llvm::Type*>((yyvsp[(2) - (4)].llvm_ptr));
      info.name = (yyvsp[(3) - (4)].identifier);
      if (info.type == llvm::PointerType::get(llvm::Type::getInt8Ty(context), 0)) {
        // For string type, initialize with null pointer
        info.initValue = llvm::ConstantPointerNull::get(llvm::cast<llvm::PointerType>(info.type));
      } else {
        info.initValue = llvm::ConstantInt::get(info.type, 0);
      }
      static_cast<std::vector<FieldInfo>*>((yyval.field_decls).field_types)->push_back(info);
      static_cast<std::vector<std::string>*>((yyval.field_decls).field_names)->push_back((yyvsp[(3) - (4)].identifier));
      free((yyvsp[(3) - (4)].identifier));
    }
    break;

  case 30:
/* Line 1792 of yacc.c  */
#line 299 "proj.y"
    {
      (yyval.field_decls).field_types = (yyvsp[(1) - (6)].field_decls).field_types;
      (yyval.field_decls).field_names = (yyvsp[(1) - (6)].field_decls).field_names;
      FieldInfo info;
      info.type = static_cast<llvm::Type*>((yyvsp[(2) - (6)].llvm_ptr));
      info.name = (yyvsp[(3) - (6)].identifier);
      info.initValue = static_cast<llvm::Value*>((yyvsp[(5) - (6)].llvm_ptr));
      static_cast<std::vector<FieldInfo>*>((yyval.field_decls).field_types)->push_back(info);
      static_cast<std::vector<std::string>*>((yyval.field_decls).field_names)->push_back((yyvsp[(3) - (6)].identifier));
      free((yyvsp[(3) - (6)].identifier));
    }
    break;

  case 31:
/* Line 1792 of yacc.c  */
#line 311 "proj.y"
    {
      (yyval.field_decls).field_types = (yyvsp[(1) - (6)].field_decls).field_types;
      (yyval.field_decls).field_names = (yyvsp[(1) - (6)].field_decls).field_names;
      FieldInfo info;
      info.type = static_cast<llvm::Type*>((yyvsp[(2) - (6)].llvm_ptr));
      info.name = (yyvsp[(3) - (6)].identifier);
      info.initValue = builder->CreateGlobalStringPtr((yyvsp[(5) - (6)].string));
      static_cast<std::vector<FieldInfo>*>((yyval.field_decls).field_types)->push_back(info);
      static_cast<std::vector<std::string>*>((yyval.field_decls).field_names)->push_back((yyvsp[(3) - (6)].identifier));
      free((yyvsp[(3) - (6)].identifier));
      free((yyvsp[(5) - (6)].string));
    }
    break;

  case 32:
/* Line 1792 of yacc.c  */
#line 327 "proj.y"
    {
      llvm::Value *exprVal = static_cast<llvm::Value*>((yyvsp[(3) - (5)].llvm_ptr));
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
    break;

  case 33:
/* Line 1792 of yacc.c  */
#line 393 "proj.y"
    {
      printf("%s\n", (yyvsp[(3) - (5)].string));
      free((yyvsp[(3) - (5)].string));
    
      llvm::Function *printfFunc = module->getFunction("printf");
      if(!printfFunc)
      {
        std::vector<llvm::Type*> printfArgs;
        printfArgs.push_back(llvm::PointerType::get(context, 0));
        llvm::FunctionType *printfType = llvm::FunctionType::get(builder->getInt32Ty(), printfArgs, true);
        printfFunc = llvm::Function::Create(printfType, llvm::Function::ExternalLinkage, "printf", module);
      }
    
      llvm::Value *formatStr = builder->CreateGlobalStringPtr("%s\n");
      llvm::Value *strVal = builder->CreateGlobalStringPtr((yyvsp[(3) - (5)].string));
      builder->CreateCall(printfFunc, { formatStr, strVal });
    }
    break;

  case 34:
/* Line 1792 of yacc.c  */
#line 411 "proj.y"
    {
      llvm::Value* loaded = static_cast<llvm::Value*>((yyvsp[(3) - (5)].llvm_ptr));
        
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
    break;

  case 35:
/* Line 1792 of yacc.c  */
#line 438 "proj.y"
    {
    auto* ty = static_cast<llvm::Type*>((yyvsp[(1) - (3)].llvm_ptr));
    llvm::AllocaInst* alloc = builder->CreateAlloca(ty, nullptr, (yyvsp[(2) - (3)].identifier));

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
    symbolTable[(yyvsp[(2) - (3)].identifier)] = alloc;
    printf("Allocated %s at %p\n", (yyvsp[(2) - (3)].identifier), (void*)alloc);
    free((yyvsp[(2) - (3)].identifier));
  }
    break;

  case 36:
/* Line 1792 of yacc.c  */
#line 479 "proj.y"
    {
      auto* ty = static_cast<llvm::Type*>((yyvsp[(1) - (5)].llvm_ptr));
      auto* val = static_cast<llvm::Value*>((yyvsp[(4) - (5)].llvm_ptr));
    
      llvm::AllocaInst* alloc = builder->CreateAlloca(ty, nullptr, (yyvsp[(2) - (5)].identifier));
      builder->CreateStore(val, alloc);
      symbolTable[(yyvsp[(2) - (5)].identifier)] = alloc;
    
      if(auto* ci = llvm::dyn_cast<llvm::ConstantInt>(val))
      {
        if (ty->isIntegerTy(32))
          printf("Initialized %s = %d at %p\n", (yyvsp[(2) - (5)].identifier), ci->getSExtValue(), (void*)alloc);
        else
          printf("Initialized %s = '%c' at %p\n", (yyvsp[(2) - (5)].identifier), (char)ci->getSExtValue(), (void*)alloc);
      }
      free((yyvsp[(2) - (5)].identifier));
    }
    break;

  case 37:
/* Line 1792 of yacc.c  */
#line 497 "proj.y"
    {
      auto* ty = static_cast<llvm::Type*>((yyvsp[(1) - (5)].llvm_ptr));
      llvm::Value* strVal = builder->CreateGlobalStringPtr((yyvsp[(4) - (5)].string));
      llvm::AllocaInst* alloc = builder->CreateAlloca(ty, nullptr, (yyvsp[(2) - (5)].identifier));
      builder->CreateStore(strVal, alloc);
      symbolTable[(yyvsp[(2) - (5)].identifier)] = alloc;
      stringVariables[(yyvsp[(2) - (5)].identifier)] = true;
      printf("Initialized %s = \"%s\" at %p\n", (yyvsp[(2) - (5)].identifier), (yyvsp[(4) - (5)].string), (void*)alloc);
      free((yyvsp[(2) - (5)].identifier));
      free((yyvsp[(4) - (5)].string));
    }
    break;

  case 38:
/* Line 1792 of yacc.c  */
#line 509 "proj.y"
    {
      auto *ty  = static_cast<llvm::Type*>((yyvsp[(1) - (5)].llvm_ptr));
      auto *val = static_cast<llvm::Value*>((yyvsp[(4) - (5)].llvm_ptr));

      if(ty->isPointerTy() && !val->getType()->isPointerTy())
      {
        yyerror("Right-hand side is not a pointer");
        exit(1);
      }
    
      llvm::AllocaInst* alloc = builder->CreateAlloca(ty, nullptr, (yyvsp[(2) - (5)].identifier));
      builder->CreateStore(val, alloc);
      symbolTable[(yyvsp[(2) - (5)].identifier)] = alloc;
    
      if (auto* ci = llvm::dyn_cast<llvm::ConstantInt>(val))
      {
        if (ty->isIntegerTy(32))
          printf("Initialized %s = %d at %p\n", (yyvsp[(2) - (5)].identifier), ci->getSExtValue(), (void*)alloc);
        else
          printf("Initialized %s = '%c' at %p\n", (char)ci->getSExtValue(), (void*)alloc);
      }
      else
      {
        printf("Initialized %s with a computed expression at %p\n", (yyvsp[(2) - (5)].identifier), (void*)alloc);
      }
      free((yyvsp[(2) - (5)].identifier));
    }
    break;

  case 39:
/* Line 1792 of yacc.c  */
#line 537 "proj.y"
    {
      auto* ty = static_cast<llvm::Type*>((yyvsp[(1) - (6)].llvm_ptr));
      llvm::ArrayType* arrayType = llvm::ArrayType::get(ty, (yyvsp[(4) - (6)].num));
      llvm::AllocaInst* alloc = builder->CreateAlloca(arrayType, nullptr, (yyvsp[(2) - (6)].identifier));
      symbolTable[(yyvsp[(2) - (6)].identifier)] = alloc;
      printf("Allocated array %s[%d] at %p\n", (yyvsp[(2) - (6)].identifier), (yyvsp[(4) - (6)].num), (void*)alloc);
      free((yyvsp[(2) - (6)].identifier));
    }
    break;

  case 40:
/* Line 1792 of yacc.c  */
#line 546 "proj.y"
    {
      llvm::Type* ty = static_cast<llvm::Type*>((yyvsp[(1) - (5)].llvm_ptr));
      llvm::Value* val = static_cast<llvm::Value*>((yyvsp[(4) - (5)].llvm_ptr));
      llvm::AllocaInst* alloc = builder->CreateAlloca(ty, nullptr, (yyvsp[(2) - (5)].identifier));
      builder->CreateStore(val, alloc);
      symbolTable[(yyvsp[(2) - (5)].identifier)] = alloc;
      printf("Initialized pointer %s at %p\n", (yyvsp[(2) - (5)].identifier), (void*)alloc);
      free((yyvsp[(2) - (5)].identifier));
    }
    break;

  case 41:
/* Line 1792 of yacc.c  */
#line 556 "proj.y"
    {
      llvm::Type* ty  = static_cast<llvm::Type*>((yyvsp[(1) - (5)].llvm_ptr));
      llvm::Value* val = static_cast<llvm::Value*>((yyvsp[(4) - (5)].llvm_ptr));

      if(!ty->isIntegerTy(32) && !ty->isIntegerTy(8))
      {
        yyerror("Cannot assign dereferenced pointer to non-int/char");
        exit(1);
      }

      llvm::AllocaInst* alloc = builder->CreateAlloca(ty, nullptr, (yyvsp[(2) - (5)].identifier));
      builder->CreateStore(val, alloc);
      symbolTable[(yyvsp[(2) - (5)].identifier)] = alloc;

      free((yyvsp[(2) - (5)].identifier));
    }
    break;

  case 42:
/* Line 1792 of yacc.c  */
#line 573 "proj.y"
    {
      if(temp == 1)
      {
        temp = 0;
        llvm::Type* ty = static_cast<llvm::Type*>((yyvsp[(1) - (5)].llvm_ptr));
        llvm::Value* val = static_cast<llvm::Value*>((yyvsp[(4) - (5)].llvm_ptr));
        llvm::AllocaInst* alloc = builder->CreateAlloca(ty, nullptr, (yyvsp[(2) - (5)].identifier));
        builder->CreateStore(val, alloc);
        symbolTable[(yyvsp[(2) - (5)].identifier)] = alloc;
        printf("Dynamically allocated %s at %p\n", (yyvsp[(2) - (5)].identifier), (void*)val);
        free((yyvsp[(2) - (5)].identifier));
      }
      else
      {
        yyerror("Non pointer type variables can't be assigned dynamically");
        exit(1);
      }
    }
    break;

  case 43:
/* Line 1792 of yacc.c  */
#line 595 "proj.y"
    {
      auto it = symbolTable.find((yyvsp[(2) - (2)].identifier));
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
      (yyval.llvm_ptr) = (void*)builder->CreateBitCast(alloc, i8PtrTy);
      printf("Created pointer to %s\n", (yyvsp[(2) - (2)].identifier));
      free((yyvsp[(2) - (2)].identifier));
    }
    break;

  case 44:
/* Line 1792 of yacc.c  */
#line 622 "proj.y"
    {
      if((yyvsp[(1) - (2)].op) == MUL)
      {
        llvm::Value* ptrVal = static_cast<llvm::Value*>((yyvsp[(2) - (2)].llvm_ptr));
        llvm::Type* ptrTy   = ptrVal->getType();
        if(!ptrTy->isPointerTy())
        {
          yyerror("Cannot dereference non-pointer");
          exit(1);
        }

        llvm::Value* loaded = builder->CreateLoad(llvm::Type::getInt32Ty(context), ptrVal, "deref");
        (yyval.llvm_ptr) = (void*)loaded;
      }
      else if((yyvsp[(1) - (2)].op) == MINUS)
      {
        llvm::Value* val = static_cast<llvm::Value*>((yyvsp[(2) - (2)].llvm_ptr));
        if (llvm::ConstantInt* CI = llvm::dyn_cast<llvm::ConstantInt>(val))
        {
          (yyval.llvm_ptr) = (void*)llvm::ConstantInt::get(builder->getInt32Ty(), -CI->getSExtValue());
        }
        else
        {
          (yyval.llvm_ptr) = (void*)builder->CreateNeg(val, "neg");
        }
      }
      else
      {
        yyerror("Star operator must be used to access a pointer");
        exit(1);
      }
    }
    break;

  case 45:
/* Line 1792 of yacc.c  */
#line 655 "proj.y"
    {
      if((yyvsp[(1) - (4)].op) == MUL)
      {
        llvm::Value* ptrVal = static_cast<llvm::Value*>((yyvsp[(2) - (4)].llvm_ptr));
        llvm::Value* opVal = static_cast<llvm::Value*>((yyvsp[(4) - (4)].llvm_ptr));
        llvm::Type* ptrTy   = ptrVal->getType();
          
        if(!ptrTy->isPointerTy())
        {
          yyerror("Cannot dereference non-pointer");
          exit(1);
        }

        llvm::Value* loaded = builder->CreateLoad(llvm::Type::getInt32Ty(context), ptrVal, "deref");
          
        llvm::Value* result = nullptr;
        if((yyvsp[(3) - (4)].op) == PLUS)
          result = builder->CreateAdd(loaded, opVal, "add");
        else if((yyvsp[(3) - (4)].op) == MINUS)
          result = builder->CreateSub(loaded, opVal, "sub");
        else if((yyvsp[(3) - (4)].op) == MUL)
          result = builder->CreateMul(loaded, opVal, "mul");
        else if((yyvsp[(3) - (4)].op) == DIV)
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
          
        (yyval.llvm_ptr) = (void*)result;
      }
      else
      {
        yyerror("Invalid pointer arithmetic");
        exit(1);
      }
    }
    break;

  case 46:
/* Line 1792 of yacc.c  */
#line 704 "proj.y"
    {
      if((yyvsp[(1) - (4)].op) == MUL)
      {
        llvm::Value* ptrVal = static_cast<llvm::Value*>((yyvsp[(2) - (4)].llvm_ptr));
        llvm::Type* ptrTy   = ptrVal->getType();
          
        if(!ptrTy->isPointerTy())
        {
          yyerror("Cannot dereference non-pointer");
          exit(1);
        }

        llvm::Value* loaded = builder->CreateLoad(llvm::Type::getInt32Ty(context), ptrVal, "deref");
          
        llvm::Value* opVal = llvm::ConstantInt::get(builder->getInt32Ty(), (yyvsp[(4) - (4)].num));
          
        llvm::Value* result = nullptr;
        if((yyvsp[(3) - (4)].op) == PLUS)
          result = builder->CreateAdd(loaded, opVal, "add");
        else if((yyvsp[(3) - (4)].op) == MINUS)
          result = builder->CreateSub(loaded, opVal, "sub");
        else if((yyvsp[(3) - (4)].op) == MUL)
          result = builder->CreateMul(loaded, opVal, "mul");
        else if ((yyvsp[(3) - (4)].op) == DIV)
        {
          if ((yyvsp[(4) - (4)].num) == 0)
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
          
        (yyval.llvm_ptr) = (void*)result;
      }
      else
      {
        yyerror("Invalid pointer arithmetic");
        exit(1);
      }
    }
    break;

  case 47:
/* Line 1792 of yacc.c  */
#line 753 "proj.y"
    { (yyval.llvm_ptr) = (void*)llvm::ConstantInt::get(builder->getInt32Ty(), (yyvsp[(1) - (1)].num));  }
    break;

  case 48:
/* Line 1792 of yacc.c  */
#line 754 "proj.y"
    { (yyval.llvm_ptr) = (void*)llvm::ConstantInt::get(builder->getInt32Ty(), -(yyvsp[(2) - (2)].num)); }
    break;

  case 49:
/* Line 1792 of yacc.c  */
#line 755 "proj.y"
    { (yyval.llvm_ptr) = (void*)llvm::ConstantInt::get(builder->getInt8Ty(), (yyvsp[(1) - (1)].ch));   }
    break;

  case 50:
/* Line 1792 of yacc.c  */
#line 759 "proj.y"
    { (yyval.llvm_ptr) = (yyvsp[(1) - (1)].llvm_ptr); }
    break;

  case 51:
/* Line 1792 of yacc.c  */
#line 760 "proj.y"
    { (yyval.llvm_ptr) = (void*)llvm::ConstantInt::get(builder->getInt32Ty(), -(yyvsp[(2) - (2)].num)); }
    break;

  case 52:
/* Line 1792 of yacc.c  */
#line 762 "proj.y"
    {
      auto* var = symbolTable[(yyvsp[(1) - (1)].identifier)];
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
        
      if(stringVariables.find((yyvsp[(1) - (1)].identifier)) != stringVariables.end())
      {
          (yyval.llvm_ptr) = (void*)var;
      }
      else
      {
        (yyval.llvm_ptr) = (void*)builder->CreateLoad(varType, var);
      }
      free((yyvsp[(1) - (1)].identifier));
    }
    break;

  case 53:
/* Line 1792 of yacc.c  */
#line 789 "proj.y"
    {
      auto* var = symbolTable[(yyvsp[(1) - (3)].identifier)];
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
      std::string fieldName = (yyvsp[(3) - (3)].identifier);
      if(fieldMap.find(fieldName) == fieldMap.end())
      {
        yyerror("Field not found in structure");
        exit(1);
      }
      unsigned fieldIndex = fieldMap[fieldName];
      llvm::Value* fieldPtr = builder->CreateStructGEP(structTy, var, fieldIndex, "fieldptr");
      llvm::Value* fieldVal = builder->CreateLoad(structTy->getElementType(fieldIndex), fieldPtr, "fieldload");
      (yyval.llvm_ptr) = (void*)fieldVal;
      free((yyvsp[(1) - (3)].identifier));
      free((yyvsp[(3) - (3)].identifier));
    }
    break;

  case 54:
/* Line 1792 of yacc.c  */
#line 825 "proj.y"
    {
      llvm::Value* loaded = static_cast<llvm::Value*>((yyvsp[(1) - (1)].llvm_ptr));
      (yyval.llvm_ptr) = (void*)loaded;
    }
    break;

  case 55:
/* Line 1792 of yacc.c  */
#line 830 "proj.y"
    {
      auto* func = module->getFunction((yyvsp[(1) - (1)].function_call).name);
      if(!func)
      {
        yyerror("Undefined function");
        exit(1);
      }
        
      auto* args = static_cast<std::vector<llvm::Value*>*>((yyvsp[(1) - (1)].function_call).args);
      std::vector<llvm::Value*> callArgs;
      for(auto* arg : *args)
      {
        callArgs.push_back(static_cast<llvm::Value*>(arg));
      }
        
      if(func->getReturnType()->isVoidTy())
      {
        fprintf(stderr, "Warning: Using void function '%s' in expression. Using 0 instead.\n", func->getName().str().c_str());
        (yyval.llvm_ptr) = (void*)llvm::ConstantInt::get(builder->getInt32Ty(), 0);
        builder->CreateCall(func, callArgs);
      }
      else 
      {
        (yyval.llvm_ptr) = (void*)builder->CreateCall(func, callArgs, "calltmp");
      }
        
      delete args;
      free((yyvsp[(1) - (1)].function_call).name);
    }
    break;

  case 56:
/* Line 1792 of yacc.c  */
#line 860 "proj.y"
    {
      auto* var = symbolTable[(yyvsp[(1) - (4)].identifier)];
      if(!var)
      {
        yyerror("Undefined array");
        exit(1);
      }

      llvm::Value* indexVal = static_cast<llvm::Value*>((yyvsp[(3) - (4)].llvm_ptr));

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
      (yyval.llvm_ptr) = (void*)builder->CreateLoad(arrType->getElementType(), elemPtr, "arrayload");
      free((yyvsp[(1) - (4)].identifier));
    }
    break;

  case 57:
/* Line 1792 of yacc.c  */
#line 913 "proj.y"
    {
      auto* var = symbolTable[(yyvsp[(1) - (2)].identifier)];
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

      if((yyvsp[(2) - (2)].op) == INCREMENT)
      {
        newVal = builder->CreateAdd(currentVal, one, "increment");
      }
      else if((yyvsp[(2) - (2)].op) == DECREMENT)
      {
        newVal = builder->CreateSub(currentVal, one, "decrement");
      }
      builder->CreateStore(newVal, var);
        
      (yyval.llvm_ptr) = (void*)newVal;
      free((yyvsp[(1) - (2)].identifier));
    }
    break;

  case 58:
/* Line 1792 of yacc.c  */
#line 946 "proj.y"
    {
      auto* lhs = static_cast<llvm::Value*>((yyvsp[(1) - (3)].llvm_ptr));
      auto* rhs = static_cast<llvm::Value*>((yyvsp[(3) - (3)].llvm_ptr));

      if (lhs->getType() != llvm::Type::getInt1Ty(context))
      {
        lhs = builder->CreateICmpNE(lhs, llvm::ConstantInt::get(lhs->getType(), 0), "bool_lhs");
      }
      if(rhs->getType() != llvm::Type::getInt1Ty(context))
      {
        rhs = builder->CreateICmpNE(rhs, llvm::ConstantInt::get(rhs->getType(), 0), "bool_rhs");
      }
       
      llvm::Value* result = builder->CreateAnd(lhs, rhs, "and");

      (yyval.llvm_ptr) = (void*)builder->CreateZExt(result, builder->getInt32Ty(), "and_result");
    }
    break;

  case 59:
/* Line 1792 of yacc.c  */
#line 964 "proj.y"
    {
      auto* lhs = static_cast<llvm::Value*>((yyvsp[(1) - (3)].llvm_ptr));
      auto* rhs = static_cast<llvm::Value*>((yyvsp[(3) - (3)].llvm_ptr));
      
      if (lhs->getType() != llvm::Type::getInt1Ty(context))
      {
        lhs = builder->CreateICmpNE(lhs, llvm::ConstantInt::get(lhs->getType(), 0), "bool_lhs");
      }
      if (rhs->getType() != llvm::Type::getInt1Ty(context))
      {
        rhs = builder->CreateICmpNE(rhs, llvm::ConstantInt::get(rhs->getType(), 0), "bool_rhs");
      }
      
      llvm::Value* result = builder->CreateOr(lhs, rhs, "OR");
      (yyval.llvm_ptr) = (void*)builder->CreateZExt(result, builder->getInt32Ty(), "or_result");
    }
    break;

  case 60:
/* Line 1792 of yacc.c  */
#line 981 "proj.y"
    {
      auto* lhs = static_cast<llvm::Value*>((yyvsp[(1) - (3)].llvm_ptr));
      auto* rhs = static_cast<llvm::Value*>((yyvsp[(3) - (3)].llvm_ptr));
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
        if((yyvsp[(2) - (3)].op) == PLUS)
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
          (yyval.llvm_ptr) = (void*)llvm::ConstantPointerNull::get(llvm::PointerType::get(context, 0));
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
      
      if((yyvsp[(2) - (3)].op) == PLUS)
        result = builder->CreateAdd(lhs, rhs, "add");
      else if((yyvsp[(2) - (3)].op) == MINUS)
        result = builder->CreateSub(lhs, rhs, "sub");
      else if((yyvsp[(2) - (3)].op) == MUL)
        result = builder->CreateMul(lhs, rhs, "mul");
      else if((yyvsp[(2) - (3)].op) == DIV)
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
      else if((yyvsp[(2) - (3)].op) == LESSTHAN)
      {
        result = builder->CreateZExt(builder->CreateICmpSLT(lhs, rhs, "lt"), llvm::Type::getInt32Ty(context), "lt_ext");
      }
      else if((yyvsp[(2) - (3)].op) == GREATERTHAN)
      {
        result = builder->CreateZExt(builder->CreateICmpSGT(lhs, rhs, "gt"), llvm::Type::getInt32Ty(context), "gt_ext");
      }
      else if ((yyvsp[(2) - (3)].op) == LESSEQUAL)
      {
        result = builder->CreateZExt(builder->CreateICmpSLE(lhs, rhs, "le"), llvm::Type::getInt32Ty(context), "le_ext");
      }
      else if ((yyvsp[(2) - (3)].op) == GREATEREQUAL)
      {
        result = builder->CreateZExt(builder->CreateICmpSGE(lhs, rhs, "ge"), llvm::Type::getInt32Ty(context), "ge_ext");
      }
      else if ((yyvsp[(2) - (3)].op) == EQUAL)
      {
        result = builder->CreateZExt(builder->CreateICmpEQ(lhs, rhs, "eq"), llvm::Type::getInt32Ty(context), "eq_ext");
      }
      else if ((yyvsp[(2) - (3)].op) == NOTEQUAL)
      {
        result = builder->CreateZExt(builder->CreateICmpNE(lhs, rhs, "neq"), llvm::Type::getInt32Ty(context), "neq_ext");
      }
      
      if (isCharOp && result && ((yyvsp[(2) - (3)].op) == PLUS || (yyvsp[(2) - (3)].op) == MINUS || (yyvsp[(2) - (3)].op) == MUL || (yyvsp[(2) - (3)].op) == DIV))
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
      
      (yyval.llvm_ptr) = (void*)result;
    }
  }
    break;

  case 61:
/* Line 1792 of yacc.c  */
#line 1124 "proj.y"
    {
      auto* var = symbolTable[(yyvsp[(1) - (4)].identifier)];
      auto* val = static_cast<llvm::Value*>((yyvsp[(3) - (4)].llvm_ptr));
      
      if (auto* callInst = llvm::dyn_cast<llvm::CallInst>(val))
      {
          if (callInst->getFunctionType()->getReturnType()->isVoidTy())
          {
            fprintf(stderr, "Warning: Attempting to assign void function '%s' to variable '%s'. Assigning 0 instead.\n", callInst->getCalledFunction()->getName().str().c_str(), (yyvsp[(1) - (4)].identifier));
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
      
      free((yyvsp[(1) - (4)].identifier));
    }
    break;

  case 62:
/* Line 1792 of yacc.c  */
#line 1157 "proj.y"
    {
      auto* var = symbolTable[(yyvsp[(1) - (7)].identifier)];
      if (!var)
      {
        yyerror("Undefined array");
        exit(1);
      }
      llvm::AllocaInst* allocInst = llvm::cast<llvm::AllocaInst>(var);
      llvm::ArrayType* arrType = llvm::cast<llvm::ArrayType>(allocInst->getAllocatedType());
      unsigned arraySize = arrType->getNumElements();

      llvm::Value* indexVal = static_cast<llvm::Value*>((yyvsp[(3) - (7)].llvm_ptr));

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
      llvm::Value* val = static_cast<llvm::Value*>((yyvsp[(6) - (7)].llvm_ptr));
      builder->CreateStore(val, elemPtr);
      printf("Stored value in array %s at computed index\n", (yyvsp[(1) - (7)].identifier));
      free((yyvsp[(1) - (7)].identifier));
    }
    break;

  case 63:
/* Line 1792 of yacc.c  */
#line 1209 "proj.y"
    {
      if ((yyvsp[(1) - (5)].op) == MUL)
      {
        llvm::Value* ptr = static_cast<llvm::Value*>((yyvsp[(2) - (5)].llvm_ptr));
        llvm::Type* ptrTy = ptr->getType();
        if (!ptrTy->isPointerTy())
        {
          yyerror("Cannot assign to non-pointer dereference");
          exit(1);
        }
        llvm::Value* val = static_cast<llvm::Value*>((yyvsp[(4) - (5)].llvm_ptr));
        builder->CreateStore(val, ptr);
      }
      else
      {
        yyerror("Invalid l-value in assignment");
        exit(1);
      }
    }
    break;

  case 64:
/* Line 1792 of yacc.c  */
#line 1229 "proj.y"
    {
      auto* var = symbolTable[(yyvsp[(1) - (4)].identifier)];
      if (!var)
      {
        yyerror("Undefined variable");
        exit(1);
      }
      
      llvm::Value* val = static_cast<llvm::Value*>((yyvsp[(3) - (4)].llvm_ptr));
      if (!val->getType()->isPointerTy())
      {
        yyerror("Right-hand side is not a pointer");
        exit(1);
      }
      
      builder->CreateStore(val, var);
      printf("Reassigned pointer %s\n", (yyvsp[(1) - (4)].identifier));
      free((yyvsp[(1) - (4)].identifier));
    }
    break;

  case 65:
/* Line 1792 of yacc.c  */
#line 1249 "proj.y"
    {
      auto* var = symbolTable[(yyvsp[(1) - (6)].identifier)];
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
      std::string fieldName = (yyvsp[(3) - (6)].identifier);
      if (fieldMap.find(fieldName) == fieldMap.end())
      {
        yyerror("Field not found in structure");
        exit(1);
      }
      unsigned fieldIndex = fieldMap[fieldName];
      llvm::Value* fieldPtr = builder->CreateStructGEP(structTy, var, fieldIndex, "fieldptr");
      llvm::Value* val = static_cast<llvm::Value*>((yyvsp[(5) - (6)].llvm_ptr));
      builder->CreateStore(val, fieldPtr);
      printf("Stored value in %s.%s\n", (yyvsp[(1) - (6)].identifier), (yyvsp[(3) - (6)].identifier));
      free((yyvsp[(1) - (6)].identifier));
      free((yyvsp[(3) - (6)].identifier));
    }
    break;

  case 66:
/* Line 1792 of yacc.c  */
#line 1286 "proj.y"
    {
      auto* var = symbolTable[(yyvsp[(1) - (4)].identifier)];
      if (!var)
      {
        yyerror("Undefined variable");
        exit(1);
      }
      
      llvm::Value* strVal = builder->CreateGlobalStringPtr((yyvsp[(3) - (4)].string));
      builder->CreateStore(strVal, var);
      stringVariables[(yyvsp[(1) - (4)].identifier)] = true;
      printf("Stored string \"%s\" at %p\n", (yyvsp[(3) - (4)].string), (void*)var);
      free((yyvsp[(1) - (4)].identifier));
      free((yyvsp[(3) - (4)].string));
    }
    break;

  case 67:
/* Line 1792 of yacc.c  */
#line 1302 "proj.y"
    {
      auto* var = symbolTable[(yyvsp[(1) - (6)].identifier)];
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
      std::string fieldName = (yyvsp[(3) - (6)].identifier);
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
      llvm::Value* strVal = builder->CreateGlobalStringPtr((yyvsp[(5) - (6)].string));
      builder->CreateStore(strVal, fieldPtr);
      free((yyvsp[(1) - (6)].identifier));
      free((yyvsp[(3) - (6)].identifier));
      free((yyvsp[(5) - (6)].string));
    }
    break;

  case 68:
/* Line 1792 of yacc.c  */
#line 1343 "proj.y"
    {
      llvm::Value* cond = static_cast<llvm::Value*>((yyvsp[(3) - (4)].llvm_ptr));
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
      
      (yyval.if_blocks).then_bb = (void*)thenBB;
      (yyval.if_blocks).else_bb = (void*)elseBB;
      (yyval.if_blocks).merge_bb = (void*)mergeBB;
    }
    break;

  case 69:
/* Line 1792 of yacc.c  */
#line 1367 "proj.y"
    {
      llvm::BasicBlock* thenBB = static_cast<llvm::BasicBlock*>((yyvsp[(1) - (4)].if_blocks).then_bb);
      llvm::BasicBlock* elseBB = static_cast<llvm::BasicBlock*>((yyvsp[(1) - (4)].if_blocks).else_bb);
      llvm::BasicBlock* mergeBB = static_cast<llvm::BasicBlock*>((yyvsp[(1) - (4)].if_blocks).merge_bb);
      
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
      
      (yyval.basic_block) = (void*)mergeBB;
    }
    break;

  case 70:
/* Line 1792 of yacc.c  */
#line 1392 "proj.y"
    {
      llvm::BasicBlock* mergeBB = static_cast<llvm::BasicBlock*>((yyvsp[(1) - (1)].basic_block));
      
      if (!builder->GetInsertBlock()->getTerminator())
      {
        builder->CreateBr(mergeBB);
      }
      
      llvm::Function* func = builder->GetInsertBlock()->getParent();
      mergeBB->insertInto(func);
      
      builder->SetInsertPoint(mergeBB);
    }
    break;

  case 71:
/* Line 1792 of yacc.c  */
#line 1406 "proj.y"
    {
      llvm::BasicBlock* mergeBB = static_cast<llvm::BasicBlock*>((yyvsp[(1) - (5)].basic_block));
      
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
    break;

  case 72:
/* Line 1792 of yacc.c  */
#line 1428 "proj.y"
    {
      (yyval.llvm_ptr) = (yyvsp[(3) - (3)].llvm_ptr);
    }
    break;

  case 73:
/* Line 1792 of yacc.c  */
#line 1435 "proj.y"
    {
      llvm::Function* func = builder->GetInsertBlock()->getParent();
      
      llvm::BasicBlock* entryBB = builder->GetInsertBlock();
      llvm::BasicBlock* condBB = llvm::BasicBlock::Create(context, "while.cond", func);
      llvm::BasicBlock* bodyBB = llvm::BasicBlock::Create(context, "while.body", func);
      llvm::BasicBlock* afterBB = llvm::BasicBlock::Create(context, "while.end", func);
      
      BreakTargets.push_back(afterBB);
      builder->CreateBr(condBB);
      builder->SetInsertPoint(condBB);
      
      (yyval.while_blocks).cond_bb = (void*)condBB;
      (yyval.while_blocks).body_bb = (void*)bodyBB;
      (yyval.while_blocks).after_bb = (void*)afterBB;
    }
    break;

  case 74:
/* Line 1792 of yacc.c  */
#line 1455 "proj.y"
    {
      llvm::Value* cond = static_cast<llvm::Value*>((yyvsp[(2) - (3)].llvm_ptr));
      llvm::BasicBlock* bodyBB = static_cast<llvm::BasicBlock*>((yyvsp[(1) - (3)].while_blocks).body_bb);
      llvm::BasicBlock* afterBB = static_cast<llvm::BasicBlock*>((yyvsp[(1) - (3)].while_blocks).after_bb);
      
      if(cond->getType() != llvm::Type::getInt1Ty(context))
      {
        cond = builder->CreateICmpNE(cond, llvm::ConstantInt::get(cond->getType(), 0), "whilecond");
      }
      
      builder->CreateCondBr(cond, bodyBB, afterBB);
      
      builder->SetInsertPoint(bodyBB);
      
      (yyval.while_blocks).cond_bb = (yyvsp[(1) - (3)].while_blocks).cond_bb;
      (yyval.while_blocks).body_bb = (yyvsp[(1) - (3)].while_blocks).body_bb;
      (yyval.while_blocks).after_bb = (yyvsp[(1) - (3)].while_blocks).after_bb;
    }
    break;

  case 75:
/* Line 1792 of yacc.c  */
#line 1477 "proj.y"
    {
      llvm::BasicBlock* condBB = static_cast<llvm::BasicBlock*>((yyvsp[(1) - (4)].while_blocks).cond_bb);
      llvm::BasicBlock* afterBB = static_cast<llvm::BasicBlock*>((yyvsp[(1) - (4)].while_blocks).after_bb);
      
      if (!builder->GetInsertBlock()->getTerminator())
      {
          builder->CreateBr(condBB);
      }
      
      builder->SetInsertPoint(afterBB);
      
      BreakTargets.pop_back();
      
      (yyval.basic_block) = (void*)afterBB;
    }
    break;

  case 76:
/* Line 1792 of yacc.c  */
#line 1496 "proj.y"
    {
      (yyval.for_blocks).var_name = strdup((yyvsp[(3) - (9)].identifier));
      (yyval.for_blocks).init_val = (void*)(yyvsp[(5) - (9)].llvm_ptr);
      (yyval.for_blocks).end_val  = (void*)(yyvsp[(7) - (9)].llvm_ptr);
      (yyval.for_blocks).step_val = (void*)(yyvsp[(9) - (9)].llvm_ptr);

      (yyval.for_blocks).cond_bb  = nullptr;
      (yyval.for_blocks).body_bb  = nullptr;
      (yyval.for_blocks).inc_bb   = nullptr;
      (yyval.for_blocks).after_bb = nullptr;
    }
    break;

  case 77:
/* Line 1792 of yacc.c  */
#line 1511 "proj.y"
    {
      llvm::Function *func = builder->GetInsertBlock()->getParent();

      llvm::BasicBlock *condBB  = llvm::BasicBlock::Create(context, "for.cond", func);
      llvm::BasicBlock *bodyBB  = llvm::BasicBlock::Create(context, "for.body", func);
      llvm::BasicBlock *incBB   = llvm::BasicBlock::Create(context, "for.inc",  func);
      llvm::BasicBlock *afterBB = llvm::BasicBlock::Create(context, "for.end",  func);

      llvm::AllocaInst *varAlloc = builder->CreateAlloca(builder->getInt32Ty(), nullptr, (yyvsp[(1) - (1)].for_blocks).var_name);

      builder->CreateStore((llvm::Value*)(yyvsp[(1) - (1)].for_blocks).init_val, varAlloc);

      builder->CreateBr(condBB);
      builder->SetInsertPoint(condBB);

      (yyval.for_blocks).var_name = (yyvsp[(1) - (1)].for_blocks).var_name;
      (yyval.for_blocks).init_val = (yyvsp[(1) - (1)].for_blocks).init_val;
      (yyval.for_blocks).end_val  = (yyvsp[(1) - (1)].for_blocks).end_val;
      (yyval.for_blocks).step_val = (yyvsp[(1) - (1)].for_blocks).step_val;

      (yyval.for_blocks).cond_bb  = (void*)condBB;
      (yyval.for_blocks).body_bb  = (void*)bodyBB;
      (yyval.for_blocks).inc_bb   = (void*)incBB;
      (yyval.for_blocks).after_bb = (void*)afterBB;

      symbolTable[(yyvsp[(1) - (1)].for_blocks).var_name] = varAlloc;
    }
    break;

  case 78:
/* Line 1792 of yacc.c  */
#line 1542 "proj.y"
    {
      auto *condBB   = static_cast<llvm::BasicBlock*>((yyvsp[(1) - (1)].for_blocks).cond_bb);
      auto *bodyBB   = static_cast<llvm::BasicBlock*>((yyvsp[(1) - (1)].for_blocks).body_bb);
      auto *incBB    = static_cast<llvm::BasicBlock*>((yyvsp[(1) - (1)].for_blocks).inc_bb);
      auto *afterBB  = static_cast<llvm::BasicBlock*>((yyvsp[(1) - (1)].for_blocks).after_bb);

      llvm::AllocaInst *varAlloc = llvm::cast<llvm::AllocaInst>(symbolTable[(yyvsp[(1) - (1)].for_blocks).var_name]);

      llvm::Value *endVal  = static_cast<llvm::Value*>((yyvsp[(1) - (1)].for_blocks).end_val);
      llvm::Value *stepVal = static_cast<llvm::Value*>((yyvsp[(1) - (1)].for_blocks).step_val);

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
    break;

  case 79:
/* Line 1792 of yacc.c  */
#line 1567 "proj.y"
    {
      auto *incBB = static_cast<llvm::BasicBlock*>((yyvsp[(1) - (3)].for_blocks).inc_bb);
      if (!builder->GetInsertBlock()->getTerminator())
      {
        builder->CreateBr(incBB);
      }
    }
    break;

  case 80:
/* Line 1792 of yacc.c  */
#line 1575 "proj.y"
    {
      auto *condBB  = static_cast<llvm::BasicBlock*>((yyvsp[(1) - (5)].for_blocks).cond_bb);
      auto *incBB   = static_cast<llvm::BasicBlock*>((yyvsp[(1) - (5)].for_blocks).inc_bb);
      auto *afterBB = static_cast<llvm::BasicBlock*>((yyvsp[(1) - (5)].for_blocks).after_bb);

      llvm::AllocaInst *varAlloc = llvm::cast<llvm::AllocaInst>(symbolTable[(yyvsp[(1) - (5)].for_blocks).var_name]);

      llvm::Value *stepVal = static_cast<llvm::Value*>((yyvsp[(1) - (5)].for_blocks).step_val);

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
      
      (yyval.basic_block) = (void*)continueBB;
    }
    break;

  case 81:
/* Line 1792 of yacc.c  */
#line 1613 "proj.y"
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
    break;

  case 82:
/* Line 1792 of yacc.c  */
#line 1630 "proj.y"
    {
      auto* var = symbolTable[(yyvsp[(1) - (3)].identifier)];
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
      
      if((yyvsp[(2) - (3)].op) == INCREMENT)
      {
          newVal = builder->CreateAdd(currentVal, one, "increment");
      }
      else if((yyvsp[(2) - (3)].op) == DECREMENT)
      {
          newVal = builder->CreateSub(currentVal, one, "decrement");
      }
      
      builder->CreateStore(newVal, var);
      
      (yyval.llvm_ptr) = (void*)newVal;
      free((yyvsp[(1) - (3)].identifier));
    }
    break;

  case 84:
/* Line 1792 of yacc.c  */
#line 1666 "proj.y"
    {
        auto caseVal = llvm::dyn_cast<llvm::ConstantInt>(static_cast<llvm::Value*>((yyvsp[(3) - (4)].llvm_ptr)));
        auto *caseBB  = llvm::BasicBlock::Create(context, "switch.case", yy_func);

        yy_switch_inst->addCase(caseVal, caseBB);
        builder->SetInsertPoint(caseBB);
    }
    break;

  case 85:
/* Line 1792 of yacc.c  */
#line 1674 "proj.y"
    {
        if (!builder->GetInsertBlock()->getTerminator())
        {
            builder->CreateBr(yy_end_bb);
        }
    }
    break;

  case 86:
/* Line 1792 of yacc.c  */
#line 1684 "proj.y"
    {
        llvm::Value* cond = static_cast<llvm::Value*>((yyvsp[(3) - (4)].llvm_ptr));
        yy_func = builder->GetInsertBlock()->getParent();
        yy_default_bb = llvm::BasicBlock::Create(context, "switch.default", yy_func);
        yy_end_bb = llvm::BasicBlock::Create(context, "switch.end",     yy_func);
        yy_switch_inst = builder->CreateSwitch(cond, yy_default_bb, 0);
    }
    break;

  case 87:
/* Line 1792 of yacc.c  */
#line 1692 "proj.y"
    {
        builder->SetInsertPoint(yy_default_bb);
    }
    break;

  case 88:
/* Line 1792 of yacc.c  */
#line 1696 "proj.y"
    {
        if (!builder->GetInsertBlock()->getTerminator())
        {
            builder->CreateBr(yy_end_bb);
        }
    }
    break;

  case 89:
/* Line 1792 of yacc.c  */
#line 1703 "proj.y"
    {
        builder->SetInsertPoint(yy_end_bb);
    }
    break;

  case 90:
/* Line 1792 of yacc.c  */
#line 1710 "proj.y"
    {
      if (strcmp((yyvsp[(3) - (7)].identifier), "main") == 0)
      {
        yyerror("The main function is already defined.");
        exit(1);
      }
      returnType = static_cast<llvm::Type*>((yyvsp[(2) - (7)].llvm_ptr));
      auto* paramTs = static_cast<std::vector<llvm::Type*>*>((yyvsp[(5) - (7)].function_decl).param_types);
      auto* paramNs = static_cast<std::vector<std::string>*>((yyvsp[(5) - (7)].function_decl).param_names);

      llvm::FunctionType* fnTy = llvm::FunctionType::get(returnType, *paramTs, false);
      llvm::Function* fn = llvm::Function::Create(fnTy, llvm::Function::ExternalLinkage, (yyvsp[(3) - (7)].identifier), module);

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
      free((yyvsp[(3) - (7)].identifier));
    }
    break;

  case 91:
/* Line 1792 of yacc.c  */
#line 1743 "proj.y"
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
    break;

  case 92:
/* Line 1792 of yacc.c  */
#line 1757 "proj.y"
    {
        (yyval.function_decl).param_types = new std::vector<llvm::Type*>();
        (yyval.function_decl).param_names = new std::vector<std::string>();
    }
    break;

  case 93:
/* Line 1792 of yacc.c  */
#line 1762 "proj.y"
    {
        (yyval.function_decl).param_types = new std::vector<llvm::Type*>();
        (yyval.function_decl).param_names = new std::vector<std::string>();
        static_cast<std::vector<llvm::Type*>*>((yyval.function_decl).param_types)->push_back(static_cast<llvm::Type*>((yyvsp[(1) - (2)].llvm_ptr)));
        static_cast<std::vector<std::string>*>((yyval.function_decl).param_names)->push_back((yyvsp[(2) - (2)].identifier));
        free((yyvsp[(2) - (2)].identifier));
    }
    break;

  case 94:
/* Line 1792 of yacc.c  */
#line 1770 "proj.y"
    {
        (yyval.function_decl).param_types = (yyvsp[(1) - (4)].function_decl).param_types;
        (yyval.function_decl).param_names = (yyvsp[(1) - (4)].function_decl).param_names;
        static_cast<std::vector<llvm::Type*>*>((yyval.function_decl).param_types)->push_back(static_cast<llvm::Type*>((yyvsp[(3) - (4)].llvm_ptr)));
        static_cast<std::vector<std::string>*>((yyval.function_decl).param_names)->push_back((yyvsp[(4) - (4)].identifier));
        free((yyvsp[(4) - (4)].identifier));
    }
    break;

  case 95:
/* Line 1792 of yacc.c  */
#line 1781 "proj.y"
    {
        (yyval.function_call).name = (yyvsp[(1) - (4)].identifier);
        (yyval.function_call).args = (yyvsp[(3) - (4)].function_call).args;
    }
    break;

  case 96:
/* Line 1792 of yacc.c  */
#line 1788 "proj.y"
    {
        (yyval.function_call).args = new std::vector<llvm::Value*>();
    }
    break;

  case 97:
/* Line 1792 of yacc.c  */
#line 1792 "proj.y"
    {
        (yyval.function_call).args = new std::vector<llvm::Value*>();
        static_cast<std::vector<llvm::Value*>*>((yyval.function_call).args)->push_back(static_cast<llvm::Value*>((yyvsp[(1) - (1)].llvm_ptr)));
    }
    break;

  case 98:
/* Line 1792 of yacc.c  */
#line 1797 "proj.y"
    {
        (yyval.function_call).args = (yyvsp[(1) - (3)].function_call).args;
        static_cast<std::vector<llvm::Value*>*>((yyval.function_call).args)->push_back(static_cast<llvm::Value*>((yyvsp[(3) - (3)].llvm_ptr)));
    }
    break;

  case 99:
/* Line 1792 of yacc.c  */
#line 1805 "proj.y"
    {
        llvm::Value* retVal = static_cast<llvm::Value*>((yyvsp[(2) - (3)].llvm_ptr));
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
        (yyval.llvm_ptr) = (void*)retVal;
    }
    break;

  case 100:
/* Line 1792 of yacc.c  */
#line 1826 "proj.y"
    {
        llvm::Function* currentFunc = builder->GetInsertBlock()->getParent();
        if (!currentFunc->getReturnType()->isVoidTy()) {
            yyerror("Non-void function must return a value");
            exit(1);
        }
        builder->CreateRetVoid();
        (yyval.llvm_ptr) = nullptr;
    }
    break;

  case 101:
/* Line 1792 of yacc.c  */
#line 1839 "proj.y"
    {
        auto* func = module->getFunction((yyvsp[(1) - (2)].function_call).name);
        if (!func)
        {
            yyerror("Undefined function");
            exit(1);
        }
        
        auto* args = static_cast<std::vector<llvm::Value*>*>((yyvsp[(1) - (2)].function_call).args);
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
        free((yyvsp[(1) - (2)].function_call).name);
    }
    break;

  case 102:
/* Line 1792 of yacc.c  */
#line 1870 "proj.y"
    {
        llvm::Type* allocTy;
        if (strcmp((yyvsp[(3) - (4)].string), "number") == 0)
        {
            allocTy = builder->getInt32Ty();
        } else if (strcmp((yyvsp[(3) - (4)].string), "letter") == 0)
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
        (yyval.llvm_ptr) = (void*)typedPtr;
        free((yyvsp[(3) - (4)].string));
    }
    break;

  case 103:
/* Line 1792 of yacc.c  */
#line 1912 "proj.y"
    {
        llvm::Type* allocTy;
        if (strcmp((yyvsp[(3) - (6)].string), "number") == 0)
        {
            allocTy = builder->getInt32Ty();
        }
        else if (strcmp((yyvsp[(3) - (6)].string), "letter") == 0)
        {
            allocTy = builder->getInt8Ty();
        }
        else
        {
            yyerror("Invalid type in dyn allocation. Use 'number' or 'letter'");
            exit(1);
        }

        llvm::Value* initVal = static_cast<llvm::Value*>((yyvsp[(5) - (6)].llvm_ptr));
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
        (yyval.llvm_ptr) = (void*)typedPtr;
        free((yyvsp[(3) - (6)].string));
    }
    break;


/* Line 1792 of yacc.c  */
#line 3832 "proj.tab.c"
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


/* Line 2055 of yacc.c  */
#line 1962 "proj.y"


void yyerror(const char *s)
{
  fprintf(stderr, "Error: %s\n", s);
}