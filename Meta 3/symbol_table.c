#include "semantics.h"
#include "symbol_table.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


extern table symbol_table;


void init_tables(){
	symbol_table = malloc(sizeof(t));
  symbol_table->name = (char*)malloc((strlen("Class")+1)*sizeof(char));
  strcpy(symbol_table->name,"Class");
  
}


void insert_el(char *value, char* stype, type_node type,char* table_to)
{
  table_node new_node= malloc(sizeof(tn));
  new_node->value = value;
  new_node->stype = stype;
  new_node->type = type;
  new_node->next=NULL;

  table_node head = NULL;
  if(strcmp(table_to,"Class") == 0){
    head = symbol_table->my_table;
    if(head==NULL){
      head = new_node; 
      printf("FDS\n");
    }else{
      table_node current = head;
      while(current->next){
        current=current->next; 
        printf("YO\n");
      }
      current->next=new_node;
    }
  }else{
    printf("ENTREI NOS METHODS\n");
  }
}


void print_tables(){

  table aux = symbol_table;
  table_node aux_nodes;
  
  while(aux!=NULL){
    printf("TABLEA PRINCIPAL -> %s\n",aux->name);
    aux_nodes=aux->my_table;
    while(aux_nodes!=NULL){
      printf("NOS-> value: %s - type: %u - stype: %s\n", aux_nodes->value, aux_nodes->type, aux_nodes->stype); 
      aux_nodes=aux_nodes->next;
    }
    printf("ACABOU A TABELA PRINCIPAL\n");
    aux=aux->next;
  }
}