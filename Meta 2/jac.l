%{
	#include <stdio.h>
	#include "y.tab.h"
	
	
	#define LINHA linha++; coluna=1;
	#define COLUNA coluna+=yyleng;
	int flag ,error =0;	
	char save[256];
	
	
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
NEWLINE 			"\n"
SPACE 				" "
TAB					"\t"
CARRIAGERETURN 		"\r"
FORMFEED			"\f"
LINETERMINATOR		"\n"|{CARRIAGERETURN}|({CARRIAGERETURN})"\n"
SPECIALTERMINATOR	r\\n
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

ESCAPE              \\n|\\f|\\r|\\\\|\\\"|\\t

ID					({CHARACTERS}|{UNDERSCORE}|{DOLLAR})+({CHARACTERS}|{UNDERSCORE}|{DOLLAR}|{NUMBERS})*

DECLIT				([0]|([1-9]({SQ1}*{NUMBERS})*))

REALLIT				({SQ2}{DOT}(({SQ2}|({EXPOENTE}{SQ2}))|({SQ2}{EXPOENTE}{SQ2}))?)|{DOT}{SQ2}(({EXPOENTE}{SQ2})?)|({SQ2}{EXPOENTE}{SQ2})


STRLIT				([^\n\r\\\"]|{ESCAPE})*

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

{BOOL}				{print_text("BOOL"); COLUNA; if(flag==2) return BOOL;}	
{BOOLLIT}			{print_with_content("BOOLLIT",yytext);COLUNA; if(flag==2) return BOOLLIT;}	
{CLASS}				{print_text("CLASS"); COLUNA;if(flag==2) return CLASS;}
{DO}				{print_text("DO"); COLUNA;if(flag==2) return DO;}
{DOTLENGTH}			{print_text("DOTLENGTH");  COLUNA;if(flag==2) return DOTLENGTH;}
{DOUBLE}			{print_text("DOUBLE"); COLUNA;if(flag==2) return DOUBLE;}
{ELSE}				{print_text("ELSE"); COLUNA;if(flag==2) return ELSE;}
{IF}				{print_text("IF"); COLUNA;if(flag==2) return IF;}
{INT}				{print_text("INT"); COLUNA;if(flag==2) return INT;}
{PARSEINT}			{print_text("PARSEINT"); COLUNA;if(flag==2) return PARSEINT;}
{PRINT}				{print_text("PRINT"); COLUNA;if(flag==2) return PRINT;}
{PUBLIC}			{print_text("PUBLIC"); COLUNA;if(flag==2) return PUBLIC;}
{RETURN}			{print_text("RETURN"); COLUNA;if(flag==2) return RETURN;}
{STATIC}			{print_text("STATIC"); COLUNA;if(flag==2) return STATIC;}
{STRING}			{print_text("STRING"); COLUNA;if(flag==2) return STRING;}
{VOID}				{print_text("VOID"); COLUNA;if(flag==2) return VOID;}
{WHILE}				{print_text("WHILE"); COLUNA;if(flag==2) return WHILE;}
{OCURV}				{print_text("OCURV"); COLUNA;if(flag==2) return OCURV;}
{CCURV}				{print_text("CCURV"); COLUNA;if(flag==2) return CCURV;}
{OBRACE}			{print_text("OBRACE"); COLUNA;if(flag==2) return OBRACE;}
{CBRACE}			{print_text("CBRACE"); COLUNA;if(flag==2) return CBRACE;}
{OSQUARE} 			{print_text("OSQUARE"); COLUNA;if(flag==2) return OSQUARE;}
{CSQUARE} 			{print_text("CSQUARE"); COLUNA;if(flag==2) return CSQUARE;}
{AND}				{print_text("AND"); COLUNA;if(flag==2) return AND;}
{OR}				{print_text("OR"); COLUNA;if(flag==2) return OR;}
{LT}				{print_text("LT"); COLUNA;if(flag==2) return LT;}
{GT}				{print_text("GT"); COLUNA;if(flag==2) return GT;}
{EQ}				{print_text("EQ"); COLUNA;if(flag==2) return EQ;}
{NEQ}				{print_text("NEQ"); COLUNA;if(flag==2) return NEQ;}
{LEQ}				{print_text("LEQ"); COLUNA;if(flag==2) return LEQ;}
{GEQ}				{print_text("GEQ"); COLUNA;if(flag==2) return GEQ;}
{PLUS}				{print_text("PLUS");COLUNA;if(flag==2) return PLUS;}
{MINUS}				{print_text("MINUS");COLUNA;if(flag==2) return MINUS;}
{STAR}				{print_text("STAR");COLUNA;if(flag==2) return STAR;}
{DIV}				{print_text("DIV");COLUNA;if(flag==2) return DIV;}
{MOD}				{print_text("MOD");COLUNA;if(flag==2) return MOD;}
{NOT}				{print_text("NOT");COLUNA;if(flag==2) return NOT;}
{ASSIGN}			{print_text("ASSIGN");COLUNA;if(flag==2) return ASSIGN;}
{SEMI}				{print_text("SEMI");COLUNA;if(flag==2) return SEMI;}
{COMMA}				{print_text("COMMA");COLUNA;if(flag==2) return COMMA;}
{DECLIT}			{print_with_content("DECLIT",yytext); COLUNA;if(flag==2){yylval.string=(char*)strdup(yytext); return DECLIT;}}
{REALLIT}			{print_with_content("REALLIT",yytext); COLUNA;if(flag==2){yylval.string=(char*)strdup(yytext); return REALLIT;}}
{RESERVED} 			{print_with_content("RESERVED",yytext); COLUNA;if(flag==2) {yylval.string=(char*)strdup(yytext); return RESERVED;}}
{ID}				{print_with_content("ID", yytext); COLUNA; if(flag==2) {yylval.string=(char*)strdup(yytext); return ID;}}
{SPACE}						{COLUNA;}
{TAB}						{COLUNA;}
{LINETERMINATOR}			{LINHA;}
{FORMFEED}					{COLUNA;}

{INITCOM}															{BEGIN MULTICOM; l_actual= linha; c_actual= coluna;COLUNA;}
<MULTICOM>{FINISHCOM}												{BEGIN 0; COLUNA;}
<MULTICOM><<EOF>>													{BEGIN 0; printf("Line %d, col %d: unterminated comment\n", l_actual, c_actual);}
<MULTICOM>{LINETERMINATOR}											{LINHA;}
<MULTICOM>.															{COLUNA;}

{SINGLECOM}															{BEGIN SINGLE;COLUNA;}
<SINGLE>{LINETERMINATOR}											{BEGIN 0;LINHA;}
<SINGLE>.															{COLUNA;}

{ASPAS}												{BEGIN STRINGLIT; strcat(save, yytext); l_actual= linha; c_actual= coluna;COLUNA; error=0;}
<STRINGLIT>{STRLIT}									{COLUNA; strcat(save, yytext);}
<STRINGLIT>\\(.?)									{printf("Line %d, col %d: invalid escape sequence (%s)\n", linha, coluna, yytext);COLUNA;error=1;}
<STRINGLIT>{LINETERMINATOR}							{BEGIN 0; save[0]=0; printf("Line %d, col %d: unterminated string literal\n", l_actual, c_actual);LINHA;}
<STRINGLIT>{ASPAS}									{BEGIN 0;  strcat(save, yytext); if(error==0){print_with_content("STRLIT",save);} COLUNA;  if(flag==2){yylval.string=(char*)strdup(save); return STRLIT;} save[0]=0;}
<STRINGLIT><<EOF>>									{BEGIN 0; save[0]=0; printf("Line %d, col %d: unterminated string literal\n", l_actual, c_actual);LINHA;}



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


int yywrap(){
	return 1;
}

void yyerror (const char *s) { 
     printf ("Line %d, col %d: %s: %s\n",linha,(int)(coluna-strlen(yytext)), s, yytext);
}