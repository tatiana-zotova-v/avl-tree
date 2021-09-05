#include <stdio.h>
#include "tree.h"

void interface_avl (struct avl *tree)
{
	int key, to_do, error, cnt;
	char value[256] = {0};
	struct avl *temp = NULL;

	printf ("Let's go create self-balancing binary search tree!\n\n"
			"Enter the key of the first node: ");
	scanf ("%d", &key);
	printf ("And the value what you want assign to it: ");
	scanf ("%s", value);
	tree = add_tree (tree, key, value);
	if (tree == NULL)
	{
		printf("Memmory allocation error\n");
		return;
	}

	printf ("\nWhat do you want to do with your avl?\n"
			"1 - add the new element\n"
			"2 - find an element by key\n"
			"3 - delete an elemet by key\n"
			"4 - print tree with value and height\n"
			"5 - print tree only with key\n"
			"0 - stop the programm\n\n");
	while (1)
	{
		scanf ("%d", &to_do);

		if (to_do == 0)
		{
			break;
		}

		else if (to_do == 1)
		{
			printf("\nEnter the key of the new node: ");
			scanf ("%d", &key);
			printf ("Enter the value what you want assign to it: ");
			scanf ("%s", value);
			tree = add_tree (tree, key, value);
		}

		else if (to_do == 2) 
		{
			printf("Enter the key of the node, what you want to find: ");
			scanf ("%d", &key);
			temp = find_node_avl (tree, key);
			if (temp == NULL)
				printf ("There is no such binary search tree");
		}

		else if (to_do == 3)
		{
			printf ("Enter the key of the node, what you want to delete: ");
			scanf ("%d", &key);
			error = del_elem_avl (&tree, key);
			if (error)
				printf ("There is no such binary search tree. Code: %d\n", error);
		}

		else if (to_do == 4 || to_do == 5)
		{
			
			if (to_do == 4)
				error = printf_avl_txt(tree);
			else if (to_do == 5)
				error = printf_avl(tree, 0);

			if (error)
			{
				printf ("The avl is empty\nDo you want to create a new avl?\n1 - yes\nelse numb - no\n");
				scanf ("%d", &cnt);
				if (cnt == 1)
				{
					printf ("Let's go create binary search tree!\n\n"
							"Enter the key of the first node: ");
					scanf ("%d", &key);
					printf ("And the value what you want assign to it: ");
					scanf ("%s", value);
					tree = add_tree (tree, key, value);
					if (tree == NULL)
					{
						printf("Memmory allocation error\n");
						return;
					}
				}

				else
					break;
			}
		}

		else if (to_do == 6)
			printf ("1 - add the new element\n"
					"2 - find an element by key\n"
					"3 - delete an elemet by key\n"
					"4 - print tree with value and height\n"
					"5 - print tree only with key\n"
					"0 - stop the programm\n\n");

		else 
		{
			printf ("\nYou entered incorrect numb, try again\n");
		}

		printf ("\nPress numb from 0 to 5 again dependening on you want\n"
				"If you don't remember the commands, press 6\n\n");
	}
	
	printf("Bye!\n");
}