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
	if(strcmp(root->stype, "DecLit")==0){
		char * cenas = (char*)strdup(" - int");
		root->type_t = cenas;
	}
	if(strcmp(root->stype, "StrLit")==0){
		char * cenas = (char*)strdup(" - String[]");
		root->type_t = cenas;
	}
	if(strcmp(root->stype, "BoolLit")==0){
		char * cenas = (char*)strdup(" - boolean");
		root->type_t = cenas;
	}
	if(strcmp(root->stype, "RealLit")==0){
		char * cenas = (char*)strdup(" - int");
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
			root->type_t = symbol_type;
	}

	no aux = root->son;
	while(aux){
		check_method_body_ids(aux,table_to);
		aux=aux->bro;
	}
}


void ast(no root, char * name){

	printf("vai construir a ast\n");
	printf("root type %s\n", root->stype);

	printf("ROOT TYPE %s\n ", root->stype);

	if(root==NULL){
		printf("root null\n");
		return;
	}

	if(strcmp(root->stype, "Program")==0){
		strcpy(name, root->son->value);
		printf("nome tabela actual %s\n ", name);

	}
	if(strcmp(root->stype, "MethodDecl")==0){
		printf("Encontrou MethodDecl\n");
		no aux = root->son; //methodheader
		no aux2 = NULL;


		//buscar nome da tabela
		
		char * params = check_method_params(aux->son->bro->bro);
		
	
		no aux3 = aux->son;
		while(strcmp(aux3->stype, "Id")!=0){
			aux3 = aux3->bro;
		}
		
		strcpy(name, aux3->value);
		if(strcmp(params,"()")!=0){
			strcat(name, params);
			
		}
		else{
			strcat(name, "()");
		}
		printf("nome actual!!!!!!!!!!!!!!!!!!!!!: %s\n ", name);
		
	
		
		
		while((aux!=NULL) && (strcmp(aux->stype,"MethodBody")!=0)){

			aux= aux->bro;
		}
		printf("encontrou methodbody!\n");
		
		if(aux->son!=NULL){

			aux2 = aux->son;

			while((aux2!=NULL)&&(aux2->type==var_node)){
				
				aux2 = aux2->bro;
			}

			aux2= aux2->son;
			if(aux2!=NULL){
				insert(aux2,name);
			}
			
			
		}

	}
	if((strcmp(root->stype, "Program")==0)){
		root= root->son;
		ast(root,name);
	}
	else{
		if(root->bro==NULL){
			return;
		}else{
			ast(root->bro,name);
		}
		
	}
	

}



void insert(no root, char * name){
	printf("entrou no insert\n");
	no aux  = root;
	char * symbol_type =  NULL;


	printf("root type %s\n  na tabela %s\n ", aux->stype, name);
	if(aux->type == stat_node){
		insert(aux->son, name);
		insert(aux->bro, name);
		symbol_type = search_char_table(aux->value, name);
		printf("olsaaaaaa %s\n", symbol_type);
	}

	if(aux->type == id_node){

		printf(" encontrou id\n");
		
		symbol_type = search_char_table(aux->value, name);
		
		printf("olsaaaaaa %s\n", symbol_type);

	}

	if(aux->type == stat_node){
		insert(aux->son, name);
		insert(aux->bro, name);
	}

	if(aux->type == op_node){
		insert(aux->son, name);
		//check type
		insert(aux->bro, name);

	}


	aux->type_t = symbol_type;

	printf("aux->type_t %s\n", aux->type_t);

	if(aux->bro!=NULL){
		insert(aux->bro,name);
	}
	else{
		return;
	}
	

}



