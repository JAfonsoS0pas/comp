#include "symbol_table.h"
#include "arvo.h"

void check_program(no root);
void check_field_decl(no root);
char* check_method_params(no root);
void check_method_decl(no root);
void add_method_params(no root,char* table_to);
char* check_stype(char* root);
void check_method_body(no root, char* table_to);
void insert(no root, char * name);
void ast(no root, char * name);
void check_method_body_ids(no root, char* table_to);
void check_type(no root);
void check_calls(no root);
void go_again(no root);
