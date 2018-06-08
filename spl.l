%{
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "cst.h"
#include "symtab.h"
#include "spl.tab.h"
extern "C" int yylex();
extern "C" void yyerror(const char* s);
int installId(char*, unsigned);
int lookup(char*);
extern sym_tab_node symtab[];
extern int currentSymTabSize;
#define TOKEN(tok)  { return(tok);}
%}

delimiter       [\t\n\r ]
digit           [0-9]
char            [a-zA-Z]
char_const      \'.\'
string_const    \'.*\'
real            ({digit}+\.{digit}+)|(\.{digit}+)
integer         {digit}+
id              {char}({char}|{digit})*
ws              {delimiter}+
comment         (\{.*\}|\(\*.*\*\)|\/\/.*)

%%

"("         TOKEN(T_LP)
")"         TOKEN(T_RP)
"["         TOKEN(T_LB)
"]"         TOKEN(T_RB)
"."         TOKEN(T_DOT)
","         TOKEN(T_COMMA)
":"         TOKEN(T_COLON)
"+"         TOKEN(T_PLUS)
"-"         TOKEN(T_MINUS)
"*"         TOKEN(T_MUL)
"/"         TOKEN(T_DIV)
">"         TOKEN(T_GT)
"<"         TOKEN(T_LT)
"="         TOKEN(T_EQUAL)
"<>"        TOKEN(T_NE)
"<="        TOKEN(T_LE)
">="        TOKEN(T_GE)
":="        TOKEN(T_ASSIGN)
"NOT"       TOKEN(T_NOT)
"MOD"       TOKEN(T_MOD)
"%"         TOKEN(T_MOD)
".."        TOKEN(T_DOTDOT)
";"         TOKEN(T_SEMI)

"and"       TOKEN(T_AND)
"array"     TOKEN(T_ARRAY)
"begin"     TOKEN(T_BEGIN)
"case"      TOKEN(T_CASE)
"const"     TOKEN(T_CONST)
"do"        TOKEN(T_DO)
"downto"    TOKEN(T_DOWNTO)
"else"      TOKEN(T_ELSE)
"end"       TOKEN(T_END)
"for"       TOKEN(T_FOR)
"function"  TOKEN(T_FUNCTION)
"goto"      TOKEN(T_GOTO)
"if"        TOKEN(T_IF)
"in"        TOKEN(T_IN)
"of"        TOKEN(T_OF)
"or"        TOKEN(T_OR)
"packed"    TOKEN(T_PACKED)
"procedure" TOKEN(T_PROCEDURE)
"program"   TOKEN(T_PROGRAM)
"record"    TOKEN(T_RECORD)
"repeat"    TOKEN(T_REPEAT)
"set"       TOKEN(T_SET)
"then"      TOKEN(T_THEN)
"to"        TOKEN(T_TO)
"type"      TOKEN(T_TYPE)
"until"     TOKEN(T_UNTIL)
"var"       TOKEN(T_VAR)
"while"     TOKEN(T_WHILE)
"with"      TOKEN(T_WITH)

"false"     TOKEN(T_FALSE)
"true"      TOKEN(T_TRUE)
"maxint"    TOKEN(T_MAXINT)
"abs"       TOKEN(T_ABS)
"chr"       TOKEN(T_CHR)
"odd"       TOKEN(T_ODD)
"ord"       TOKEN(T_ORD)
"pred"      TOKEN(T_PRED)
"sqr"       TOKEN(T_SQR)
"sqrt"      TOKEN(T_SQRT)
"succ"      TOKEN(T_SUCC)
"write"     TOKEN(T_WRITE)
"writeln"   TOKEN(T_WRITELN)
"read"      TOKEN(T_READ)
"boolean"   TOKEN(T_BOOLEAN)
"char"      TOKEN(T_CHAR)
"integer"   TOKEN(T_INTEGER)
"real"      TOKEN(T_REAL)
"string"    TOKEN(T_STRING)

{id}                { yylval.iVal = installId(yytext, 0); return S_ID; }
{char_const}        { yylval.iVal = installId(yytext, 2); return S_CHAR; }
{string_const}      { yylval.iVal = installId(yytext, 4); return S_STRING; }
{integer}           { yylval.iVal = atoi(yytext); return S_INTEGER; }
{real}              { yylval.iVal = installId(yytext, 1); return S_REAL; }
{ws}                // do nothing
{comment}           // do nothing
.                   printf("ERROR. Unexpected symbol found. %s %d\n", yytext, yytext[0]);

%%

// 
int installId(char* id, unsigned type = -1) {
    // convert to lower case
    char lower_id[100];
    strcpy(lower_id, id);
    for (char* p = lower_id; *p; p++) *p = tolower(*p);
    extern sym_tab_node symtab[];
    extern int currentSymTabSize;
    int result = lookup(id);
    // new symbol
    if (result == -1) {
        strcpy(symtab[currentSymTabSize].id, id);
        symtab[currentSymTabSize].type = type;
        return currentSymTabSize++;
    }
    // old symbol
    else {
        return result;
    }
}
int lookup(char* id) {
    // convert to lower case
    char lower_id[100];
    strcpy(lower_id, id);
    for (char* p = lower_id; *p; p++) *p = tolower(*p);

    extern sym_tab_node symtab[];
    extern int currentSymTabSize;
    for (int i = 0; i < currentSymTabSize; i++) {
        if (strcmp(id, symtab[i].id) == 0) {
            return i;
        }
    }
    return -1;
}
