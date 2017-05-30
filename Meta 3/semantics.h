#include "symbol_table.h"
#include "arvo.h"

void check_program(no root);
void check_field_decl(no root);
char* check_method_params(no root);
char* check_method_decl(no root);
void add_method_params(no root,char* table_to);
char* check_stype(char* root);
void check_method_body(no root, char* table_to);
void check_ast(no root);
void check_method_body_ids(no root, char* table_to);
void check_method_body_ast(no root);
char** check_method_params_array(no root);
char** check_method_params_array_calls(no root);
