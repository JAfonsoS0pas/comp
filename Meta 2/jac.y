%{
    
	#include "arvo.c"

	int cnt;
	no root;
	no aux;
    int print_flag = 0,flag = 0;
    
    int yylex(void);
    void yyerror (const char *s);
    no create(type_node type, char* value, char* stype);
	void printftree(no n, int prof);
	void addnode(no father, no new);  //criar no
	void addbro(no a, no b); //criar irmao
	int cntbro(no root);
	void give_type(no novo, char* type);


%}

 
%union{
int inteiro;
char* string;
struct node* ynode;
}

%token CLASS DO DOTLENGTH ELSE IF PARSEINT PRINT PUBLIC RETURN STATIC STRING VOID WHILE OCURV CCURV OBRACE CBRACE OSQUARE CSQUARE AND OR LT GT EQ NEQ LEQ GEQ PLUS MINUS STAR DIV MOD NOT ASSIGN SEMI COMMA
%token <string> STRLIT DECLIT REALLIT ID RESERVED BOOL INT DOUBLE BOOLLIT

%type <ynode> Program ProgramL FieldDecl FieldDecl2 MethodDecl MethodHeader MethodHeader3 MethodBody MethodBody2 FormalParams STRING FormalALt VarDecl VarDecl2 Type Statement StatementAux StatementZeroMais PrintAux ExprAux Assignment MethodInvocation MethodInvocation2 ExprAux2 ParseArgs Expr Expr1 Expr6 Expr7 VOID

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
Program: CLASS ID OBRACE ProgramL CBRACE		 			{root=create(root_node, "","Program"); aux = create(id_node,$2,"Id");addnode(root, aux); addbro(aux,$4); $$=root;}
		;
ProgramL: %empty											{$$=NULL;}
		| FieldDecl 	ProgramL							{$$=$1;addbro($$,$2);}
		| MethodDecl 	ProgramL							{$$=$1;addbro($$,$2);}
		| SEMI			ProgramL							{$$=NULL;}
		;	

FieldDecl: PUBLIC STATIC Type ID FieldDecl2 SEMI 			{$$=create(var_node, "", "FieldDecl"); addnode($$,$3); addbro($3, create(id_node,$4,"Id")); 
																if($5!=NULL){
																	aux=$5;
																	while(aux!=NULL){
																		no aux1 = create(var_node, "", "FieldDecl");
																		no aux2 = create($3->type, $3->value, $3->stype);
																		addnode(aux1,aux2);
																		addbro(aux2,create(id_node,aux->value,"Id"));
																		addbro($$,aux1);
																		aux=aux->bro;
																	}
																	free(aux);
																}
															}
		| error SEMI 										{$$=NULL;}
		;
FieldDecl2: %empty 											{$$=NULL;}
		|  COMMA ID FieldDecl2								{$$=create(id_node,$2,"Id"); addbro($$,$3);}
		;

MethodDecl: PUBLIC STATIC MethodHeader MethodBody 			{$$=create(fdec_node,"","MethodDecl");addnode($$,$3); addbro($3,$4);}
		;
MethodHeader: Type ID OCURV MethodHeader3 CCURV 			{$$=create(fdec_node,"","MethodHeader");addnode($$,$1);addbro($1, create(id_node,$2,"Id")); 
																aux = create(fdec_node,"","MethodParams"); addbro($1,aux); addnode(aux,$4);
															} 
		| VOID ID OCURV MethodHeader3 CCURV 				{$$=create(fdec_node,"","MethodHeader");$1=create(ter_node,"","Void"); addnode($$,$1); 
																addbro($1,create(id_node,$2,"Id")); aux = create(fdec_node,"","MethodParams"); addbro($1, aux);
																addnode(aux,$4);
															}
		;
MethodHeader3: %empty 										{$$=NULL;}
		| FormalParams 										{$$=$1;}
		; 

MethodBody: OBRACE MethodBody2 CBRACE 						{$$=create(fdec_node,"", "MethodBody");addnode($$,$2);}
		;
MethodBody2: %empty 										{$$=NULL;}
		| VarDecl 		MethodBody2 						{$$=$1; addbro($$,$2);}
		| Statement 	MethodBody2							{$$=$1; addbro($$,$2);}
		;

FormalParams: Type ID FormalALt 							{$$=create(fdec_node,"","ParamDcl"); aux = create(id_node,$2,"Id"); addnode($$, aux); 
																addbro(aux,$3);
															}
		| STRING OSQUARE CSQUARE ID 						{$$=create(fdec_node,"","ParamDcl");aux =create(fdec_node,"","StringArray"); addnode($$, aux);
																addbro(aux,create(id_node,$4,"Id"));
															}
		;
FormalALt: %empty 											{$$=NULL;}
	   	| COMMA Type ID FormalALt 							{$$=create(id_node,$3,"Id");addnode($$,$4);}
		;

VarDecl: Type ID VarDecl2 SEMI 								{$$=create(fdec_node,"", "VarDecl"); addnode($$,$1);addbro($1,create(id_node,$2,"Id")); 
															if($3!=NULL){
																	aux=$3;
																	while(aux!=NULL){
																		no aux1 = create(fdec_node,"", "VarDecl");
																		no aux2 = create($1->type, $1->value, $1->stype);
																		addnode(aux1,aux2);
																		addbro(aux2,create(id_node,aux->value,"Id"));
																		addbro($$,aux1);
																		aux=aux->bro;
																	}
																	free(aux);
																}
															}
		;
VarDecl2: %empty 											{$$=NULL;}
		| COMMA ID VarDecl2 								{$$=create(id_node,$2,"Id"); addbro($$,$3);}
		;	


Type: 	BOOL 												{$$=create(ter_node,"","Bool");}
		| INT 												{$$=create(ter_node,"","Int");}
		| DOUBLE 											{$$=create(ter_node,"","Double");}
		;


Statement: OBRACE StatementZeroMais CBRACE					{$$=$2;}

		| IF OCURV Expr CCURV Statement 					{$$=create(stat_node,"","If"); addnode($$,$3); addbro($3,$5);}
		| IF OCURV Expr CCURV Statement ELSE Statement		{$$=create(stat_node,"","If"); addnode($$,$3); addbro($3,$5); 
																printf("SONS %d -> %s\n",cntsons($7),$3->stype);
																if(cntsons($7)>1){
																	aux = create(stat_node,"","Block"); 
																	addbro($5,aux);
																	addnode(aux, $7);
																}
															}
		| WHILE OCURV Expr CCURV Statement 					{$$=create(stat_node,"","While"); addnode($$,$3); addbro($3,$5);}

		| DO Statement WHILE OCURV Expr CCURV SEMI 			{;}
		| PRINT OCURV PrintAux CCURV SEMI  					{$$=create(stat_node,"","Print"); addnode($$,$3);}
		| StatementAux SEMI 								{$$=$1;}
		| RETURN ExprAux SEMI 								{$$=create(stat_node,"","Return");addnode($$,$2);}
		| error SEMI 										{$$=NULL;}
		;
StatementZeroMais: %empty									{$$=NULL;}
		| Statement StatementZeroMais						{$$=$1;addbro($$,$2); }
		;

StatementAux: %empty										{$$=NULL;}
		| Assignment 										{$$=$1;}
		| MethodInvocation 									{$$=$1;}
		| ParseArgs 										{$$=$1;}
		;
PrintAux: Expr 												{$$=$1;}
		| STRLIT 											{$$=create(ter_node,"","StrLit");}
		;
ExprAux: %empty 											{$$=NULL;}
		| Expr 												{$$=$1;}
		;

Assignment: ID ASSIGN Expr 									{$$=create(op_node,"","Assign"); aux = create(id_node,$1,"Id");addnode($$,aux); addbro(aux,$3);}
		;
MethodInvocation: ID OCURV MethodInvocation2 CCURV 			{$$=create(op_node,"","Call");aux= create(id_node,$1,"Id"); addnode($$,aux); addbro(aux,$3);}
		| ID OCURV error CCURV 								{$$=NULL;}
		;
MethodInvocation2: %empty 									{$$=NULL;}
		| Expr ExprAux2 									{$$=$1; addbro($$,$2);}
		;
ExprAux2: %empty 											{$$=NULL;}

		| COMMA Expr ExprAux2 								{$$=$2;addbro($$,$3);}

		;

ParseArgs: PARSEINT OCURV ID OSQUARE Expr CSQUARE CCURV 	{$$=create(op_node,"","ParseArgs"); aux=create(id_node,$3,"Id"); addnode($$,aux); addbro(aux,$5);}

		| PARSEINT OCURV error CCURV						{$$=NULL;}
		;
Expr: Expr1													{$$=$1;}
		| Expr AND Expr 									{$$=create(op_node,"","And");addnode($$,$1);addbro($1,$3);}
		| Expr OR Expr 										{$$=create(op_node,"","Or");addnode($$,$1);addbro($1,$3);}
		| Expr EQ Expr 										{$$=create(op_node,"","Eq");addnode($$,$1);addbro($1,$3);}
		| Expr GEQ Expr 									{$$=create(op_node,"","Geq");addnode($$,$1);addbro($1,$3);}
		| Expr GT Expr 										{$$=create(op_node,"","Gt");addnode($$,$1);addbro($1,$3);}
		| Expr LEQ Expr 									{$$=create(op_node,"","Leq");addnode($$,$1);addbro($1,$3);}
		| Expr LT Expr 										{$$=create(op_node,"","Lt");addnode($$,$1);addbro($1,$3);}
		| Expr NEQ Expr 									{$$=create(op_node,"","Neq");addnode($$,$1);addbro($1,$3);}
		| Expr PLUS Expr 									{$$=create(op_node,"","Add");addnode($$,$1);addbro($1,$3);}
		| Expr MINUS Expr 									{$$=create(op_node,"","Sub");addnode($$,$1);addbro($1,$3);}
		| Expr STAR Expr 									{$$=create(op_node,"","Mul");addnode($$,$1);addbro($1,$3);}
		| Expr DIV Expr 									{$$=create(op_node,"","Div");addnode($$,$1);addbro($1,$3);}
		| Expr MOD Expr 									{$$=create(op_node,"","Mod");addnode($$,$1);addbro($1,$3);}
		| PLUS Expr 										{$$=create(op_node,"","Plus");addnode($$,$2);}
		| MINUS Expr 										{$$=create(op_node,"","Minus");addnode($$,$2);}
		| NOT Expr 											{$$=create(op_node,"","Not");addnode($$,$2);}
		| ID Expr6 											{$$=create(id_node,$1,"Id");addnode($$,$2);}
		| OCURV Expr CCURV 									{$$=$2;}
		| OCURV error CCURV 								{$$=NULL;}
		| Expr7 											{$$=$1;}
		;
Expr1: Assignment											{$$=$1;}
		| MethodInvocation 									{$$=$1;}
		| ParseArgs 										{$$=$1;}
		;
Expr6: %empty 												{$$=NULL;}
		| DOTLENGTH 										{$$=create(op_node,"","Length");}
		;

Expr7: BOOLLIT 												{$$=create(ter_node,$1,"BoolLit");}
		| DECLIT 											{$$=create(ter_node,$1,"DecLit");}
		| REALLIT 											{$$=create(ter_node,$1,"RealLit");}
		;
%%


int main(int argc, char *argv[]){
	if(argc > 1){
		if(strcmp(argv[1],"-l") == 0 || strcmp(argv[1],"-1") == 0){
			if(strcmp(argv[1],"-l") == 0){
				flag=1;
			}
			yylex();
		}
		if(strcmp(argv[1],"-t")==0){
			flag=2;
			yyparse();
    		printftree(root,0);
    	}
	}
	else{
		flag=2;
		yyparse();
		
	}
	
	return 0;
}