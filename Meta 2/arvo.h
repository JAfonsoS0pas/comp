typedef enum {root_node, var_node, fdec_node, stat_node, op_node, ter_node, id_node} type_node;
typedef struct no{
	struct no father;
	struct no bro;
	struct no son;
	type_node type;
	char* value;
	char* stype;
	int n;
}*no

//no tree;
int cnt = 0;
no create(type_node type, char* value, char* type);
void printftree(no *n, int prof);
void addnode(no *father, no *new);  //criar no
void addbro(no *old, no *new); //criar irmao
int cntbro(no *root);
void give_type(no *no, char* type);






       

