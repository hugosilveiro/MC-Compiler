#include <string.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "anotedTree.h"
#include "printer.h"

#define DEBUG_A 0
#define ERRORS 0

extern Table * symbol_table;
Table * current_table2 = NULL;

void get_anoted_Tree(Node* tree)
{
	if (DEBUG_A) printf("[get_anoted_tree]\n");
	Node* temp = tree->child;
	while(temp!=NULL)
	{
		if (DEBUG_A) printf("%s\n", NODE_NAME[temp->node_type]);
		
		if(strcmp("FuncDefinition", NODE_NAME[temp->node_type]) == 0)
		{
			if(DEBUG_A)printf("FuncDefinition\n");
			insert_funct_definition(temp);
		}
		
		temp= temp->brother;
	}
}

void insert_funct_definition(Node * node)
{

	if(DEBUG_A)
	{
		printf("[insert_function_definition]\n");	
	}	

	//function name:
	char * func_name;
	func_name = strdup(get_function_name(node));

	Table *aux;
	aux = search_table(func_name);

	if(aux!=NULL)
	{
		current_table2 = aux;
		insert_funcBody(node);
		current_table2 = NULL;

	}
	
}

void insert_funcBody(Node * node)
{
	if(DEBUG_A){
		printf("insert_function_funcBody\n");
	}
	Node * temp = node->child;
	while(temp != NULL){

		if(strcmp(NODE_NAME[temp->node_type], "FuncBody") == 0)
		{
			get_inside_funcBody(temp);
			//check_inside_funcBody(temp);
		}
		temp = temp->brother;
	}
}


void get_inside_store(Node * node)
{
	Node * temp;
	temp = node->child;
	if(temp!=NULL)
	{
		node->type = temp->type;
	}
}

void check_call_type(Node * node)
{
	Node * temp;
	temp = node->child;
	if(temp!=NULL)
	{
		if(type_call(temp->type)!=NULL)
		{
			node->type = strdup( type_call(temp->type));	
		}
	}
}

char * type_call(char * type)
{
	int aux = strlen(type);
	char * new_aux = (char*)malloc(aux+1);
	int i;
	for(i = 0; i < aux; i++){
		if(type[i] != '('){
			new_aux[i] = type[i];
		}
		else if(type[i] == '('){
			new_aux[i] = '\0';
			return new_aux;
		}
	}
	return NULL;
}


/*
//erros check num arguments
void check_num_args(Node * temp)
{
	Table * table;
	Symbol * symbol;
	table = search_table("global");
	symbol = search_symbol(temp->value, table);
	int caller, called;
	if(symbol!=NULL)
	{
		called = num_args(temp->type);	
	}
	if(temp->type!=NULL)
	{
		caller = num_args(temp->type);
	}

	if(called != caller)
	{
	 	printf(errors_list[8], temp->value, caller, called);
	}
}

int num_args(char * string)
{
	int comma = 0;
	int i;
	for(i = 0;i<strlen(string)-1;i++)
	{
		if(string[i] == ','){
			comma++;
		}
	}
	return comma+1;
}
*/

void get_inside_funcBody(Node * node)
{
	Node * temp = node->child;

	while(temp!= NULL)
	{
		if(DEBUG_A)printf("[get_inside_funcBody] %s\n",NODE_NAME[temp->node_type] );

		if(strcmp(NODE_NAME[temp->node_type], "Id") == 0){
			get_inside_id(temp);
		}
		else if(strcmp(NODE_NAME[temp->node_type], "IntLit") == 0){
			temp->type = "int";
		}
		else if(strcmp(NODE_NAME[temp->node_type], "ChrLit") == 0){
			temp->type = "int";
		}
		else if(strcmp(NODE_NAME[temp->node_type], "StrLit") == 0){
			get_inside_strlit(temp);
		}
		else if(strcmp(NODE_NAME[temp->node_type], "Eq") == 0)
		{
			

			temp->type = "int"; 
 
			get_inside_funcBody(temp);




		}
		else if(strcmp(NODE_NAME[temp->node_type], "Ne") == 0)
		{

			temp->type = "int";  
			get_inside_funcBody(temp);


		}
		else if(strcmp(NODE_NAME[temp->node_type], "Lt") == 0)
		{
			temp->type = "int"; 
			get_inside_funcBody(temp);

		}
		else if(strcmp(NODE_NAME[temp->node_type], "Gt") == 0)
		{
			temp->type = "int"; 
			get_inside_funcBody(temp);

		}
		else if(strcmp(NODE_NAME[temp->node_type], "Le") == 0)
		{
			temp->type = "int"; 
			get_inside_funcBody(temp);

		}
		else if(strcmp(NODE_NAME[temp->node_type], "Ge") == 0)
		{
			temp->type = "int"; 
			get_inside_funcBody(temp);

		}
		else if(strcmp(NODE_NAME[temp->node_type], "And") == 0)
		{	
			temp->type = "int"; 
			get_inside_funcBody(temp);

		}
		else if(strcmp(NODE_NAME[temp->node_type], "Or") == 0)
		{	
			temp->type = "int"; 
			get_inside_funcBody(temp);

		}
		else if(strcmp(NODE_NAME[temp->node_type], "Add") == 0)
		{	

			get_inside_funcBody(temp);
			is_Add(temp);

		}
		else if(strcmp(NODE_NAME[temp->node_type], "Sub") == 0)
		{

			get_inside_funcBody(temp);
			is_Sub(temp);

		}
		else if(strcmp(NODE_NAME[temp->node_type], "Mul") == 0)
		{
			//temp->type = "int"; 
			get_inside_funcBody(temp);
			is_Mul_Div_Mod(temp);

		}
		else if(strcmp(NODE_NAME[temp->node_type], "Div") == 0)
		{
			//temp->type = "int"; 
			get_inside_funcBody(temp);
			is_Mul_Div_Mod(temp);

		}
		else if(strcmp(NODE_NAME[temp->node_type], "Mod") == 0)
		{
			//temp->type = "int"; 
			get_inside_funcBody(temp);
			is_Mul_Div_Mod(temp);

		}
		else if(strcmp(NODE_NAME[temp->node_type], "Not") == 0)
		{
			temp->type = "int"; 
			get_inside_funcBody(temp);

		}
		else if(strcmp(NODE_NAME[temp->node_type], "Minus") == 0)
		{
			//temp->type = "int"; 
			get_inside_funcBody(temp);
			is_Plus_Minus(temp);

		}
		else if(strcmp(NODE_NAME[temp->node_type], "Plus") == 0)
		{
			//temp->type = "int"; 
			get_inside_funcBody(temp);
			is_Plus_Minus(temp);

		}
		else if(strcmp(NODE_NAME[temp->node_type], "Addr") == 0)
		{
			get_inside_funcBody(temp);
			get_inside_addr(temp); 
			//temp->type = "int"; 

			//get_inside_funcBody(temp);

		}
		else if(strcmp(NODE_NAME[temp->node_type], "Deref") == 0)
		{	
			//printf("Deref\nchild:%s\n", NODE_NAME[temp->child->node_type]);
			get_inside_funcBody(temp);
			get_deref_type(temp);
			//get_deref_type(temp); 
			

		}
		else if(strcmp(NODE_NAME[temp->node_type], "Store") == 0)
		{
			//printf("gotr: %s\n",get_operator_type_result(temp));
			//temp->type = get_operator_type_result(temp); 

			get_inside_funcBody(temp);
			get_inside_store(temp);
		}
		else if(strcmp(NODE_NAME[temp->node_type], "Comma") == 0)
		{
			get_inside_funcBody(temp);
			get_inside_comma(temp);

		}
		
		else if(strcmp(NODE_NAME[temp->node_type], "Call") == 0)
		{
			
			//temp->type = check_call_type(temp); 
			//get_inside_funcBody(temp);

			if (DEBUG_A) printf("call\n");
			get_inside_funcBody(temp);
			check_call_type(temp); 


		}
		else if(strcmp(NODE_NAME[temp->node_type], "Return") == 0){
			get_inside_funcBody(temp);
		}
		else if(strcmp(NODE_NAME[temp->node_type], "If") == 0)
		{
			
			get_inside_funcBody(temp);
		}
		else if(strcmp(NODE_NAME[temp->node_type], "For") == 0)
		{
			
			get_inside_funcBody(temp);
		}
		else if(strcmp(NODE_NAME[temp->node_type], "StatList")==0)
		{
			get_inside_funcBody(temp);
		}	
		
		temp = temp->brother;
	}

}
char * get_type_without_array(char * type)
{
	if(DEBUG_A) printf("get_type_without_array\n");
	int i;
	char * aux = (char*)malloc(strlen(type));
	for(i = 0; i < strlen(type)-1; i++){
		if(type[i] != '['){
			aux[i] = type[i];
		}
		else{
			return aux;
		}
	}
	return type;
}


void aux_pointer(Node* node, int aux_value)
{
	if(DEBUG_A)printf("node->type: %s\n", node->type);
	if(node!=NULL)
	{
		char * aux1 = NULL;
	if(aux_value>0){
		if(DEBUG_A)printf("aux_value: %d\n", aux_value);
		if(node->type[0] == 'i'){
			aux1 = (char*)malloc(strlen("int")+1);
			strcpy(aux1, get_type_without_array(node->type));
			int i;
			for(i = 0; i < aux_value; i++){
				aux1 = concat(aux1, "*");
			}

		}
		else if(node->type[0] == 'c'){
			aux1 = (char*)malloc(strlen("char")+1);
			strcpy(aux1, get_type_without_array(node->type));
			int i;
			for(i = 0; i < aux_value; i++){
				aux1 = concat(aux1, "*");
			}
		}
		else if(node->type[0] == 'v'){
			aux1 = (char*)malloc(strlen("void")+1);
			strcpy(aux1, get_type_without_array(node->type));
			int i;
			for(i = 0; i < aux_value; i++){
				aux1 = concat(aux1, "*");
			}
		}
		node->type = aux1;
		//printf("node->type: %s\n", node->type);
		if(DEBUG_A)printf("aux1: %s\n", aux1);
	}	
	}
}


void is_Add(Node * node)

{
	if(DEBUG_A) printf("is_Add:%s\n", NODE_NAME[node->child->node_type]);
	if(DEBUG_A) printf("is_Add:%s\n", node->type);
	//printf("child1: %s\n", node->child->type);
	Node * child1 = node->child;
	Node * child2 = child1->brother;
	int aux_value1;
	int aux_value2;
	char * type1aux, * type2aux;

	//printf("aux_value1: %d\n", aux_value1);
	//printf("aux_value2: %d\n", aux_value2);
	

	type1aux = strdup(child1->type);
	type2aux = strdup(child2->type);
	
	//printf("aux_value2: %d\n", aux_value2);

	if(child1->type != NULL){
		aux_value1 = aux_Arrray_Declarations(child1->type);
		//printf("%d\n", aux_value1);
		aux_pointer(child1, aux_value1);	
	}
	if(child2->type != NULL){
		aux_value2 = aux_Arrray_Declarations(child2->type);
		//printf("%d\n", aux_value2);
		aux_pointer(child2, aux_value2);	
	}
		


	if(child1 != NULL && child2 != NULL){
		//printf("%s\n%s\n", child1->type, child2->type);
		if(strcmp(child1->type, "int") == 0 && strcmp(child2->type, "char") == 0){
			if(DEBUG_A)printf("int && char\n");
			node->type = child1->type;
		}
		else if(strcmp(child1->type, "char") == 0 && strcmp(child2->type, "int") == 0){
			if(DEBUG_A)printf("char && int\n");
			node->type = child2->type;
		}
		else if(strcmp(child1->type, "int") == 0 && strcmp(child2->type, "int") == 0){
			if(DEBUG_A)printf("int && int\n");
			node->type = child1->type;
		}
		else if(strcmp(child1->type, "char") == 0 && strcmp(child2->type, "char") == 0){
			if(DEBUG_A)printf("char && char\n");
			node->type = "int";
		}
		
		else if(strcmp(child1->type, "int") == 0  && return_pointers(child2->type)>0){
			if(DEBUG_A)printf("1-int 2-pointerr\n");
			 node->type = child2->type;
		}

		
	
		else if(strcmp(child1->type, "char") == 0 && return_pointers(child2->type)>0){
			if(DEBUG_A)printf("1-char  2-pointerr\n");
			node->type = child2->type;
		}
		else if(strcmp(child2->type, "char") == 0 && return_pointers(child1->type)>0){
			if(DEBUG_A)printf("1-pointer 2-char\n");
			node->type = child1->type;
		}
		
		else if(strcmp(child2->type, "int") == 0  && return_pointers(child1->type)>0){
			if(DEBUG_A)printf("1-pointer 2-int\n");
			node->type =  child1->type;
		}	

		else if(strcmp(child1->type, child2->type)==0){
			if(DEBUG_A)printf("igual\n");
			node->type = child1->type;
		}

		
		
		
	}
	child1->type = type1aux;
	child2->type = type2aux;

}

void is_Sub(Node * node)
{
	Node * child1 = node->child;
	Node * child2 = child1->brother;
	int aux_value1;
	int aux_value2;
	char * type1aux, * type2aux;

	type1aux = strdup(child1->type);
	type2aux = strdup(child2->type);


	if(child1->type != NULL){
		aux_value1 = aux_Arrray_Declarations(child1->type);
		aux_pointer(child1, aux_value1);	
	}
	if(child2->type != NULL){
		aux_value2 = aux_Arrray_Declarations(child2->type);
		aux_pointer(child2, aux_value2);	
	}


	
	if(DEBUG_A) printf("child1->type: %s\n", child1->value);
	if(DEBUG_A) printf("child2->type: %s\n", child2->value);
	if(child1 != NULL && child2 != NULL){
		if(strcmp(child1->type, "int") == 0 && strcmp(child2->type, "char") == 0){
			node->type = child1->type;
		}
		else if(strcmp(child1->type, child2->type) == 0){
			node->type = "int";
		}
		else if(strcmp(child1->type, "char") == 0 && strcmp(child2->type, "int") == 0){
			node->type = child2->type;
		}
		else if(strcmp(child1->type, "int") == 0 && strcmp(child2->type, "int") == 0){
			node->type = child1->type;
		}

		else if(return_pointers(child1->type) > 0 && strcmp(child2->type, "int") == 0){
			node->type = child1->type;
		}
		else if(return_pointers(child1->type) > 0 && strcmp(child2->type, "char") == 0){
			node->type = child1->type;
		}				
	
	}
	child1->type = type1aux;
	child2->type = type2aux;
}
int aux_Arrray_Declarations(char * value)
{
	//printf("value: %s\n", value);
	int n_pointers=0;
	int i;
	for(i =0; i < strlen(value)-1; i++){
		if(value[i] == '['){
			n_pointers++;
		}
	}
	//printf("n_pointers: %d\n", n_pointers);
	return n_pointers;
}
void is_Mul_Div_Mod(Node * node)
{
	Node * child1 = node->child;
	Node * child2 = child1->brother;
	int aux_value1;
	int aux_value2;
	char * type1aux, * type2aux;


	type1aux = strdup(child1->type);
	type2aux = strdup(child2->type);

	if(child1->type != NULL){
		aux_value1 = aux_Arrray_Declarations(child1->type);
		aux_pointer(child1, aux_value1);	
	}
	if(child2->type != NULL){
		aux_value2 = aux_Arrray_Declarations(child2->type);
		aux_pointer(child2, aux_value2);	
	}

	
	if(child1 != NULL && child2 != NULL){
		if(strcmp(child1->type, "int") == 0 && strcmp(child2->type, "int") == 0){
			node->type = child1->type;
		}
		else if(strcmp(child1->type, "char") == 0 && strcmp(child2->type, "char") == 0){
			node->type = "int";
		}
		else if(strcmp(child1->type, "int") == 0 && strcmp(child2->type, "char") == 0){
			node->type = child1->type;
		}
		else if(strcmp(child1->type, "char") == 0 && strcmp(child2->type, "int") == 0){
			node->type = child2->type;
		}
		
	}
	child1->type = type1aux;
	child2->type = type2aux;
}

void is_Plus_Minus(Node * node)
{
	Node * child1 = node->child;
	
	if(child1 != NULL){
		if(strcmp(child1->type, "int") == 0 ){
			node->type = child1->type;
		}
		else if(strcmp(child1->type, "char") == 0 ){
			node->type = "int";
		}
	}

}

int return_pointers(char * value)
{
	if(DEBUG_A) printf("value: %s\n", value);
	int i;
	int n_pointers = 0;
	for(i = 0; i < strlen(value); i++){
		if(value[i] == '*'){
			n_pointers++;
		}
	}
	if(DEBUG_A)printf("n_pointers: %d\n", n_pointers);
	return n_pointers;
}



void get_inside_comma(Node * node)
{
	if(DEBUG_A)printf("get_inside_comma\n");
	Node * temp1;
	temp1 = node->child;
	char * aux;
	int n_pointers = 0;
	if(temp1!=NULL)
	{
		Node * temp2 = temp1->brother;
		if(temp2 != NULL)
		{
			
			n_pointers = aux_Arrray_Declarations(temp2->type);
			if(DEBUG_A) printf("n_pointers: %d\n", n_pointers);
			if(DEBUG_A) printf("node->type: %s\n", temp2->type);

			if(n_pointers>0){
				//aux = (char*)malloc(strlen(temp2->type));
				aux = strdup(temp2->type); 
				aux_pointer(temp2, n_pointers);
				node->type = temp2->type;
				temp2->type = strdup(aux);	
			}
			else{
				node->type = temp2->type;	
			}
			
			//node->type = temp2->type;
			
		}
	}

}

void get_inside_addr(Node * node)
{
	Node * temp;
	temp = node->child;
	if(temp!=NULL)
	{
		node->type = temp->type;
		node->type = concat(node->type, "*");
	}
	
}


char * get_operator_type_result(Node * node)
{
	Node * child = node->child;
	
	if(child!=NULL)
	{
		return child->type;
	}
	return NULL;
}

char * return_symbol_name(Symbol * symbol)
{

	return symbol->type;

}

void get_add_type(Node * node)
{
	Node * temp1;
	Node * temp2;
	temp1 = node->child;
	if(temp1!=NULL)
	{
		temp2 = temp1->brother;
		if(temp2!=NULL)
		{
			node->type = temp1->type;
		}	
	}
}


void get_deref_type(Node * node)
{
	Node * temp = node->child;
	if(temp!=NULL)
	{
		node->type = strdup(temp->type);
		node->type[strlen(temp->type)-1] = '\0';
	}
}


char * get_expr_type(Node * node)
{
	Node * temp = node->child;
	char * aux;

	while(temp!=NULL)
	{
		if(strcmp(NODE_NAME[temp->node_type], "Id") == 0){
			aux = strdup(temp->value);
		}

		temp = temp->brother;
	}

	return aux;
}


void get_inside_id(Node * node)
{
	if (DEBUG_A) printf("[get_inside_id] node->value: %s\n", node->value);

	Symbol * symbol = search_symbol(node->value, current_table2);
	if(symbol!=NULL)
	{
		//printf("[get_inside_id] type: %s\n", symbol->type);
		node->type = symbol->type;
	}
	else
	{
		Table * table = search_table("global");
		Symbol * symbol2 = search_symbol(node->value, table);
		if(symbol2!=NULL)
		{
			//printf("[get_inside_id] type: %s\n", symbol2->type);
			node->type = symbol2->type;	
		}
		
	}
}


void get_inside_strlit(Node * node)
{

	//int length = strlen(node->value)-1;;

	int length = parse_strlit(node->value);
	
	char * aux;
	aux = (char*) malloc(sizeof(char)*(length+6));


	sprintf(aux, "char[%d]", length);

	//printf("get_inside_strlit: %s\n", aux);
	node->type = aux;	
}
	

int parse_strlit(char* str) {
    int size = 0;
    int flag = 0;
    int  i;
    for(i = 0; i < strlen(str); i++) {

        if(flag == 0) {
            size++;

            if(str[i] == '\\') {
                flag++;
            }
        } else {
            if( flag == 1 && (str[i] == 'n' || str[i] == 't' || str[i] == '\\' || str[i] == '\'' || str[i] == '\"') ) {
                flag = 0;
            } else if(flag == 4) {
                if(str[i] == '\\') {
                    flag = 1;
                } else {
                    flag = 0;
                }

                size++;
            } else if(isdigit(str[i]) &&   str[i]-'0' <= 7) {
                flag++;
            } else {
                if(str[i] == '\\') {
                    flag = 1;
                } else {
                    flag = 0;
                }

                size++;
            }
        }

    }

    return size - 1;
}