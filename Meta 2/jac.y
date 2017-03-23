%{
	#include "arvo.h"
    #include <stdio.h>
    int yylex(void);
    void yyerror (const char *s);
    no* root;

%}

 
%union{
int inteiro;
char* string;
no* node
}

%token BOOL BOOLLIT CLASS DO DOTLENGTH DOUBLE ELSE IF INT PARSEINT PRINT PUBLIC RETURN STATIC STRING VOID WHILE OCURV CCURV OBRACE CBRACE OSQUARE CSQUARE AND OR LT GT EQ NEQ LEQ GEQ PLUS MINUS STAR DIV MOD NOT ASSIGN SEMI COMMA
%token <string> STRLIT DECLIT REALLIT ID RESERVED

%type <node> Program ProgramL FieldDecl FieldDecl2 MethodDecl MethodHeader MethodHeader3 MethodBody MethodBody2 FormalParams FormalALt VarDecl VarDecl2 Type Statement StatementAux StatementZeroMais PrintAux ExprAux Assignment MethodInvocation MethodInvocation2 ExprAux2 ParseArgs Expr Expr1 Expr6 Expr7


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
%nonassoc ELSE RETURN REALLIT STRLIT IF 



%%
Program: CLASS ID OBRACE ProgramL CBRACE		 			{create(root_node, "" ,"Program"); $$=root; addnode($$, $2);printftree(root, 1);}
		;
ProgramL: %empty											{$$=NULL;}
		| FieldDecl 	ProgramL							{$$=$1; addbro($$,$1);}
		| MethodDecl 	ProgramL							{$$=$1; addbro($$,$1);}
		| SEMI			ProgramL							{$$=$1; addbro($$,$1);}
		;	

FieldDecl: PUBLIC STATIC Type ID FieldDecl2 SEMI 			{create(fdec_node, "", "FieldDecl"); addnode($$,$3); addbro($3, $4);}
		| error SEMI 										{;}
		;
FieldDecl2: %empty 											{$$=NULL;}
		| COMMA ID FieldDecl2 								{addbro($$, $1);addbro($1,$2);}
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


