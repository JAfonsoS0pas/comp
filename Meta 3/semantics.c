#include "symbol_table.h"
#include "semantics.h"
#include "arvo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


void check_program(no root){
    if(root==NULL){
		return;
	}
	if(strcmp(root->stype, "Program")==0){
		char* name = (char*)strdup(root->son->value);
		init_class_table(name);
	}
	if(strcmp(root->stype, "FieldDecl")==0){
		check_field_decl(root);
	}
	if (strcmp(root->stype, "MethodDecl")==0){
		check_method_decl(root->son);
	}
	no aux = root->son;
	while(aux!=NULL){
		check_program(aux);
		aux=aux->bro;
	}
}


void check_ast(no root){
	if(root==NULL){
		return;
	}
	if(strcmp(root->stype,"MethodDecl")==0){
		check_method_body_ast(root);
	}
	if(strcmp(root->stype, "And")==0){
		char * cenas = (char*)strdup(" - boolean");
		root->type_t = cenas;
	}
	if(strcmp(root->stype, "Or")==0){
		char * cenas = (char*)strdup(" - boolean");
		root->type_t = cenas;
	}
	if(strcmp(root->stype, "DecLit")==0){
		char * cenas = (char*)strdup(" - int");
		root->type_t = cenas;
	}
	if(strcmp(root->stype, "StrLit")==0){
		char * cenas = (char*)strdup(" - String");
		root->type_t = cenas;
	}
	if(strcmp(root->stype, "BoolLit")==0){
		char * cenas = (char*)strdup(" - boolean");
		root->type_t = cenas;
	}
	if(strcmp(root->stype, "RealLit")==0){
		char * cenas = (char*)strdup(" - double");
		root->type_t = cenas;
	}
	if(strcmp(root->stype, "Gt")==0){
		char * cenas = (char*)strdup(" - boolean");
		root->type_t = cenas;
	}
	if(strcmp(root->stype, "Eq")==0){
		char * cenas = (char*)strdup(" - boolean");
		root->type_t = cenas;
	}
	if(strcmp(root->stype, "Geq")==0){
		char * cenas = (char*)strdup(" - boolean");
		root->type_t = cenas;
	}
	if(strcmp(root->stype, "Lt")==0){
		char * cenas = (char*)strdup(" - boolean");
		root->type_t = cenas;
	}
	if(strcmp(root->stype, "Leq")==0){
		char * cenas = (char*)strdup(" - boolean");
		root->type_t = cenas;
	}
	if(strcmp(root->stype, "Neq")==0){
		char * cenas = (char*)strdup(" - boolean");
		root->type_t = cenas;
	}
	if(strcmp(root->stype, "Not")==0){
		char * cenas = (char*)strdup(" - boolean");
		root->type_t = cenas;
	}
	if(strcmp(root->stype, "ParseArgs")==0){
		char * cenas = (char*)strdup(" - int");
		root->type_t = cenas;
	}
	if(strcmp(root->stype, "Length")==0){
		char * cenas = (char*)strdup(" - int");
		root->type_t = cenas;
	}
	if(strcmp(root->stype, "Mod")==0){
		char * cenas = (char*)strdup(" - int");
		root->type_t = cenas;
	}

	no aux = root->son;
	while(aux!=NULL){
		check_ast(aux);
		aux=aux->bro;
	}
	if(strcmp(root->stype, "Assign")==0 || strcmp(root->stype, "Minus")==0 || strcmp(root->stype, "Plus")==0 || strcmp(root->stype, "Assign")==0 || strcmp(root->stype, "Call")==0 ){
		char * cenas = (char*)strdup(root->son->type_t);
		root->type_t = cenas;
	}
	if(strcmp(root->stype, "Add")==0 || strcmp(root->stype, "Sub")==0 || strcmp(root->stype, "Div")==0 || strcmp(root->stype, "Mul")==0){
		char * cenas;
		printf("1%s 2%s 3%d\n",root->son->type_t,root->son->bro->type_t,strcmp(root->son->stype, root->son->bro->stype) );
		if(strcmp(root->son->type_t, root->son->bro->type_t)==0){
			cenas = (char*)strdup(root->son->type_t);	
		}
		else{
			cenas = (char*)strdup(" - double"); 
		}
		root->type_t = cenas;
	}
}

void check_field_decl(no root){
	char *stype = check_stype(root->son->stype);
    char *value = (char*)strdup(root->son->bro->value);
    insert_el(value,stype,NULL,NULL,"Class");
}


void check_method_decl(no root){
	char *stype = check_stype(root->son->stype);
	char *value = (char*)strdup(root->son->bro->value);
	char *params = check_method_params(root->son->bro->bro);
	
    char * new_str ;
	if((new_str = malloc(strlen(value)+strlen(params)+1)) != NULL){
	    new_str[0] = '\0';   // ensures the memory is an empty string
	    strcat(new_str,value);
	    strcat(new_str,params);
	}
    insert_el(value,stype,params,NULL,"Class");
    init_method_table(new_str);
    insert_el("return",stype,NULL,NULL,new_str);
    add_method_params(root->son->bro->bro,new_str);
    check_method_body(root->bro,new_str);

}

char* check_stype(char* root){
	char *stype = NULL;
	if(strcmp(root,"StringArray")==0){
			stype = (char*)calloc((strlen("String[]")+1),sizeof(char));
			strcpy(stype,"String[]");
	}
	else if(strcmp(root,"Int")==0){
		stype = (char*)calloc((strlen("int")+1),sizeof(char));
		strcpy(stype,"int");
	}
	else if(strcmp(root,"Double")==0){
		stype = (char*)calloc((strlen("double")+1),sizeof(char));
		strcpy(stype,"double");
	}
	else if(strcmp(root,"Bool")==0){
		stype = (char*)calloc((strlen("boolean")+1),sizeof(char));
		strcpy(stype,"boolean");
	}
	else if(strcmp(root,"Void")==0){
		stype = (char*)calloc((strlen("void")+1),sizeof(char));
		strcpy(stype,"void");
	}
	else if(strcmp(root,"ParseArgs")==0){
		stype = (char*)calloc((strlen("int")+1),sizeof(char));
		strcpy(stype,"int");
	}
	return stype;
}


void add_method_params(no root,char* table_to){
	no head=NULL;
	if(root->son){
		head=root->son;
	}
	while(head){
		char *stype = check_stype(head->son->stype);
		insert_el(head->son->bro->value,stype,NULL,"param",table_to);
		head=head->bro;
	}

}

char* check_method_params(no root){
	char params[500] = "(";
	no aux=NULL;
	if(root->son)
		aux = root->son;
	while(aux){
		if(strcmp(aux->son->stype,"StringArray")==0)
			strcat(params,"String[]");	
		else if(strcmp(aux->son->stype,"Int")==0)
			strcat(params,"int");
		else if(strcmp(aux->son->stype,"Double")==0)
			strcat(params,"double");
		else if(strcmp(aux->son->stype,"Bool")==0)
			strcat(params,"boolean");
		if(aux->bro)
			strcat(params,",");
		aux=aux->bro;
	}
	strcat(params,")");
	return strdup(params);
}

void check_method_body(no root, char* table_to){
	no head=NULL;
	if(root->son){
		head=root->son;
	}
	while(head){
		if(strcmp(head->stype,"VarDecl")==0){
			char *stype = check_stype(head->son->stype);
			insert_el(head->son->bro->value,stype,NULL,NULL,table_to);
		}
		head=head->bro;
	}
}


void check_method_body_ast(no root){ // root = methodHeader
	char * name = root->son->son->bro->value;
	char * params = check_method_params(root->son->son->bro->bro); 
	printf("check:%s - %s\n",name,params );
	no head=root->son->bro->son;
	char*  table_to = malloc(strlen(name)+strlen(params)+1);
	table_to[0] = '\0';   // ensures the memory is an empty string
    strcat(table_to,name);
    strcat(table_to,params);  

	while(head){
		if(strcmp(head->stype,"VarDecl")==0){
			//ignora			
		}
		else{
			check_method_body_ids(head,table_to);
		}
		head=head->bro;
	 }
}


void check_method_body_ids(no root, char* table_to){
	if(root==NULL){
		return;
	}
	if(strcmp(root->stype,"Id")==0){
		char * symbol_type =  search_char_table(root->value,table_to);
		printf("symbol_type%s\n",symbol_type );
		
		root->type_t = symbol_type;
	}
	no aux = root->son;
	while(aux){
		check_method_body_ids(aux,table_to);
		aux=aux->bro;
	}
	if(strcmp(root->stype,"Call")==0){
		table calling = search_table(root->son->value);
		if(calling){

		}
		else{
			
		}
	}
	
}