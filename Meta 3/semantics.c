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

		//check_declaration(root, "Method");
	}
	else{

	}
	no aux = root->son;
	while(aux!=NULL){
		check_program(aux);
		aux=aux->bro;
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

void insert(no root, char * name){

	no aux  = root;
	char * symbol_type;
	char * str_aux = (char * )calloc(200, sizeof(char));
	int len = 0;

	if(aux == NULL){
		return;
	}


	if(aux->type == stat_node){
		insert(aux->son, name);
		insert(aux->bro, name);
	}

	if(aux->type == op_node){
		insert(aux->son, name);
		//verify(aux);
		insert(aux->bro, name);
	}

	if(aux->type == id_node){
		//symbol_type = 
	}

}

