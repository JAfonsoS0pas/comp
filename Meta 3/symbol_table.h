#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H
#include "arvo.h"

typedef struct tn* table_node;
typedef struct tn{
  	char* value;
  	char* stype;
  	char* params;
  	char* flag;
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
char * search_char_table(char * name, char * t_name);
char* search_table_call(no root, char * yes);
char * search_table_return(no root, char * yes);
#endif