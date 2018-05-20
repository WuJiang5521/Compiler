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

delimiter   [\t\n\r ]
char        [a-zA-Z]
char_const  '\[a-zA-Z]\'
digit       [0-9]
integer     {digit}+
float       ({digit}\.{digit}*)|(.{digit}+)
id          {char}({char}|{digit})*
ws          {delimiter}+

%%

"("         TOKEN(LP)
")"         TOKEN(RP)
"["         TOKEN(LB)
"]"         TOKEN(RB)
"."         TOKEN(DOT)
","         TOKEN(COMMA)
":"         TOKEN(COLON)
"+"         TOKEN(PLUS)
"-"         TOKEN(MINUS)
"*"         TOKEN(MUL)
"/"         TOKEN(DIV)
">"         TOKEN(GT)
"<"         TOKEN(LT)
"="         TOKEN(EQUAL)
"<>"        TOKEN(NE)
"<="        TOKEN(LE)
">="        TOKEN(GE)
":="        TOKEN(ASSIGN)
"NOT"       TOKEN(NOT)
"MOD"       TOKEN(MOD)
".."        TOKEN(DOTDOT)
";"         TOKEN(SEMI)

"and"       TOKEN(AND)
"array"     TOKEN(ARRAAY)
"begin"     TOKEN(BEGIN)
"case"      TOKEN(CASE)
"const"     TOKEN(CONST)
"div"       TOKEN(DIV)
"do"        TOKEN(DO)
"downto"    TOKEN(DOWNTO)
"else"      TOKEN(ELSE)
"end"       TOKEN(END)
"for"       TOKEN(FOR)
"function"  TOKEN(FUNCTION)
"goto"      TOKEN(GOTO)
"if"        TOKEN(IF)
"in"        TOKEN(IN)
"of"        TOKEN(OF)
"or"        TOKEN(OR)
"packed"    TOKEN(PACKED)
"procedure" TOKEN(PROCEDURE)
"program"   TOKEN(PROGRAM)
"record"    TOKEN(RECORD)
"repeat"    TOKEN(REPEAT)
"set"       TOKEN(SET)
"then"      TOKEN(THEN)
"to"        TOKEN(TO)
"type"      TOKEN(TYPE)
"until"     TOKEN(UNTIL)
"var"       TOKEN(VAR)
"while"     TOKEN(WHILE)
"with"      TOKEN(WITH)

"false"     TOKEN(FALSE)
"true"      TOKEN(TRUE)
"maxint"    TOKEN(MAXINT)
"abs"       TOKEN(ABS)
"chr"       TOKEN(CHR)
"odd"       TOKEN(ODD)
"ord"       TOKEN(ORD)
"pred"      TOKEN(PRED)
"sqr"       TOKEN(SQR)
"sqrt"      TOKEN(SQRT)
"succ"      TOKEN(SUCC)
"write"     TOKEN(WRITE)
"writeln"   TOKEN(WRITELN)
"boolean"   TOKEN(BOOLEAN)
"char"      TOKEN(CHAR)
"integer"   TOKEN(INTEGER)
"real"      TOKEN(REAL)

{id}            SYMBOL(ID)
{char_const}    SYMBOL(CHAR)
{integer}       SYMBOL(INTEGER)
{float}         SYMBOL(FLOAT)
{ws}            // do nothing
.               printf("ERROR. Unexpected symbol found. %s %d\n", yytext, yytext[0]);

%%
