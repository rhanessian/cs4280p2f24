#include "token.h"

void printPreorder (struct node* root, int level) {
	if(root != NULL){
		printf("%*c%s:", level*2, ' ', root->lab);
		int i;
		int num = sizeof(root->tkArray) / sizeof(root->tkArray[0]);
		for (i = 0; i < num; i++){
			printf(" %s ",  root->tkArray[i].tkInstance);	
		}
		printf("\n");
		if (root->child1 != NULL)
			printPreorder(root->child1, level+1);
		if (root->child2 != NULL)
			printPreorder(root->child2, level+1);
		if (root->child3 != NULL)
			printPreorder(root->child3, level+1);
		if (root->child4 != NULL)
			printPreorder(root->child4, level+1);
	}
}