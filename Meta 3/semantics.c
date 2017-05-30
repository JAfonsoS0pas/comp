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
	if(strcmp(root->stype,"MethodDecl")==0){
		check_method_decl(root->son);
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




void check_ast(no root){
	if(root==NULL){
		return;
	}
	if(strcmp(root->stype,"MethodDecl")==0){
		char *params = check_method_params(root->son->son->bro->bro);
		char *value = (char*)strdup(root->son->son->bro->value);
		char * new_str ;
		if((new_str = malloc(strlen(value)+strlen(params)+1)) != NULL){
		    new_str[0] = '\0';   // ensures the memory is an empty string
		    strcat(new_str,value);
		    strcat(new_str,params);
		}
		check_method_body(root->son->bro,new_str);
	}
	no aux = root->son;
	while(aux!=NULL){
		check_ast(aux);
		aux=aux->bro;
	}
}

char* check_method_decl(no root){
	char *stype = check_stype(root->son->stype);
	char *value = (char*)strdup(root->son->bro->value);
	char *params = check_method_params(root->son->bro->bro);
	char **params_array = check_method_params_array(root->son->bro->bro);
	
    char * new_str ;
	if((new_str = malloc(strlen(value)+strlen(params)+1)) != NULL){
	    new_str[0] = '\0';   // ensures the memory is an empty string
	    strcat(new_str,value);
	    strcat(new_str,params);
	}
    insert_el(value,stype,params,NULL,"Class");
    init_method_table(new_str,value,params_array,stype);
    add_method_params(root->son->bro->bro,new_str);
    return new_str;
}


void check_method_body(no root,char* table_to){
	if(root==NULL){
		return;
	}
	if(strcmp(root->stype,"VarDecl")==0){
			char *stype = check_stype(root->son->stype);
			insert_el(root->son->bro->value,stype,NULL,NULL,table_to);
	}
	if(strcmp(root->stype,"Id")==0){
		if(root->father!=NULL){
			if(strcmp(root->father->stype,"VarDecl")!=0){
				char * symbol_type =  search_char_table(root->value,table_to);
				root->type_t = symbol_type;
			}
		}else{
			char * symbol_type =  search_char_table(root->value,table_to);
			root->type_t = symbol_type;
		}
	}
	if(strcmp(root->stype, "And")==0 || strcmp(root->stype, "Or")==0 || strcmp(root->stype, "BoolLit")==0 || strcmp(root->stype, "Gt")==0 || strcmp(root->stype, "Eq")==0 || strcmp(root->stype, "Geq")==0 || strcmp(root->stype, "Lt")==0 || strcmp(root->stype, "Leq")==0 || strcmp(root->stype, "Neq")==0 || strcmp(root->stype, "Not")==0){
		char * cenas = (char*)strdup(" - boolean");
		root->type_t = cenas;
	}
	if(strcmp(root->stype, "DecLit")==0 || strcmp(root->stype, "Length")==0 || strcmp(root->stype, "ParseArgs")==0 ){
		char * cenas = (char*)strdup(" - int");
		root->type_t = cenas;
	}
	if(strcmp(root->stype, "StrLit")==0){
		char * cenas = (char*)strdup(" - String");
		root->type_t = cenas;
	}
	if(strcmp(root->stype, "RealLit")==0){
		char * cenas = (char*)strdup(" - double");
		root->type_t = cenas;
	}

	no aux = root->son;
	while(aux!=NULL){
		check_method_body(aux,table_to);
		aux=aux->bro;
	}
	if(strcmp(root->stype, "Assign")==0 || strcmp(root->stype, "Minus")==0 || strcmp(root->stype, "Plus")==0 ){
		char * cenas = (char*)strdup(root->son->type_t);
		root->type_t = cenas;
	}
	if(strcmp(root->stype, "Add")==0 || strcmp(root->stype, "Sub")==0 || strcmp(root->stype, "Div")==0 || strcmp(root->stype, "Mul")==0 || strcmp(root->stype, "Mod")==0){
		char * cenas;
		if(strcmp(root->son->type_t, root->son->bro->type_t)==0){
			cenas = (char*)strdup(root->son->type_t);	
		}
		else{
			cenas = (char*)strdup(" - double"); 
		}
		root->type_t = cenas;
	}
	if(strcmp(root->stype,"Call")==0){
		char ** params = check_method_params_array_calls(root);

		table cenas = check_call(root->son->value,params,0);
		if(cenas!=NULL){
			char * new_str;
			if((new_str = malloc(strlen(" - ")+strlen(cenas->my_table->stype)+1)) != NULL){
			    new_str[0] = '\0';   // ensures the memory is an empty string
			    strcat(new_str," - ");
			    strcat(new_str,cenas->my_table->stype);
			}
			root->type_t = new_str;
			int i = strlen(cenas->clean_name);
			char * new_str2;
			if((new_str2 = malloc(strlen(" - ")+strlen(&cenas->name[i])+1)) != NULL){
			    new_str2[0] = '\0';   // ensures the memory is an empty string
			    strcat(new_str2," - ");
			    strcat(new_str2,&cenas->name[i]);
			}
			root->son->type_t = new_str2;
		}
		else{
			char * new_str;
			if((new_str = malloc(strlen(" - undef")+1)) != NULL){
			    new_str[0] = '\0';   // ensures the memory is an empty string
			    strcat(new_str," - undef");
			}
			root->type_t = new_str;
			root->son->type_t = new_str;
		}
	}
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

char** check_method_params_array(no root){
	char** params = (char **)malloc(50 * sizeof(char*)); // maximo de 50 argumentos
	int i=1;
	no aux=NULL;
	if(root->son)
		aux = root->son;
	while(aux){
		if(strcmp(aux->son->stype,"StringArray")==0)
			params[i] = strdup("String[]");	
		else if(strcmp(aux->son->stype,"Int")==0)
			params[i] = strdup("int");
		else if(strcmp(aux->son->stype,"Double")==0)
			params[i] = strdup("double");
		else if(strcmp(aux->son->stype,"Bool")==0)
			params[i] = strdup("boolean");
		i++;
		aux=aux->bro;
	}
	char str[10];
	sprintf(str, "%d", i-1);
	params[0] = strdup(str);

	return params;
}


char** check_method_params_array_calls(no root){
	char** params = (char **)malloc(50 * sizeof(char*)); // maximo de 50 argumentos
	int i=1;
	no aux =NULL;
	if(root->son->bro)
		aux=root->son->bro;
	while(aux!=NULL){
		if(aux->type_t!=NULL){
			params[i] = strdup(&aux->type_t[3]);
			i++;
		}
		aux=aux->bro;
	}
	char str[10];
	sprintf(str, "%d", i-1);
	params[0] = strdup(str);

	return params;
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