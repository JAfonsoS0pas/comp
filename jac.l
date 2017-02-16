NUMBERS				[0-9]
CHARACTERS			[a-zA-Z]
NEWLINE 			"\n"

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