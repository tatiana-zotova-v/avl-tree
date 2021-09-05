#include <stdlib.h>
#include "tree.h"

int main()
{
	///*
	struct avl *tree = NULL;
	interface_avl(tree);
	free_tree_avl(&tree);
	//*/
	/*
	Dlya legkogo zapuska bez vvoda

	struct avl *tree = NULL;

	tree = add_tree(tree, 10, "10");
	tree = add_tree(tree, 5, "5");
	tree = add_tree(tree, 3, "3");
	tree = add_tree(tree, 11, "11");
	tree = add_tree(tree, 12, "12");
	tree = add_tree(tree, 7, "7");
	tree = add_tree(tree, 9, "9");
	tree = add_tree(tree, 8, "8");
	printf_avl_txt(tree);
	printf_avl(tree, 0);
	find_node_avl(tree, 12);
	del_elem_avl(&tree, 12);
	find_node_avl(tree, 12);
	printf_avl_txt(tree);
	free_tree_avl(&tree);
	printf("\n\n\n");
	int a = printf_avl(tree, 0);
	printf("%d\n", a);
	*/
	return 0;
}