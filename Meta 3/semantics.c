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
	if(strcmp(root->stype, "ParseArgs")==0){
		char * cenas = (char*)strdup(" - int");
		root->type_t = cenas;
	}
	if(strcmp(root->stype, "Length")==0){
		char * cenas = (char*)strdup(" - int");
		root->type_t = cenas;
	}
	
	no aux = root->son;
	while(aux!=NULL){
		check_program(aux);
		aux=aux->bro;
	}
}

void check_calls(no root){
	if(root==NULL){
		return;
	}
	if(root->stype!=NULL){
		if(strcmp(root->stype,"Call")==0){
			if(root->son->bro!=NULL){
				no aux=root->son->bro;
				char params[500] = "(";
				while(aux){
					char aux_str[100];
					if(strcmp(aux->type_t,"")!=0){
						strcpy(aux_str,aux->type_t);
						char * token;
						char search[]="  - ";
						token=strtok(aux_str, search);
						strcat(params, token);
						}
					if(aux->bro!=NULL)
						strcat(params,",");
					aux=aux->bro;
				}
				strcat(params, ")");
				char * wowo = strdup(params);
				if(root->son!=NULL){
					root->son->type_t = search_table_call(root->son, wowo);
					root->type_t = search_table_return(root->son,wowo);
				}
			}
		}
	}
	no aux = root->son;
	while(aux!=NULL){
		check_calls(aux);
		aux=aux->bro;
	}

}

void check_field_decl(no root){
	char *stype = check_stype(root->son->stype);
	char *value =NULL;
	if(root->son->bro!=NULL){
    	value = (char*)strdup(root->son->bro->value);
	}
    insert_el(value,stype,NULL,NULL,"Class");
}


void check_method_decl(no root){
	char *stype = check_stype(root->son->stype);
	char *value=NULL;
	if(root->son->bro!=NULL){
		 value = (char*)strdup(root->son->bro->value);
	}
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
		if(head->bro){
			head=head->bro;
		}else{
			break;
		}
		

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
		no aux2 = root;
	
		no aux = root->son;

		while(aux){

			check_method_body_ids(aux,table_to);
			if(aux!=NULL){
				check_type(aux);
				check_type(aux2);}
			if(aux->bro!=NULL){
				aux=aux->bro;
			}
			else{
				break;
			}
			

		}
	
}



void check_type(no root){
	if((strcmp(root->stype, "If")==0)|| (strcmp(root->stype, "Block")==0)|| (strcmp(root->stype, "While")==0)||(strcmp(root->stype, "Return")==0)){
    	return;
  	}
	int cnt = 0;

	if((strcmp(root->stype, "Assign")==0)){
		if(root->son->type_t!=NULL){
		  	root->type_t = strdup(root->son->type_t);
		  	root = root->son;
  		}
	}  

  	if((strcmp(root->stype, "Sub")==0) || (strcmp(root->stype, "Add"))==0 || (strcmp(root->stype, "Mul"))==0 || (strcmp(root->stype, "Div"))==0) {
    	no aux  = root->son;
    	while(aux!=NULL){
    		if(aux->type_t!=NULL){
		      	if(cnt == 0){
			        if(strcmp(aux->type_t," - int")==0){
			        	root->type_t  = strdup(aux->type_t);
			        }
			        if(strcmp(aux->type_t," - double")==0){
			          	root->type_t  = strdup(aux->type_t);
			        }
			        cnt++;
		     	}
		      	else{
		      		if((aux->type_t!=NULL)){
			        	if(strcmp(aux->type_t, root->type_t ) !=0){
			          		root->type_t  = strdup(" - double");
			        	}
			    	}
				}
			}
			if(aux->bro!=NULL){
				aux = aux->bro;
			}
			else{
				break;
			}
    	}
  	}
}

