%{
	#include <stdio.h>
	#include <string.h>

	int flag = 0;	

	void print_text(char* text);
	void print_with_content(char* text, char* content);
%}

%X SINGLE MULTICOM

NUMBERS				[0-9]
CHARACTERS			[a-zA-Z]
UNDERSCORE			"_"
DOLLAR				"$"
NEWLINE 			"\n"
SPACE 				" "
TAB					"\t"
CARRIAGERETURN 		"\r"
FORMFEED			"\f"
DOT 				"."
INITCOM				"/*"
FINISHCOM			"*/"
SINGLECOM			"//"
SQ1			({NUMBERS}+|{UNDERSCORE}+)
SQ2			{SQENUND}+{NUMBERS}
EXPOENTE		("E"|"e")("+"|"-")

ESCAPE				{SPACE}|{TAB}|{FORMFEED}|{CARRIAGERETURN}|{NEWLINE}

ID					({CHARACTERS}|"_")+({CHARACTERS}|"_"|{NUMBERS})*
DECLIT				("0"|([1-9]{SQ1}+{NUMBERS}))

REALLIT				({SQ2}{DOT}(({SQ2}|({EXPOENTE}{SQ2})) | ({SQ2}{EXPOENTE}{SQ2}))? ) |({DOT}{SQ2}({EXPOENTE}{SQ2})? ) | ({SQ2}{EXPOENTE}{SQ2})

STRLIT				

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
RESERVED 			"++"|"null"|"--"|"abstract"|"assert"|"break"|"byte"|"case"|"catch"|"char"|"const"|"continue"|"default"|"enum"|"extends"|"final"|"finally"|"float"|"goto"|"implements"|"import"|"instanceof"|"interface"|"long"|"native"|"new"|"package"|"private"|"protected"|"short"|"strictfp"|"super"|"switch"|"synchronized"|"this"|"throw"|"throws"|"transient"|"try"|"volatile"



%%

{INITCOM}				{BEGIN MULTICOM;}
<MULTICOM>.				{;}
<MULTICOM>{ESCAPE}		{;}
<MULTICOM>{FINISHCOM}	{BEGIN 0;}

{SINGLECOM} 			{BEGIN SINGLE;}
<SINGLE>.				{;}
<SINGLE>{NEWLINE}		{BEGIN 0;}

{BOOL}				{print_text("BOOL");}	
{BOOLLIT}			{print_text("BOOLLIT");}	
{CLASS}				{print_text("CLASS");}
{DO}				{print_text("DO");}
{DOTLENGTH}			{print_text("DOTLENGTH");}
{DOUBLE}			{print_text("DOUBLE");}
{ELSE}				{print_text("ELSE");}
{IF}				{print_text("IF");}
{INT}				{print_text("INT");}
{PARSEINT}			{print_text("PARSEINT");}
{PRINT}				{print_text("PRINT");}
{PUBLIC}			{print_text("PUBLIC");}
{RETURN}			{print_text("RETURN");}
{STATIC}			{print_text("STATIC");}
{STRING}			{print_text("STRING");}
{VOID}				{print_text("VOID");}
{WHILE}				{print_text("WHILE");}
{OCURV}				{print_text("OCURV");}
{CCURV}				{print_text("CCURV");}
{OBRACE}			{print_text("OBRACE");}
{CBRACE}			{print_text("CBRACE");}
{OSQUARE} 			{print_text("OSQUARE");}
{CSQUARE} 			{print_text("CSQUARE");}
{AND}				{print_text("AND");}
{OR}				{print_text("OR");}
{LT}				{print_text("LT");}
{GT}				{print_text("GT");}
{EQ}				{print_text("EQ");}
{NEQ}				{print_text("NEQ");}
{LEQ}				{print_text("LEQ");}
{GEQ}				{print_text("GEQ");}
{PLUS}				{print_text("PLUS");}
{MINUS}				{print_text("MINUS");}
{STAR}				{print_text("STAR");}
{DIV}				{print_text("DIV");}
{MOD}				{print_text("MOD");}
{NOT}				{print_text("NOT");}
{ASSIGN}			{print_text("ASSIGN");}
{SEMI}				{print_text("SEMI");}
{COMMA}				{print_text("COMMA");}
{RESERVED} 			{print_text("RESERVED");}
{ID}				{print_with_content("ID", yytext);}
{DECLIT}			{print_with_content("DECLIT",yytext);}
{ESCAPE}			{;}
.					{;}

%%

void print_text(char* text){
	if(flag == 1){
		printf("%s\n",text);
	}
}

void print_with_content(char* text, char* content){
	if(flag == 1){
		printf("%s(%s)\n",text,content);
	}
}

int main(int argc, char *argv[]){
	if(argc > 1){
		if(strcmp(argv[1],"-l") == 0 || strcmp(argv[1],"-1") == 0){
			flag=1;
		}
		printf("flag -> %d\n", flag);
	}
	yylex();
	return 0;
}

int yywrap(){
	return 1;
}
