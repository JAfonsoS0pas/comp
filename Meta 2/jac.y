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

%left {PLUS} {MINUS}
%left {DIV}
%%

Epsilon: {};
expression : ID;

program : Program;
program : ProgramL;
fielddecl : FieldDecl;
fielddecl : FieldDecl2;
methoddecl : MethodDecl;
methodheader : MethodHeader;
methodheader : MethodHeader2;
methodheader : MethodHeader3;
type : Type;

Type: BOOL {$$=$1;}
	 | INT {$$=$1;}
	 | DOUBLE {$$=$1;}
;

FieldDecl: PUBLIC STATIC Type ID FieldDecl2 SEMI {$$=};
FieldDecl2: Epsilon {$$=NULL;}
			| COMMA {$$=$1;}
			| ID 	{$$=$1;}
;

Program: CLASS ID OBRACE ProgramL CBRACE {$$=};
ProgramL: Epsilon 		{$$=NULL;}
		| FieldDecl 	{$$=$1;}
		| MethodDecl 	{$$=$1;}
		| SEMI			{$$=$1;}
		| ProgramL		{$$=$1;}
;	


MethodDecl: PUBLIC STATIC MethodHeader MethodBody {$$=};
MethodHeader: MethodHeader2 ID OCURV MethodHeader3 CCURV {$$=};
MethodHeader2: Type {$$=$1;}
			   | VOID {$$=$1;}
; 
MethodHeader3: Epsilon {$$=NULL;}
			| FormalParams {$$=$1;}
; 

%%


