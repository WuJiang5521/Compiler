%{
#ifdef DEBUG_PRINT 
#define TOKEN(tok)  printf(#tok "\n");
#define SYMBOL(sym) printf(#sym ": %s\n", yytext);
#else
//int installId(char*, unsigned);
//int lookup(char*);
//SYMTABNODEPTR newSymTabNode();
//extern SYMTABNODEPTR symTab[SYMTABSIZE];
//extern int currentSymTabSize;
//#define TOKEN(tok)  return(T_##x);
//#define SYMBOL(sym) yylval.iVal = installId(yytext, T_##x); TOKEN(x);
#endif
%}

delimiter       [\t\n\r ]
char            [a-zA-Z]
char_const      '\[a-zA-Z]\'
string_const    "\[a-zA-Z]*\"
digit           [0-9]
integer         {digit}+
real            ({digit}\.{digit}*)|(.{digit}+)
id              {char}({char}|{digit})*
ws              {delimiter}+

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

{id}                SYMBOL(S_ID)
{char_const}        SYMBOL(S_CHAR)
{string_const}      SYMBOL(S_STRING)
{integer}           SYMBOL(S_INTEGER)
{real}              SYMBOL(S_REAL)
{ws}            // do nothing
.               printf("ERROR. Unexpected symbol found. %s %d\n", yytext, yytext[0]);

%%

