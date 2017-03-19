typedef enum {root_node, var_node, fdec_node, stat_node, op_node, ter_node, id_node} type_node;
typedef struct node* no;
typedef struct node {
	char* value;
	char* stype;
	type_node type;
	int n;
	no father;
	no bro;
	no son;
}node;


       

