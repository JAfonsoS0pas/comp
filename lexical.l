NUMBERS				[0-9]
CHARACTERS			[a-zA-Z]

%%
{NUMBERS}+			{printf("Numeros: %s\n",yytext);}
{CHARACTERS}+			{printf("Letras: %s\n",yytext);}
.					{;}
%%
int main(){
	yylex();
	return 0;
}

int yywrap(){
	return 1;
}