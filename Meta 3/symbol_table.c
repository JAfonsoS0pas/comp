#include "semantics.h"
#include "symbol_table.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


extern table symbol_table;


void init_class_table(char* name){
	symbol_table = calloc(1,sizeof(t));

  symbol_table->type = (char*)calloc((strlen("Class")+1),sizeof(char));
  strcpy(symbol_table->type,"Class");

  symbol_table->name = (char*)calloc((strlen(name)+1),sizeof(char));
  strcpy(symbol_table->name,name);

}


void init_method_table(char* name ){

  table new_node = calloc(1,sizeof(t));

  new_node->type = (char*)calloc((strlen("Method")+1),sizeof(char));
  strcpy(new_node->type,"Method");

  new_node->name = (char*)calloc((strlen(name)+1),sizeof(char));
  strcpy(new_node->name,name);


  table head = symbol_table;
  if(head==NULL){
    symbol_table = new_node; 
  }else{
    while(head->next){
      head=head->next; 
    }
    head->next=new_node;
  }
}

table search_table(char* name){
  table head = symbol_table;
  while(head){
    if(strcmp(head->name,name)==0){
      return head;
    }
    head=head->next; 
  }
  return NULL;
}


char * search_char_table(char * name, char * t_name){
	int i;
	table aux =NULL;
	table_node aux_table = NULL;
	char * str = NULL;

	for(aux = symbol_table->next; aux!= NULL; aux = aux->next){
		if(strcmp(aux->name, t_name)==0){
			for(aux_table = aux->my_table; aux_table!=NULL; aux_table= aux_table ->next){
				if(strcmp(name, aux_table->name)==0){
					return aux_table->stype;
				}
			}
		}
	}

	for(aux_table = symbol_table->my_table; aux_table!=NULL; aux_table=aux_table->next){
		if(strcmp(name, aux_table->name)==0){
			str = (char*)calloc(200,sizeof(char));
			if(aux_table->params != NULL){
				strcpy(str, aux_table->stype);
				strcat(str,"(");
				for(i=0;i<aux_table->parametros;i++){
					if(i>0){
						strcat(str, ",");
					}
					//strcat(str, aux_table->)
				}
			}
		}
	}

}

void insert_el(char *value, char* stype,char* params,char* flag, char* table_to)
{
  table_node new_node= calloc(1,sizeof(tn));
  new_node->value = value;
  new_node->stype = stype;
  new_node->next=NULL;
  if(params){
    new_node->params = params;
  }
  else{
    new_node->params = "";
  }
  if(flag){
    new_node->flag= flag;
  }
  else{
    new_node->flag= "";
  }

  table look = NULL;
  if(strcmp(table_to,"Class")==0)
    look = symbol_table;
  else
    look =  search_table(table_to);
  
  if(!look->my_table){
    look->my_table = new_node; 
  }else{
    table_node head = look->my_table ;
    while(head->next){
      head=head->next; 
    }
    head->next=new_node;
  }
}



void print_tables(){
  table aux ;
  table_node aux_nodes;
  
  for(aux = symbol_table;aux;aux=aux->next){
    printf("===== %s %s Symbol Table =====\n",aux->type, aux->name);
    aux_nodes = aux->my_table;
    while(aux_nodes){
      if(strcmp(aux_nodes->flag,"")!=0)
        printf("%s\t\t%s\t%s\n", aux_nodes->value, aux_nodes->stype,aux_nodes->flag);
      else{
        printf("%s\t%s\t%s\n", aux_nodes->value, aux_nodes->params, aux_nodes->stype);
      }
      aux_nodes=aux_nodes->next;
    }
    printf("\n");
  }
}

/*
void verify(no root){
	//int i, j;
	no aux = root->son;
	table aux_table =  symbol_table;
	char * type = NULL;

	if(strcmp(root->stype,'Call')==0){
		for(;aux_table->my_table!=NULL && strcmp(aux_table->name, aux_table->my_table->value)!=0;aux_table->my_table = aux_table->my_table->next);
			if(aux_table->my_table!=NULL)
				root->type_t = aux_table->type;

	}
	else if(strcmp(root->stype,"Mul")==0 || strcmp(root->stype, "Div") == 0 || strcmp(root->stype, "Mod")==0){
		if(aux->type_t!=NULL){
			root->type_t = (char * )calloc(5,sizeof(char));
			strcpy(root->type_t,"int");
		}
	}


}*/