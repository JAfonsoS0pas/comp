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
		char* name = check_method_decl(root->son);
		init_method_table(name);

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
	char *stype = NULL;
	if(strcmp(root->son->stype,"Bool")==0){
		stype = (char*)strdup("boolean");
	}else{
		stype = (char*)strdup(root->son->stype);
		int i ;
		for(i= 0; stype[i]; i++){
		  stype[i] = tolower(stype[i]);
		}
	}
    char *value = (char*)strdup(root->son->bro->value);
    insert_el(value,stype,NULL,"Class");
}


char* check_method_decl(no root){
	char *stype = (char*)strdup(root->son->stype);
	char *value = (char*)strdup(root->son->bro->value);
	char *params = check_method_params(root->son->bro->bro);
	int i ;
	for(i= 0; stype[i]; i++){
	  stype[i] = tolower(stype[i]);
	}
    char * new_str ;
	if((new_str = malloc(strlen(value)+strlen(params)+1)) != NULL){
	    new_str[0] = '\0';   // ensures the memory is an empty string
	    strcat(new_str,value);
	    strcat(new_str,params);
	}
    insert_el(value,stype,params,"Class");
    return new_str;
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

void check_declaration(no root,char* table_to){
    char *stype = (char*)strdup(root->stype);
    char *value = (char*)strdup(root->value);

    
    insert_el(value,stype,NULL,table_to);
}