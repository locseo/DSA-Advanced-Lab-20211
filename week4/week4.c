#include<stdio.h>
#include<string.h>
#include "jrb.h"
#include "jval.h"
void printBook(JRB tree)
{
	JRB node;
	jrb_traverse(node,tree)
	{
		printf("Name: %s Phonenumber: %ld\n",jval_s(node->key),jval_l(node->val));
		}
	}
JRB findKey(JRB tree,Jval value)
{
	JRB node;
	jrb_traverse(node,tree)
	{
		if (jval_l(node->val) == jval_l(value))
		return node;
	}
	return NULL;
}
void addEntry(JRB tree,char *name,long phoneNumber )
{
	Jval phone;
	phone.l = phoneNumber;
	JRB node = findKey(tree,phone);
	if(node == NULL)
	{
		jrb_insert_str(tree,strdup(name),new_jval_l(phoneNumber));
	}
	else
	{
		node->val = new_jval_l(phoneNumber);
	}
}
void deleteEntry(JRB tree,char *name)
{
	JRB node = jrb_find_str(tree,name);
	if(node != NULL)
	{
		jrb_delete_node(node);
	}
	else
	{
		printf("Can't find the entry!\n");
	}
}
void drop(JRB tree)
{
	JRB node;
	jrb_traverse(node,tree)
	{
		free(jval_s(node->key));
		jrb_free_tree(tree);
	}
}
int main()
{
	FILE *f = fopen("phonebook.txt","r");
	JRB book = make_jrb();
	while(!feof(f))
	{
		char name[20];
		long number;
		fscanf(f,"Name: %s Phonenumber: %ld\n",name,&number);
		addEntry(book,name,number);
	}
	fclose(f);
	printBook(book);
	return 0;
}
