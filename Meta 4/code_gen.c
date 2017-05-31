#include "code_gen.h"

void code_gen_field_decl(no root){
	if(strcmp(root->son->stype,"Int")==0){
		printf("%%%s = type i32\n",root->son->bro->value );
	}
	if(strcmp(root->son->stype,"Double")==0){
		printf("%%%s = type double\n",root->son->bro->value );
	}
	if(strcmp(root->son->stype,"Bool")==0){
		printf("%%%s = type i1\n",root->son->bro->value );
	}
}

void code_gen_method_decl(no root){
	printf("define i32 @%s(){\n",root->son->son->bro->value );
	//Int root->son->son->stype
	printf("}\n"); 
}

void code_gen(no root){
	if(strcmp(root->stype,"FieldDecl")==0){
		code_gen_field_decl(root);
	}
	if(strcmp(root->stype,"MethodDecl")==0){
		code_gen_method_decl(root);
	}
	no aux = root->son;
	while(aux!=NULL){
		code_gen(aux);
		aux=aux->bro;
	}
	if(strcmp(root->stype,"Program")==0){
		printf("define i32 @main() {\n" );
		printf("ret i32 0\n");
		printf("}\n");		
	}
}