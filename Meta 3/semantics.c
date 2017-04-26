#include "symbol_table.h"
#include "semantics.h"
#include "arvo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void check_program(no root){
    if(root==NULL){
		return;
	}
	check_declaration(root);
	no aux = root->son;
	while(aux!=NULL){
		check_program(aux);
		aux=aux->bro;
	}
}

void check_declaration(no root){
	printf("YA%s-%s-%u\n",root->stype,root->value, root->type );
    char *stype = (char*)strdup(root->stype);
    type_node type = root->type;
    char *value = (char*)strdup(root->value);
    insert_el(value,stype,type,"Class");
}
