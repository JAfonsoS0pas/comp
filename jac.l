
%{
	#include <stdio.h>
	#include <string.h>
	
	#define LINHA linha++; coluna=1;
	#define COLUNA coluna+=yyleng;
	int flag = 0,error =0;	
	char *save;
	
	
	void print_text(char* text);
	void print_with_content(char* text, char* content);
	int linha =1;
	int coluna=1;
	int c_actual=1;
	int l_actual=1;
	
%}

%X SINGLE MULTICOM STRINGLIT

NUMBERS				[0-9]
CHARACTERS			[a-zA-Z]
UNDERSCORE			"_"
DOLLAR				"$"
NEWLINE 			\\n
SPACE 				" "
TAB					\\t
CARRIAGERETURN 		"\r"
FORMFEED			"\f"
LINETERMINATOR		"\n"|{CARRIAGERETURN}|({CARRIAGERETURN})"\n"
DOT 				"."
DOUBLEDOT			":"
INITCOM				"/*"
FINISHCOM			"*/"
SINGLECOM			"//"

BB					\\\\
SQ1					({NUMBERS}|{UNDERSCORE})
SQ2					{NUMBERS}+({SQ1}*{NUMBERS})*
EXPOENTE			("E"|"e")("+"|"-")?
ASPAS				\"

ESCAPE              {FORMFEED}|{BB}|{TAB}

ID					({CHARACTERS}|{UNDERSCORE}|{DOLLAR})+({CHARACTERS}|{UNDERSCORE}|{DOLLAR}|{NUMBERS})*

DECLIT				([0]|([1-9]({SQ1}*{NUMBERS})*))

REALLIT				({SQ2}{DOT}(({SQ2}|({EXPOENTE}{SQ2}))|({SQ2}{EXPOENTE}{SQ2}))?)|{DOT}{SQ2}(({EXPOENTE}{SQ2})?)|({SQ2}{EXPOENTE}{SQ2})


STRLIT				([^\n\r\\"]|{ESCAPE})*
INVALIDESCAPE 		(\\([^{STRLIT}]))*





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
RESERVED 			"++"|"null"|"--"|"abstract"|"assert"|"break"|"byte"|"case"|"catch"|"char"|"const"|"continue"|"default"|"enum"|"extends"|"final"|"finally"|"float"|"for"|"goto"|"implements"|"import"|"instanceof"|"interface"|"Integer"|"long"|"native"|"new"|"package"|"private"|"protected"|"short"|"strictfp"|"super"|"switch"|"synchronized"|"System"|"this"|"throw"|"throws"|"transient"|"try"|"volatile"



%%

{BOOL}				{print_text("BOOL"); COLUNA;}	
{BOOLLIT}			{print_with_content("BOOLLIT",yytext);COLUNA;}	
{CLASS}				{print_text("CLASS"); COLUNA;}
{DO}				{print_text("DO"); COLUNA;}
{DOTLENGTH}			{print_text("DOTLENGTH");  COLUNA;}
{DOUBLE}			{print_text("DOUBLE"); COLUNA;}
{ELSE}				{print_text("ELSE"); COLUNA;}
{IF}				{print_text("IF"); COLUNA;}
{INT}				{print_text("INT"); COLUNA;}
{PARSEINT}			{print_text("PARSEINT"); COLUNA;}
{PRINT}				{print_text("PRINT"); COLUNA;}
{PUBLIC}			{print_text("PUBLIC"); COLUNA;}
{RETURN}			{print_text("RETURN"); COLUNA;}
{STATIC}			{print_text("STATIC"); COLUNA;}
{STRING}			{print_text("STRING"); COLUNA;}
{VOID}				{print_text("VOID"); COLUNA;}
{WHILE}				{print_text("WHILE"); COLUNA;}
{OCURV}				{print_text("OCURV"); COLUNA;}
{CCURV}				{print_text("CCURV"); COLUNA;}
{OBRACE}			{print_text("OBRACE"); COLUNA;}
{CBRACE}			{print_text("CBRACE"); COLUNA;}
{OSQUARE} 			{print_text("OSQUARE"); COLUNA;}
{CSQUARE} 			{print_text("CSQUARE"); COLUNA;}
{AND}				{print_text("AND"); COLUNA;}
{OR}				{print_text("OR"); COLUNA;}
{LT}				{print_text("LT"); COLUNA;}
{GT}				{print_text("GT"); COLUNA;}
{EQ}				{print_text("EQ"); COLUNA;}
{NEQ}				{print_text("NEQ"); COLUNA;}
{LEQ}				{print_text("LEQ"); COLUNA;}
{GEQ}				{print_text("GEQ"); COLUNA;}
{PLUS}				{print_text("PLUS");COLUNA;}
{MINUS}				{print_text("MINUS");COLUNA;}
{STAR}				{print_text("STAR");COLUNA;}
{DIV}				{print_text("DIV");COLUNA;}
{MOD}				{print_text("MOD");COLUNA;}
{NOT}				{print_text("NOT");COLUNA;}
{ASSIGN}			{print_text("ASSIGN");COLUNA;}
{SEMI}				{print_text("SEMI");COLUNA;}
{COMMA}				{print_text("COMMA");COLUNA;}
{DECLIT}			{print_with_content("DECLIT",yytext); COLUNA;}
{REALLIT}			{print_with_content("REALLIT",yytext); COLUNA;}
{RESERVED} 			{print_with_content("RESERVED",yytext); COLUNA;}
{ID}				{print_with_content("ID", yytext); COLUNA;}
{SPACE}						{COLUNA;}
"\t"						{COLUNA;}
{FORMFEED}					{COLUNA;}
{LINETERMINATOR}			{LINHA;}

{INITCOM}															{BEGIN MULTICOM; l_actual= linha; c_actual= coluna;COLUNA;}
<MULTICOM>{FINISHCOM}												{BEGIN 0; COLUNA;}
<MULTICOM><<EOF>>													{BEGIN 0; printf("Line %d, col %d: unterminated comment\n", l_actual, c_actual);}
<MULTICOM>{LINETERMINATOR}											{LINHA;}
<MULTICOM>.															{COLUNA;}

{SINGLECOM}															{BEGIN SINGLE;COLUNA;}
<SINGLE>{LINETERMINATOR}											{BEGIN 0;LINHA;}
<SINGLE>.															{COLUNA;}

{ASPAS}{STRLIT}														{BEGIN STRINGLIT; save = yytext; l_actual= linha; c_actual= coluna;COLUNA; error=0;}
<STRINGLIT>{INVALIDESCAPE}											{printf("Line %d, col %d: invalid escape sequence (%s)\n", linha, coluna, yytext);COLUNA;error=1;}
<STRINGLIT>{LINETERMINATOR}											{BEGIN 0; printf("Line %d, col %d: unterminated string literal\n", l_actual, c_actual);LINHA;}
<STRINGLIT><<EOF>>													{BEGIN 0; printf("Line %d, col %d: unterminated string literal\n", l_actual, c_actual);LINHA;}
<STRINGLIT>{ASPAS}													{BEGIN 0; if(error==0){print_with_content("STRLIT",save);} COLUNA;}
<STRINGLIT>.														{COLUNA;}



.																	{printf("Line %d, col %d: illegal character (%s)\n", linha, coluna, yytext);COLUNA};







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
	}
	yylex();
	return 0;
}

int yywrap(){
	return 1;
}
