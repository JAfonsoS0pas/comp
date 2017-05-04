#include "semantics.h"
#include "symbol_table.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


extern table symbol_table;


void init_class_table(char* name){
	symbol_table = calloc(1,sizeof(t));

  symbol_table->type = (char*)calloc((strlen("Class")+1),sizeof(char));
  strcpy(symbol_table->type,"Class");

  symbol_table->name = (char*)calloc((strlen(name)+1),sizeof(char));
  strcpy(symbol_table->name,name);

}


void init_method_table(char* name ){

  table new_node = calloc(1,sizeof(t));

  new_node->type = (char*)calloc((strlen("Method")+1),sizeof(char));
  strcpy(new_node->type,"Method");

  new_node->name = (char*)calloc((strlen(name)+1),sizeof(char));
  strcpy(new_node->name,name);


  table head = symbol_table;
  if(head==NULL){
    symbol_table = new_node; 
  }else{
    while(head->next){
      head=head->next; 
    }
    head->next=new_node;
  }
}

table search_table(char* name){
  table head = symbol_table;
  while(head){
    if(strcmp(head->name,name)==0){
      return head;
    }
    head=head->next; 
  }
  return NULL;
}

char* search_table_call(no root, char * yes){
  // printf("CALL %s\n",yes );
  table_node head = symbol_table->my_table;
  char str[500] = " - ";
  //printf("root_value - %s ,yes - %s\n",root->value, yes );
  while(head){
    //printf("head_value - %s, head->params %s\n",head->value, head->params );
    if((root->value!=NULL) && (head->value!=NULL)&&(yes!=NULL) && (head->params!=NULL)){
      if(strcmp(root->value,head->value)==0 && strcmp(head->params,yes)==0 && strcmp(head->params,"")!=0){
            strcat(str,head->params);
            return strdup(str);
        }
    }
    head=head->next;  
  }
  

  char * token;
  char * p = strdup(yes);
  p++;
  p[strlen(p)-1]=0;
  char teste[500] ="(";


  if (p != NULL) {

    // printf("P1 - %s\n",p );
    token = strsep(&p, ",");
    
    while (token != NULL)
    {
      // printf("P2 - %s\n",p );
      if(strcmp(token, "")!=0){
        // printf("parametro: %s\n", token);
        if(strcmp(token,"double")==0){
          strcat(teste,"int");
        }
        else{
          strcat(teste,token);
        }
      }
      token = strsep(&p, ",");
      if(token)
        strcat(teste,",");
    }

    strcat(teste,")");
 }
  if(strcmp(yes,teste)!=0){
    free(p);
      p = search_table_call(root,teste);
      if(strcmp(p," - undef")!=0){
        return p;
      }
    // printf("YA\n");
  }
  // printf("tenho parametros %s\n", yes);
  // printf("e agora tenho %s\n",teste );

  return strdup(" - undef");
}

char * search_table_return(no root, char * yes){
   // printf("RETURN %s - %s\n",root->value,yes );
  table_node head = symbol_table->my_table;
  char str[500] = " - ";
  while(head){
      if(strcmp(root->value,head->value)==0 && strcmp(head->params,yes)==0 && strcmp(head->params,"")!=0){
        strcat(str,head->stype);
        return strdup(str);
    }
    head=head->next;
  }
  char * token;
  char * p = strdup(yes);
  p++;
  p[strlen(p)-1]=0;
  char teste[500] ="(";


  if (p != NULL) {
    
    // printf("P1 - %s\n",p );
    token = strsep(&p, ",");
    while (token != NULL)
    {
      // printf("P2 - %s\n",p );
      if(strcmp(token, "")!=0){
        
         // printf("parametro: %s\n", token);
        if(strcmp(token,"double")==0){
          strcat(teste,"int");
          // printf("troquei\n");
        }
        else{
          strcat(teste,token);
        }
      }
     
      token = strsep(&p, ",");
      if(token)
        strcat(teste,",");
    }
    
    strcat(teste,")");
  }
  if(strcmp(yes,teste)!=0){
      free(p);
      p = search_table_return(root,teste);
      if(strcmp(p," - undef")!=0){
        return p;
      }
    // printf("YA\n");
  }
  // printf("CHEGUEI AO UNDEF %s\n",yes );
  return strdup(" - undef");
}

char * search_char_table(char * name, char * t_name){
	table aux =NULL;
	table_node aux_nodes = NULL;
  char str[500] = " - ";

	for(aux = symbol_table;aux;aux=aux->next){
      if(strcmp(aux->name, t_name)==0){
  	    aux_nodes = aux->my_table;
  	    while(aux_nodes){
          if(strcmp(aux_nodes->value, name)==0){
  	    	  if(aux_nodes->stype != NULL){
                strcat(str,aux_nodes->stype);
  						  return strdup(str);
  	    			}
  				}
  	      aux_nodes=aux_nodes->next;
  	    }
      }
  }
  aux_nodes= symbol_table->my_table;
  while(aux_nodes){
    if(strcmp(aux_nodes->value, name)==0){
      if(aux_nodes->stype != NULL){
          strcat(str,aux_nodes->stype);
          return strdup(str);
        }
    }
    aux_nodes=aux_nodes->next;
  
  }
	return NULL;
}

void insert_el(char *value, char* stype,char* params,char* flag, char* table_to)
{
  table_node new_node= calloc(1,sizeof(tn));
  new_node->value = value;
  new_node->stype = stype;
  new_node->next=NULL;
  if(params){
    new_node->params = params;
  }
  else{
    new_node->params = "";
  }
  if(flag){
    new_node->flag= flag;
  }
  else{
    new_node->flag= "";
  }

  table look = NULL;
  if(strcmp(table_to,"Class")==0)
    look = symbol_table;
  else
    look =  search_table(table_to);
  
  if(!look->my_table){
    look->my_table = new_node; 
  }else{
    table_node head = look->my_table ;
    while(head->next){
      head=head->next; 
    }
    head->next=new_node;
  }
}



void print_tables(){
  table aux ;
  table_node aux_nodes;
  
  for(aux = symbol_table;aux;aux=aux->next){
    printf("===== %s %s Symbol Table =====\n",aux->type, aux->name);
    aux_nodes = aux->my_table;
    while(aux_nodes){
      if(strcmp(aux_nodes->flag,"")!=0)
        printf("%s\t\t%s\t%s\n", aux_nodes->value, aux_nodes->stype,aux_nodes->flag);
      else{
        printf("%s\t%s\t%s\n", aux_nodes->value, aux_nodes->params, aux_nodes->stype);
      }
      aux_nodes=aux_nodes->next;
    }
    printf("\n");
  }
}


