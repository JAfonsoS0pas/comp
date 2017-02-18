NUMBERS				[0-9]
CHARACTERS			[a-zA-Z]
UNDERSCORE			"_"
DOLLAR				"$"
NEWLINE 			"\n"

ID					
DECLIT				
REALLIT
STRLIT

BOOL 				"boolean"
BOOLIT				["true"|"false"]
CLASS 				"class"
DOLLAR				"do"
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
RESERVED 			["++"|"--"|"null"]


%%
{NUMBERS}+			{printf("Numeros: %s\n",yytext);}
{CHARACTERS}+			{printf("Letras: %s\n",yytext);}
{NEWLINE}				{;}
.					{;}
%%
int main(){
	yylex();
	return 0;
}

int yywrap(){
	return 1;
}