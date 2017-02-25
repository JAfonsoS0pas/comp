%X SINGLE MULTICOM

NUMBERS				[0-9]
CHARACTERS			[a-zA-Z]
UNDERSCORE			"_"
DOLLAR				"$"
NEWLINE 			"\n"
DOT 				"."
INITCOM				"/*"
FINISHCOM			"*/"
SINGLECOM			"//"

ID					({CHARACTERS}|"_")+({CHARACTERS}|"_"|{NUMBERS})*
DECLIT				("0"|[1-9]+|([1-9]+({NUMBERS}|{UNDERSCORE})*{NUMBERS}+))
REALLIT				({NUMBERS}{DOT}({NUMEBERS}|("E"|"e")("+"|"-")|({NUMBERS}({NUMBERS}+|{UNDERSCORE}+){NUMBERS})("E"|"e")("+"|"-") {NUMBERS}+?) | {DOT} 
STRLIT				"fidalgoooooo"

BOOL 				"boolean"
BOOLLIT				"true"|"false"
CLASS 				"class"
DO					"do"
DOTLENGTH			".length"
DOUBLE				"double"
ELSE				"else"
IF					"if"
INT 				"int"
PARSEINT			"Integer.parseInt"
PRINT 				"System.out.println"
PUBLIC 				"public"
RETURN 				"return"
STATIC 				"static"
STRING 				"String"
VOID 				"void"
WHILE 				"while"
OCURV 				"("
CCURV				")"
OBRACE 				"{"
CBRACE 				"}"
OSQUARE 			"["
CSQUARE 			"]"
AND 				"&&"
OR 					"||"
LT 					"<"
GT 					">"
EQ 					"=="
NEQ 				"!="
LEQ 				"<="
GEQ 				">="
PLUS 				"+"
MINUS 				"-"
STAR 				"*"
DIV 				"/"
MOD 				"%"
NOT 				"!"
ASSIGN 				"="
SEMI 				";"
COMMA 				","
RESERVED 			"++"|"null"|"--"



%%

{INITCOM}				{BEGIN MULTICOM;}
<MULTICOM>.				{;}
<MULTICOM>{NEWLINE}		{;}
<MULTICOM>{FINISHCOM}	{BEGIN 0;}

{SINGLECOM} 			{BEGIN SINGLE;}
<SINGLE>.				{;}
<SINGLE>{NEWLINE}		{BEGIN 0;}

{BOOL}				{printf("BOOL\n");}	
{BOOLLIT}			{printf("BOOLLIT\n");}	
{CLASS}				{printf("CLASS\n");}
{DO}				{printf("DO\n");}
{DOTLENGTH}			{printf("DOTLENGTH\n");}
{DOUBLE}			{printf("DOUBLE\n");}
{ELSE}				{printf("ELSE\n");}
{IF}				{printf("IF\n");}
{INT}				{printf("INT\n");}
{PARSEINT}			{printf("PARSEINT\n");}
{PRINT}				{printf("PRINT\n");}
{PUBLIC}			{printf("PUBLIC\n");}
{RETURN}			{printf("RETURN\n");}
{STATIC}			{printf("STATIC\n");}
{STRING}			{printf("STRING\n");}
{VOID}				{printf("VOID\n");}
{WHILE}				{printf("WHILE\n");}
{OCURV}				{printf("OCURV\n");}
{CCURV}				{printf("CCURV\n");}
{OBRACE}			{printf("OBRACE\n");}
{CBRACE}			{printf("CBRACE\n");}
{OSQUARE} 			{printf("OSQUARE\n");}
{CSQUARE} 			{printf("CSQUARE\n");}
{AND}				{printf("AND\n");}
{OR}				{printf("OR\n");}
{LT}				{printf("LT\n");}
{GT}				{printf("GT\n");}
{EQ}				{printf("EQ\n");}
{NEQ}				{printf("NEQ\n");}
{LEQ}				{printf("LEQ\n");}
{GEQ}				{printf("GEQ\n");}
{PLUS}				{printf("PLUS\n");}
{MINUS}				{printf("MINUS\n");}
{STAR}				{printf("STAR\n");}
{DIV}				{printf("DIV\n");}
{MOD}				{printf("MOD\n");}
{NOT}				{printf("NOT\n");}
{ASSIGN}			{printf("ASSIGN\n");}
{SEMI}				{printf("SEMI\n");}
{COMMA}				{printf("COMMA\n");}
{RESERVED} 			{printf("RESERVED\n");}
{ID}				{printf("ID(%s)\n", yytext);}
{DECLIT}			{printf("DECLIT(%s)\n",yytext);}
{NEWLINE}			{;}
.					{;}

%%

int main(){
	yylex();
	return 0;
}

int yywrap(){
	return 1;
}
