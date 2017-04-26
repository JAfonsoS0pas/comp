#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H
#include "arvo.h"

typedef struct tn* table_node;
typedef struct tn{
  char* value;
  char* stype;
  type_node type;
  table_node next;
}tn;

typedef struct t* table;
typedef struct t{
  char* name;
  table_node my_table;
  table next;
}t;


void init_tables();
void insert_el(char *value, char* stype,type_node type,char* table_to);
void print_tables();

#endif