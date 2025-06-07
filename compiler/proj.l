%{
#include "proj.tab.h"
%}
%option noyywrap

%%

"number"                    { return INT; }
"letter"                    { return CHAR; }
"word"                      { return STRING; }
"ptr"                       { return PTR; }
"dyn"                       { return DYN; }
"print"                     { return PRINT; }
"if"                        { return IF; }
"else"                      { return ELSE; }
"end"                       { return END; }
"while"                     { return WHILE; }
"and"                       { yylval.num = AND; return AND; }
"or"                        { yylval.num = OR; return OR; }
"for"                       { return FOR; }
"to"                        { return TO; }
"step"                      { return STEP; }
"break"                     { return BREAK; }
"switch"                    { return SWITCH; }
"case"                      { return CASE; }
"default"                   { return DEFAULT; }
"function"                  { return FUNCTION; }
"void"                      { return VOID; }
"return"                    { return RETURN; }
"struct"                    { return STRUCT; }
"."                         { return DOT; }
[a-zA-Z_][a-zA-Z0-9_]*      { yylval.identifier = strdup(yytext); return IDENTIFIER; }
[0-9]+                      { yylval.num = atoi(yytext); return NUMBER; }
"'"[a-zA-Z]"'"              { yylval.ch = yytext[1]; return CHAR_LITERAL; }
\"([^\"]*)\"                { yylval.string = strdup(yytext + 1); yylval.string[strlen(yylval.string) - 1] = '\0'; return STRING_LITERAL; }
"="                         { return ASSIGN; }
"+"                         { yylval.num = PLUS; return OPERATOR; }
"-"                         { yylval.num = MINUS; return OPERATOR; }
"*"                         { yylval.num = MUL; return OPERATOR; }
"/"                         { yylval.num = DIV; return OPERATOR; }
"<"                         { yylval.num = LESSTHAN; return OPERATOR; }
">"                         { yylval.num = GREATERTHAN; return OPERATOR; }
"<="                        { yylval.num = LESSEQUAL; return OPERATOR; }
">="                        { yylval.num = GREATEREQUAL; return OPERATOR; }
"=="                        { yylval.num = EQUAL; return OPERATOR; }
"!="                        { yylval.num = NOTEQUAL; return OPERATOR; }
"&&"                        { yylval.num = AND; return AND; }
"||"                        { yylval.num = OR; return OR; }
"++"                        { yylval.num = INCREMENT; return ADDSUB; }
"--"                        { yylval.num = DECREMENT; return ADDSUB; }
"("                         { return LPAREN; }
")"                         { return RPAREN; }
"{"                         { return LBRACE; }
"}"                         { return RBRACE; }
"["                         { return LBRACKET; }
"]"                         { return RBRACKET; }
","                         { return COMMA; }
";"                         { return SEMICOLON; }
"&"                         { return AMPERSAND; }
[ \t\n]+                    {}
.                           { printf("Unexpected: %c\n", *yytext); exit(1); }

%%