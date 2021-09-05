#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

struct avl *new_avl(int key, char *value)
{
	struct avl *node;
	node = malloc(sizeof(struct avl));
	if(node == NULL)
		return NULL;

	node->value = malloc(sizeof(char)*strlen(value));
	if(node->value == NULL)
		return NULL;

	node->height = 0;
	node->key = key;
	strncpy(node->value, value, strlen(value));
	node->left = NULL;
	node->right = NULL;

	return node;
}

int height(struct avl* tree)
{
	if(tree == NULL)
		return -1;
	else 
		return tree->height;
}

int now_h(struct avl *tree)
{
	if(tree == NULL)
		return -1;
	if(height(tree->left) > height(tree->right))
		return height(tree->left) + 1;
	else 
		return height(tree->right) + 1;
}

int balance(struct avl *tree)
{
	if(tree == NULL)
		return 3;
	return(height(tree->left) - height(tree->right));
}

struct avl *r_rotation(struct avl *tree)
{
	struct avl *temp = tree;

	tree = tree->left;
	temp->left = tree->right;
	tree->right = temp;

	temp->height = now_h(temp);
	tree->height = now_h(tree);

	return tree;
}

struct avl *l_rotation(struct avl *tree)
{
	struct avl *temp = tree;

	tree = tree->right;
	temp->right = tree->left;
	tree->left = temp;

	temp->height = now_h(temp);
	tree->height = now_h(tree);

	return tree;
}

struct avl *rl_rotation(struct avl *tree)
{
	tree->right = r_rotation(tree->right);
	tree = l_rotation(tree);

	tree->right->height = now_h(tree->right);
	tree->height = now_h(tree);

	return tree;
}

struct avl *lr_rotation(struct avl *tree)
{
	tree->left = l_rotation(tree->left);
	tree = r_rotation(tree);

	tree->left->height = now_h(tree->left);
	tree->height = now_h(tree);

	return tree;
}

void balancing(struct avl **tree)
{
	if(balance(*tree) == 2)
	{
		if(balance((*tree)->left) == 1)
			*tree = r_rotation((*tree));
		
		else if(balance((*tree)->left) == -1)
		{
			*tree = lr_rotation((*tree));
		}
	}

	else if(balance(*tree) == -2)
	{
		if(balance((*tree)->right) == -1)
			*tree = l_rotation(*tree);

		else if(balance((*tree)->right) == 1)
			*tree = rl_rotation(*tree);
	}
}

struct avl *add_tree(struct avl *tree, int key, char *value)
{
	if(tree == NULL)
		return new_avl(key, value);

	else if(key < tree->key)
		tree->left = add_tree(tree->left, key, value);

	else if(key > tree->key)
		tree->right = add_tree(tree->right, key, value);

	else
		printf("The element with this key already exist, you cannot add the same\n");

	balancing(&tree);

	tree->height = now_h(tree);

	return tree;
}

struct avl *find_node_avl(struct avl *tree, int key)
{
	struct avl* temp = tree;
	if (tree == NULL)
		return NULL;
	
	while (temp != NULL)
	{
		if (key == temp->key)
		{
			printf ("Value of the element with this key: %s\n", temp->value);
			return temp;
		}
		else if (key > temp->key)
			temp = temp->right;
		else 
			temp = temp->left;
	}

	printf ("There is no element with this key.\n");
	return tree;
}

struct avl *min_elem_avl(struct avl *tree)
{
	if (tree == NULL)
		return NULL;

	while (tree->left != NULL)
	{
		tree = tree->left;
	}
	return tree;
}

int del_elem_avl(struct avl **tree, int key)
{
	if (tree == NULL)
		return 1;

	if ((*tree)->key == key)
	{
		struct avl *to_del = *tree;
	
		if (to_del->right == NULL && to_del->left == NULL)
			*tree = NULL;

		else if (to_del->right == NULL || to_del->left == NULL)
		{	
			if (to_del->left == NULL)
				*tree = to_del->right;

			else if (to_del->right == NULL)
				*tree = to_del->left;
		}

		else
		{		
			struct avl *safe;
			
			*tree = min_elem_avl (to_del->right);

			if (*tree != to_del->right)
			{
				safe = (*tree)->right;
				(*tree)->right = to_del->right;
				(*tree)->right->left = safe;
			}

			(*tree)->left = to_del->left;
		}

		free (to_del->value);
		free (to_del);
	}

	else 
	{
		struct avl **temp = tree;

		if ((*temp)->right != NULL && key > (*temp)->key)
			del_elem_avl(&(*temp)->right, key);

		else if ((*temp)->left != NULL && key < (*temp)->key)
			del_elem_avl(&(*temp)->left, key);
	}

	if (*tree != NULL)
		(*tree)->height = now_h(*tree);

	balancing (tree);

	return 0;	
}

int printf_avl_txt(struct avl *avl)
{
	if(avl == NULL)
		return 1;

	printf("\n\tKey: %d\t\t\t\t height: %d\n", avl->key, avl->height);
	if(avl->left == NULL)
		printf("Left: NULL\t");

	else
		printf("Left: %d \t", (avl->left)->key);

	if(avl->right == NULL)
		printf("Right: NULL\n");

	else
		printf("Right: %d\n", (avl->right)->key);

	printf_avl_txt(avl->left);
	printf_avl_txt(avl->right);

	return 0;
}

int printf_avl(struct avl* avl, int level)
{
	if(avl == NULL)
		return 1;

	for (int i = 0; i < level; i++)
		printf("\t");

	printf("%d\n", avl->key);

	printf_avl(avl->left, level + 1);
	printf_avl(avl->right, level + 1);

	return 0;
}

void free_tree_avl(struct avl **tree)
{
	if(*tree == NULL)
		return;

	if ((*tree)->left != NULL)
		free_tree_avl(&(*tree)->left);

	if ((*tree)->right != NULL)
		free_tree_avl(&(*tree)->right);

	del_elem_avl(tree, (*tree)->key);
}