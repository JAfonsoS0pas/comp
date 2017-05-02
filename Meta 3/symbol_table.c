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
	table aux =NULL;
	table_node aux_nodes = NULL;
  char str[500] = " - ";

	for(aux = symbol_table;aux;aux=aux->next){
      if(strcmp(aux->name, t_name)==0){
  	    aux_nodes = aux->my_table;
  	    while(aux_nodes){
          if(strcmp(aux_nodes->value, name)==0){
  	    	  if(aux_nodes->stype != NULL){
                strcat(str,aux_nodes->stype);
  						  return strdup(str);
  	    			}
  				}
  	      aux_nodes=aux_nodes->next;
  	    }
      }
  }
  aux_nodes= symbol_table->my_table;
  while(aux_nodes){
    if(strcmp(aux_nodes->value, name)==0){
      if(aux_nodes->stype != NULL){
          strcat(str,aux_nodes->stype);
          return strdup(str);
        }
    }
    aux_nodes=aux_nodes->next;
  
  }
	return NULL;
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



void check_type(no root){


  
  //printf("entrou vai checkar %s\n", root->stype);

  if((strcmp(root->stype, "If")==0)|| (strcmp(root->stype, "Block")==0)|| (strcmp(root->stype, "While")==0)||(strcmp(root->stype, "Return")==0)){
    return;
  }
  
 

  int cnt = 0;

if((strcmp(root->stype, "Assign")==0)){
  
  printf("Assign!!  %s %s \n",root->son->value,  root->son->type_t);
  root->type_t = strdup(root->son->type_t);
  root = root->son;
  
}  

  if((strcmp(root->stype, "Sub")==0) || (strcmp(root->stype, "Add"))==0 || (strcmp(root->stype, "Mul"))==0 || (strcmp(root->stype, "Div"))==0) {
    printf("encontrou add");
    no aux  = root->son;

    while(aux!=NULL){
     
     //printf("tipo do filho : %s\n ", aux->type_t);
      if(cnt == 0){
         if(strcmp(aux->type_t," - int")==0){

          root->type_t  = strdup(aux->type_t);
          printf("ADD %s %s\n", root->type_t, root->stype);

        }
        if(strcmp(aux->type_t," - double")==0){

          root->type_t  = strdup(aux->type_t);
          printf("ADD %s %s\n", root->type_t, root->stype);
        }
        cnt++;
        
      }
      else{
        if(strcmp(aux->type_t, root->type_t ) !=0){
          
          root->type_t  = strdup(" - double");
         
        }
      }
     aux = aux->bro;
    }

  }




  
  
}