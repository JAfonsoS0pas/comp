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
	char* type;
	char* name;
	char* clean_name;
	char** params_array;
	int n_params;
	table_node my_table;
	table next;
}t;


void init_class_table(char* name);
void init_method_table(char* name ,char* clean_name, char** params_array,char* stype);
void insert_el(char *value, char* stype,char* params, char* flag, char* table_to);
void insert_elem(char* value, char* stype, char* params, char* flag, table table_to);
table search_table(char* name);
void print_tables();
char* search_char_table(char * name, char * t_name);
table check_call(char* id, char** params,int promotion);
#endif