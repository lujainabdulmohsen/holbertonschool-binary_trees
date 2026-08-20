#include <stdlib.h>
#include "binary_trees.h"

/**
 * queue_node - Node of a queue.
 *
 * @tree: Pointer to a binary tree node.
 * @next: Pointer to the next queue node.
 */
typedef struct queue_node
{
	const binary_tree_t *tree;
	struct queue_node *next;
} queue_node_t;

/**
 * queue_free - Frees all nodes in a queue.
 *
 * @queue: Pointer to the first queue node.
 */
static void queue_free(queue_node_t *queue)
{
	queue_node_t *tmp;

	while (queue)
	{
		tmp = queue;
		queue = queue->next;
		free(tmp);
	}
}

/**
 * binary_tree_levelorder - Goes through a binary tree using level-order.
 *
 * @tree: Pointer to the root node.
 * @func: Pointer to a function to call for each node.
 */
void binary_tree_levelorder(const binary_tree_t *tree, void (*func)(int))
{
	queue_node_t *front, *back, *new_node;

	if (!tree || !func)
		return;

	front = malloc(sizeof(queue_node_t));
	if (!front)
		return;

	front->tree = tree;
	front->next = NULL;
	back = front;

	while (front)
	{
		func(front->tree->n);

		if (front->tree->left)
		{
			new_node = malloc(sizeof(queue_node_t));
			if (!new_node)
			{
				queue_free(front);
				return;
			}

			new_node->tree = front->tree->left;
			new_node->next = NULL;
			back->next = new_node;
			back = new_node;
		}

		if (front->tree->right)
		{
			new_node = malloc(sizeof(queue_node_t));
			if (!new_node)
			{
				queue_free(front);
				return;
			}

			new_node->tree = front->tree->right;
			new_node->next = NULL;
			back->next = new_node;
			back = new_node;
		}

		new_node = front;
		front = front->next;
		free(new_node);
	}
}
