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
    return search_table_call(root,teste);
    // printf("YA\n");
  }
  // printf("tenho parametros %s\n", yes);
  // printf("e agora tenho %s\n",teste );

  return strdup(" - undef");
}

char * search_table_return(no root, char * yes){

  table_node head = symbol_table->my_table;
  char str[500] = " - ";
  while(head){
      //printf("head->params %s | Yes %s\n\n", head->params, yes);
      if(strcmp(root->value,head->value)==0 && strcmp(head->params,yes)==0 && strcmp(head->params,"")!=0){
        strcat(str,head->stype);
        //printf("encontrei!");
        return strdup(str);
    }
    head=head->next;
  }
 /* ////////////////////////AQUI//////////////////
  
  printf(" nao encontrei parei\n");
  char * token ="";
  char * counter = strdup(yes);
  char * p = strdup(yes);
  char * apl ;
  p++;
  p[strlen(p)-1]=0;
  char * copia;
  copia = strdup(p);
  char * primeiro ="";

  char * oui;
  int cnt5 = 0;
  oui = strtok(counter,",");
  while(oui!=NULL){
      cnt5 ++;
      oui = strtok(NULL,",");
  }

  if(strcmp(yes, "(undef)")==0){
    return "- undef";
  }
  printf("CNT5 %d\n", cnt5 );
  int k;

printf("YES %s\n", yes);
  int not_double = 0;

if(cnt5==1){
  if(strcmp(yes,"(double)")==0){
    return search_table_return(root, "(int)"); 
  }else{
    return "- undef";
  }
}


for(k=0;k<cnt5;k++){
  int cnt = 0;
  char * yolo="";
  if (p != NULL) {
    if(cnt==0){

     token = strtok(p,",");
     char * rest = "first";
     int ty = 0;
     printf("token : %s\n", token);
     char* save="";


     while(rest!=NULL){
      if(ty==0){
        primeiro = strdup(rest);
        if(strcmp("double", primeiro)==0){
          not_double = 1;
        }
        rest = strtok(NULL,",");
        if(strcmp("double", rest)==0){
          not_double = 1;
        }


        if((rest==NULL)||(strcmp(rest, "undef"))){
          break;
        }else{
         
          printf("save: %s\n", save);
         

        }
       printf("rest2 %s\n", rest);
        printf("rest2 %s\n", primeiro);
       
        printf("yolo");
      }
      else{
       printf("yolo");
        printf("rest4 %s\n", rest);
        rest = strtok(NULL,",");
        if(rest!=NULL){
          strcat(save,rest);
        }else{
          break;
        }
        
      }
     printf("yolo");
     printf("restddd2 %s\n", primeiro);
      printf("hue");
      printf("rest %s\n", rest);
      printf("rest2 %s\n", save);
       save = strdup(rest);
      
    }

    printf("hue");
      printf("rest 3\n" );
      if(strcmp(yes, "(double)")==0){

        return search_table_return(root, "(int)");
      }


      if(strcmp(yes, "()")==0){

        return "- undef";
      }
      if(strcmp(yes,"(int)")==0){
        return "- undef";
      }
      printf("YES5 %s\n");
      if(strcmp(token,"double")==0){
          not_double = 1;
          strcpy(token, "int");
      }

      if(not_double==0){
        return "- undef";
      }

     
      char * corte = strdup(token);
      strcat(corte, ",");
      if(strcmp(primeiro, "first")!=0){
        printf("corte:    %s\n ", corte);
         strcat(corte, primeiro);
         apl = strdup("(");
        
         yolo = strdup(corte);
          strcat(apl, yolo);
           printf("YOLO CORTE: %s\n", apl);
            printf("YOLO CORTE: %s\n", yolo);
          strcat(apl,")");
          printf("corte : %s\n", apl);
          printf("corte : %s\n", apl);
      }
     printf("YES3 %s\n", save);
      printf("YOLO CORTE: %s\n", apl);
      search_table_return(root, apl);
    
      printf("YES3 %s\n", save);
    }
   }else{

    printf("YES 5555%s\n", yes);
    printf("YOLO CORTE: %s\n", yolo);
    token = strtok(p,yolo);
     char * rest = "first";
     int ty = 0;
     char* save="";
     while(rest!=NULL){
      if(ty==0){
        primeiro = strdup(rest);
        if(strcmp("double", primeiro)==0){
          not_double = 1;
        }
        rest = strtok(NULL,",");
        if(strcmp("double", rest)==0){
          not_double = 1;
        }
        if(rest!=NULL){
          save = strdup(rest);
        }
      }
      else{

        rest = strtok(NULL,",");
       if((rest==NULL)||(strcmp(rest, "undef")==0)){
          strcat(save,rest);
        }else{
          break;
        }
      }

    }
   printf("YES %s\n", yes);
      if(strcmp(token,"double")==0){
          strcpy(token, "int");
          not_double=1;
      }
      if(not_double!=1){
        return ("- undef");
      }



      char * corte = strdup(token);
      strcat(corte, ",");
      if(strcmp(primeiro, "first")!=0){
        strcat(corte, primeiro);
      printf("corte : %s\n", corte);
        apl = strdup("(");
        
         yolo = strdup(corte);
          strcat(apl, yolo);
          strcat(apl,")");
        printf("corte : %s\n", yolo);
      }else{
        strcat(yolo,")");
      }

      search_table_return(root, apl);




  }
     
    }

  */
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
          //printf("1 -rogerio %s name:%s\n", aux_nodes->value, var);

          if(strcmp(aux_nodes->value, name)==0){
            //printf("name: %s\n", name);
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

  aux = symbol_table;
  //printf("vou à MAIN  \n");

    aux_nodes = aux->my_table;
    while(aux_nodes){
      //printf("55 -rogerio %s name:%s\n", aux_nodes->value, var);

      if(strcmp(aux_nodes->value, name)==0){
       // printf("name: %s\n", name);
        if(aux_nodes->stype != NULL){
            strcat(str,aux_nodes->stype);
            return strdup(str);
          } 
      }
      aux_nodes=aux_nodes->next;
      //printf("aux_nodes %s\n", aux_nodes);
      //printf("55 -rogerio %s name:%s\n", aux_nodes->value, var);
    }
      
  
	return ("- undef");
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


