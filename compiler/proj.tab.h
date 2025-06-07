/* A Bison parser, made by GNU Bison 2.7.  */

/* Bison interface for Yacc-like parsers in C
   
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
/* Line 2058 of yacc.c  */
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


/* Line 2058 of yacc.c  */
#line 176 "proj.tab.h"
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
