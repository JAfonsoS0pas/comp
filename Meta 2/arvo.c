#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "arvo.h"


no *create(type_node type, char* value, char* stype){
	no *new = malloc(sizeof(no));
	
	new->stype = (char*)malloc(strlen(stype)*sizeof(char));
	new->value = (char*)malloc(strlen(value)*sizeof(char));
	strcpy(new->stype,stype);
	strcpy(new->value,value);
	new->type= type;

	new->father=NULL;
	new->son=NULL;
	new->bro=NULL;
	new->n = 0;

	return new;
	

}
void addnode(no *father, no *new){

	if(new==NULL){
		return;
	}
	father->son = new;
	father->n++;
	new->father=father;

}
no addbro(no a, no b){
	if ((a==NULL)||(b==NULL))
	{
		return;
	}
	no *aux;
	aux=a;
	while(aux->son!=NULL){
		aux = aux->son;
	}
	aux->bro=b;

	if(a->father!=NULL){
		b->father=a->father;
		b->n++;
	}

}



int cntbro(no *root){
	int cnt = 0;
	no * aux;
	aux=root;
	while(aux!=NULL){
		aux=aux->bro;
		cnt++;
	}
	return cnt;
}


//no getbro(no a, int prof);
void printftree(no *root, int d){
	if(root==NULL){
		return;
	}
	int i=0;
	no *aux;
	if(root->type = root_node){
		while(i<prof){
			printf("..");
			i++;
		}
		printf("%s(%s)\n", root-stype, root->value);
	}
	else if{
		while(i<prof){
			printf("..");
			i++;
		}
		printf("%s\n", root->stype);
	}

	aux = root->son;
	while(aux!=NULL){
		printftree(aux, int d+1);
		aux=aux->bro;
		
	}



}


