%{
    #include <stdio.h>
    int yylex(void);
    void yyerror (const char *s);
%}

%token BOOL
%token BOOLLIT
%token CLASS
%token DO
%token DOTLENGTH
%token DOUBLE
%token ELSE
%token IF
%token INT
%token PARSEINT
%token PRINT
%token PUBLIC
%token RETURN
%token STATIC
%token STRING
%token VOID
%token WHILE
%token OCURV
%token CCURV
%token OBRACE
%token CBRACE
%token OSQUARE
%token CSQUARE
%token AND
%token OR
%token LT
%token GT
%token EQ
%token NEQ
%token LEQ
%token GEQ
%token PLUS
%token MINUS
%token STAR
%token DIV
%token MOD
%token NOT
%token ASSIGN
%token SEMI
%token COMMA
%token DECLIT
%token REALLIT
%token RESERVED
%token ID
%token STRLIT

%right ASSIGN
%left PLUS MINUS
%left DIV STAR
%%

program : Program 									{printf("YO%s\n",$$);};




Program: CLASS ID OBRACE ProgramL CBRACE 			{;};
ProgramL: %empty									{;}
		| FieldDecl 	ProgramL					{;}
		| MethodDecl 	ProgramL					{;}
		| SEMI			ProgramL					{;}
		;	

FieldDecl: PUBLIC STATIC Type ID FieldDecl2 SEMI 	{;};
FieldDecl2: %empty 									{;}
			| COMMA ID FieldDecl2 					{;}
			;


MethodDecl: PUBLIC STATIC MethodHeader MethodBody {;};
MethodHeader: MethodHeader2 ID OCURV MethodHeader3 CCURV {;};
MethodHeader2: Type 								{;}
			| VOID 									{;}
			; 
MethodHeader3: %empty 								{;}
			| FormalParams 							{;}
			; 

MethodBody: OBRACE MethodBody2 CBRACE 				{;};
MethodBody2: %empty 								{;}
			| VarDecl 		MethodBody2 			{;}
			| Statement 	MethodBody2				{;}
			;

FormalParams: Type ID FormalALt 					{;}
			| STRING OSQUARE CSQUARE ID 			{;}							{;}
			;
FormalALt: %empty 									{;}
		   	| COMMA Type ID FormalALt 				{;}
			;

VarDecl: Type ID VarDecl2 SEMI 						{;};
VarDecl2: %empty 									{;}
		| COMMA ID VarDecl2 						{;}
		;	

Type: BOOL 											{;}
	| INT 											{;}
	| DOUBLE 										{;}
	;


Statement: OBRACE StatementZeroMais CBRACE					{;}
		| IF OCURV Expr CCURV Statement StatementOpcional	{;}
		| WHILE OCURV Expr CCURV Statement 					{;}
		| DO Statement WHILE OCURV Expr CCURV SEMI 			{;}
		| PRINT OCURV PrintAux CCURV SEMI  					{;}
		| StatementAux SEMI 								{;}
		| RETURN ExprAux SEMI 								{;}
		;
StatementZeroMais: %empty									{;}
		| Statement StatementZeroMais						{;}
		;
StatementOpcional: %empty									{;}
		| Statement 				 						{;}
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

Assignment: ID ASSIGN Expr 									{;};
MethodInvocation: ID OCURV MethodInvocation2 CCURV 			{;};
MethodInvocation2: %empty 									{;}
		| Expr ExprAux2 									{;}
		;
ExprAux2: %empty 											{;}
		| COMMA Expr ExprAux2 								{;}
		;
ParseArgs: PARSEINT OCURV ID OSQUARE Expr CSQUARE CCURV 	{;};
Expr: Expr1													{;}
	| Expr Expr2 Expr 										{;}
	| Expr Expr3 Expr 										{;}
	| Expr Expr4 Expr 										{;}
	| Expr5 Expr 											{;}
	| ID Expr6 												{;}
	| OCURV Expr CCURV 										{;}
	| Expr7 												{;}
	;
Expr1: Assignment											{;}
	| MethodInvocation 										{;}
	| ParseArgs 											{;}
	;
Expr2: AND 													{;}
	| OR 													{;}
	; 
Expr3: EQ 													{;}
	| GEQ 													{;}
	| GT 													{;}
	| LEQ 													{;}
	| LT 													{;}
	| NEQ 													{;}
	;
Expr4: PLUS 												{;}
	| MINUS 												{;}
	| STAR 													{;}
	| DIV 													{;}
	| MOD 													{;}
	;
Expr5: PLUS 												{;}
	| MINUS 												{;}
	| NOT 													{;}
	;
Expr6: %empty 												{;}
	| DOTLENGTH 											{;}
	;
Expr7: BOOLLIT 												{;}
	| DECLIT 												{;}
	| REALLIT 												{;}
	;	


%%


