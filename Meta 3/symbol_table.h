#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H
#include "arvo.h"

typedef struct tn* table_node;
typedef struct tn{
  	char* value;
 	char* name; //acrescentei
  	char* stype;
  	char* params;
  	char* flag;
  	int parametros; //lembrar de ir alterar nas funções
  	table_node next;
}tn;

typedef struct t* table;
typedef struct t{
	char* type; //nao me faz sentido ter isto
	char* name;
	table_node my_table;
	table next;
}t;


void init_class_table(char* name);
void init_method_table(char* name);
void insert_el(char *value, char* stype,char* params, char* flag, char* table_to);
table search_table(char* name);
void print_tables();

#endif