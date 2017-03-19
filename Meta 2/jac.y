%{
    #include <stdio.h>
    int yylex(void);
    void yyerror (const char *s);
%}

 
%union{
int inteiro;
char* string;
}

%token BOOL BOOLLIT CLASS DO DOTLENGTH DOUBLE ELSE IF INT PARSEINT PRINT PUBLIC RETURN STATIC STRING VOID WHILE OCURV CCURV OBRACE CBRACE OSQUARE CSQUARE AND OR LT GT EQ NEQ LEQ GEQ PLUS MINUS STAR DIV MOD NOT ASSIGN SEMI COMMA
%token <string> STRLIT DECLIT REALLIT ID RESERVED



%left COMMA
%right ASSIGN

%left OR
%left AND 
%left EQ NEQ
%left LT LEQ GEQ GT
%left PLUS MINUS
%left STAR DIV MOD

%right NOT
%left OBRACE OCURV CCURV OSQUARE CSQUARE
%nonassoc ELSE



%%
Program: CLASS ID OBRACE ProgramL CBRACE		 			{;}
		;
ProgramL: %empty											{;}
		| FieldDecl 	ProgramL							{;}
		| MethodDecl 	ProgramL							{;}
		| SEMI			ProgramL							{;}
		;	

FieldDecl: PUBLIC STATIC Type ID FieldDecl2 SEMI 			{;}
		| error SEMI 										{;}
		;
FieldDecl2: %empty 											{;}
		| COMMA ID FieldDecl2 								{;}
		;


MethodDecl: PUBLIC STATIC MethodHeader MethodBody 			{;}
		;
MethodHeader: Type ID OCURV MethodHeader3 CCURV 			{;}
		| VOID ID OCURV MethodHeader3 CCURV 				{;}
		;
MethodHeader3: %empty 										{;}
		| FormalParams 										{;}
		; 

MethodBody: OBRACE MethodBody2 CBRACE 						{;}
		;
MethodBody2: %empty 										{;}
		| VarDecl 		MethodBody2 						{;}
		| Statement 	MethodBody2							{;}
		;

FormalParams: Type ID FormalALt 							{;}
		| STRING OSQUARE CSQUARE ID 						{;}
		;
FormalALt: %empty 											{;}
	   	| COMMA Type ID FormalALt 							{;}
		;

VarDecl: Type ID VarDecl2 SEMI 								{;}
		;
VarDecl2: %empty 											{;}
		| COMMA ID VarDecl2 								{;}
		;	

Type: BOOL 													{;}
		| INT 												{;}
		| DOUBLE 											{;}
		;


Statement: OBRACE StatementZeroMais CBRACE					{;}
		| IF OCURV Expr CCURV Statement 					{;}
		| IF OCURV Expr CCURV Statement ELSE Statement		{;}
		| WHILE OCURV Expr CCURV Statement 					{;}
		| DO Statement WHILE OCURV Expr CCURV SEMI 			{;}
		| PRINT OCURV PrintAux CCURV SEMI  					{;}
		| StatementAux SEMI 								{;}
		| RETURN ExprAux SEMI 								{;}
		| error SEMI 										{;}
		;
StatementZeroMais: %empty									{;}
		| Statement StatementZeroMais						{;}
		;

StatementAux: %empty										{;}
		| Assignment 										{;}
		| MethodInvocation 									{;}
		| ParseArgs 										{;}
		;
PrintAux: Expr 												{;}
		| STRLIT 											{;}
		;
ExprAux: %empty 											{;}
		| Expr 												{;}
		;

Assignment: ID ASSIGN Expr 									{;}
		;
MethodInvocation: ID OCURV MethodInvocation2 CCURV 			{;}
		| ID OCURV error CCURV 								{;}
		;
MethodInvocation2: %empty 									{;}
		| Expr ExprAux2 									{;}
		;
ExprAux2: %empty 											{;}
		| COMMA Expr ExprAux2 								{;}
		;
ParseArgs: PARSEINT OCURV ID OSQUARE Expr CSQUARE CCURV 	{;}
		| PARSEINT OCURV error CCURV						{;}
		;
Expr: Expr1													{;}
		| Expr AND Expr 									{;}
		| Expr OR Expr 										{;}
		| Expr EQ Expr 										{;}
		| Expr GEQ Expr 									{;}
		| Expr GT Expr 										{;}
		| Expr LEQ Expr 									{;}
		| Expr LT Expr 										{;}
		| Expr NEQ Expr 									{;}
		| Expr PLUS Expr 									{;}
		| Expr MINUS Expr 									{;}
		| Expr STAR Expr 									{;}
		| Expr DIV Expr 									{;}
		| Expr MOD Expr 									{;}
		| PLUS Expr 										{;}
		| MINUS Expr 										{;}
		| NOT Expr 											{;}
		| ID Expr6 											{;}
		| OCURV Expr CCURV 									{;}
		| OCURV error CCURV 								{;}
		| Expr7 											{;}
		;
Expr1: Assignment											{;}
		| MethodInvocation 									{;}
		| ParseArgs 										{;}
		;
Expr6: %empty 												{;}
		| DOTLENGTH 										{;}
		;
Expr7: BOOLLIT 												{;}
		| DECLIT 											{;}
		| REALLIT 											{;}
		;
%%


