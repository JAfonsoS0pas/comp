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

  symbol_table->params_array = NULL;

}


void init_method_table(char* name ,char* clean_name ,char** params_array, char* stype){

  table new_node = calloc(1,sizeof(t));

  new_node->type = (char*)calloc((strlen("Method")+1),sizeof(char));
  strcpy(new_node->type,"Method");

  new_node->name = name;
  new_node->clean_name = clean_name;
  new_node->params_array = params_array;


  table head = symbol_table;
  if(head==NULL){
    symbol_table = new_node;
  }else{
    while(head->next){
      head=head->next; 
    }
    head->next=new_node;
  }

  insert_elem("return",stype,NULL,NULL,head->next);
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

table check_call(char* id, char** params,int promotion){
  table head = symbol_table->next;
  while(head!=NULL){
    if(strcmp(head->clean_name,id)==0){
      if(head->params_array!=NULL && params!=NULL){
        if(strcmp(head->params_array[0],params[0])==0){
          int j=atoi(params[0]),i,myTable=0;
          for(i=1;i<=j;i++){
            if(promotion==1){
              if(strcmp(head->params_array[i],params[i])!=0 && !(strcmp(head->params_array[i],"double")==0 && strcmp(params[i],"int")==0)){
                myTable=1;
              }
            }else{
              if(strcmp(head->params_array[i],params[i])!=0 ){
                myTable=1;
              }  
            }
          }
          if(myTable==0){
            return head;
          }
        }
      }
    }
    head=head->next;
  }
  if(promotion==0){
    return check_call(id,params,1);
  }
  return NULL;
}


void insert_elem(char* value, char* stype, char* params, char* flag, table table_to){
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
  table_to->my_table = new_node;
   
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




char* search_char_table(char * name, char * t_name){
  table aux =NULL;
  table_node aux_nodes = NULL;
  char str[500] = " - ";
  aux = search_table(t_name);
  if(aux){
    for(aux_nodes=aux->my_table;aux_nodes;aux_nodes=aux_nodes->next){
      if(strcmp(aux_nodes->value,name)==0){
        strcat(str,aux_nodes->stype);
        return strdup(str);
      }
    }
  }
  aux=symbol_table;
  for(aux_nodes=aux->my_table;aux_nodes;aux_nodes=aux_nodes->next){
    if(strcmp(aux_nodes->value,name)==0 && strcmp(aux_nodes->params,"")==0){
        strcat(str,aux_nodes->stype);
        return strdup(str);
      }
  }
  return strdup("- undef");
}