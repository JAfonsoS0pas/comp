#include <stdlib.h>
#include "arvo.h"


no create(type_node type, char* value, char* stype){
	no new = malloc(sizeof(node));
	
	new->stype = (char*)malloc(1+strlen(stype)*sizeof(char));
	strcpy(new->stype,stype);
	new->value = (char*)malloc(1+strlen(value)*sizeof(char));
	strcpy(new->value,value);
	new->type= type;
	new->type_t="";
	new->father=NULL;
	new->son=NULL;
	new->bro=NULL;
	new->n = 0;

	return new;

}

void addnode(no father, no new){

	if(new==NULL){
		return;
	}
	father->son = new;
	father->n++;
	new->father=father;

}
void addbro(no a, no b){
	if ((a==NULL)||(b==NULL))
	{
		return;
	}
	no aux;
	aux=a;
	while(aux->bro!=NULL){
		aux = aux->bro;
	}
	aux->bro=b;

	if(a->father!=NULL){
		b->father=a->father;
		b->father->n++;
	}


}



int cntsons(no root){
	int cnt = 0;
	no aux;
	aux=root;
	while(aux!=NULL){
		aux=aux->son;
		cnt++;
	}
	return cnt;
}

int cntbros(no root){
	int cnt = 0;
	no aux;
	aux=root;
	while(aux!=NULL){
		aux=aux->bro;
		cnt++;
	}
	return cnt;
}


void printftree(no root, int prof){
	if(root==NULL){
		return;
	}
	int i=0;
	no aux;
	if(root->type == root_node){
		printf("%s\n", root->stype);
	}
	else {
		while(i<prof){
			printf("..");
			i++;
		}
		if(strcmp(root->value,"")!=0){
			
			if(root->type_t!=NULL){
				if(strcmp(root->type_t,"(null)")!=0){
					
					printf("%s(%s)%s\n", root->stype, root->value,root->type_t);
				}else{
					
					printf("%s\n", root->stype);
				}
			}else{
				printf("%s\n", root->stype);
			}
		}
		else
			printf("%s%s\n", root->stype, root->type_t);
	}
	aux = root->son;
	while(aux!=NULL){
		no auxToFree = aux;
		printftree(aux, prof+1);
		aux=aux->bro;
		
		free(auxToFree->stype);
		free(auxToFree->value);
		free(auxToFree);
	}

}


