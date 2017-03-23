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
Program: CLASS ID OBRACE ProgramL CBRACE		 			{$$=create(root_node, "" ,"Program"); $$=root; addnode($$, $2);}
		;
ProgramL: %empty											{$$=NULL;}
		| FieldDecl 	ProgramL							{$$=$1; addbro($$,$1);}
		| MethodDecl 	ProgramL							{$$=$1; addbro($$,$1);}
		| SEMI			ProgramL							{$$=$1; addbro($$,$1);}
		;	

FieldDecl: PUBLIC STATIC Type ID FieldDecl2 SEMI 			{$$=create(var_node, "", "FieldDecl"); addnode($$,$3); addbro($3, create(id_node,$4,"Id"));}
		| error SEMI 										{$$=NULL;}
		;
FieldDecl2: %empty 											{$$=NULL;}
		| COMMA ID FieldDecl2 								{addbro($$, $1);addbro($1, create(id_node, $2, "Id"));}
		;


MethodDecl: PUBLIC STATIC MethodHeader MethodBody 			{$$=create(fdec_node,"","MethodDecl");}
		;
MethodHeader: Type ID OCURV MethodHeader3 CCURV 			{;}
		| VOID ID OCURV MethodHeader3 CCURV 				{;}
		;
MethodHeader3: %empty 										{$$=NULL;}
		| FormalParams 										{$$=$1;}
		; 

MethodBody: OBRACE MethodBody2 CBRACE 						{;}
		;
MethodBody2: %empty 										{$$=NULL;}
		| VarDecl 		MethodBody2 						{;}
		| Statement 	MethodBody2							{;}
		;

FormalParams: Type ID FormalALt 							{;}
		| STRING OSQUARE CSQUARE ID 						{;}
		;
FormalALt: %empty 											{$$=NULL;}
	   	| COMMA Type ID FormalALt 							{;}
		;

VarDecl: Type ID VarDecl2 SEMI 								{;}
		;
VarDecl2: %empty 											{$$=NULL;}
		| COMMA ID VarDecl2 								{;}
		;	

Type: 	BOOL 												{$$=create(ter_node,"","Type");}
		| INT 												{$$=create(ter_node,"","Type");}
		| DOUBLE 											{$$=create(ter_node,"","Type");}
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
StatementZeroMais: %empty									{$$=NULL;}
		| Statement StatementZeroMais						{;}
		;

StatementAux: %empty										{$$=NULL;}
		| Assignment 										{;}
		| MethodInvocation 									{;}
		| ParseArgs 										{;}
		;
PrintAux: Expr 												{;}
		| STRLIT 											{;}
		;
ExprAux: %empty 											{$$=NULL;}
		| Expr 												{;}
		;

Assignment: ID ASSIGN Expr 									{;}
		;
MethodInvocation: ID OCURV MethodInvocation2 CCURV 			{;}
		| ID OCURV error CCURV 								{;}
		;
MethodInvocation2: %empty 									{$$=NULL;}
		| Expr ExprAux2 									{;}
		;
ExprAux2: %empty 											{$$=NULL;}
		| COMMA Expr ExprAux2 								{;}
		;
ParseArgs: PARSEINT OCURV ID OSQUARE Expr CSQUARE CCURV 	{;}
		| PARSEINT OCURV error CCURV						{;}
		;
Expr: Expr1													{$$=NULL;}
		| Expr AND Expr 									{$$=create(op_node,"","And");addnode($$,$1);addbro($1,$3);}
		| Expr OR Expr 										{$$=create(op_node,"","Or");addnode($$,$1);addbro($1,$3);}
		| Expr EQ Expr 										{$$=create(op_node,"","Eq");addnode($$,$1);addbro($1,$3);}
		| Expr GEQ Expr 									{$$=create(op_node,"","Geq");addnode($$,$1);addbro($1,$3);}
		| Expr GT Expr 										{$$=create(op_node,"","Gt");addnode($$,$1);addbro($1,$3);}
		| Expr LEQ Expr 									{$$=create(op_node,"","Leq");addnode($$,$1);addbro($1,$3);}
		| Expr LT Expr 										{$$=create(op_node,"","Lt");addnode($$,$1);addbro($1,$3);}
		| Expr NEQ Expr 									{$$=create(op_node,"","Neq");addnode($$,$1);addbro($1,$3);}
		| Expr PLUS Expr 									{$$=create(op_node,"","Plus");addnode($$,$1);addbro($1,$3);}
		| Expr MINUS Expr 									{$$=create(op_node,"","Minus");addnode($$,$1);addbro($1,$3);}
		| Expr STAR Expr 									{$$=create(op_node,"","Star");addnode($$,$1);addbro($1,$3);}
		| Expr DIV Expr 									{$$=create(op_node,"","Div");addnode($$,$1);addbro($1,$3);}
		| Expr MOD Expr 									{$$=create(op_node,"","Mod");addnode($$,$1);addbro($1,$3);}
		| PLUS Expr 										{$$=create(op_node,"","Plus");addnode($$,$2);}
		| MINUS Expr 										{$$=create(op_node,"","Minus");addnode($$,$2);}
		| NOT Expr 											{$$=create(op_node,"","Not");addnode($$,$2);}
		| ID Expr6 											{$$=create(op_node,"","Length");addnode($$,create(id_node,"","Id"));}
		| OCURV Expr CCURV 									{;}
		| OCURV error CCURV 								{;}
		| Expr7 											{;}
		;
Expr1: Assignment											{;}
		| MethodInvocation 									{;}
		| ParseArgs 										{;}
		;
Expr6: %empty 												{$$=NULL;}
		| DOTLENGTH 										{;}
		;
Expr7: BOOLLIT 												{;}
		| DECLIT 											{;}
		| REALLIT 											{;}
		;
%%


