#include "binary_trees.h"

/**
 * avl_height - Gets the height of a node
 * @node: Pointer to node
 *
 * Return: Height of node
 */
static size_t avl_height(const avl_t *node)
{
	size_t left, right;

	if (node == NULL)
		return (0);

	left = avl_height(node->left);
	right = avl_height(node->right);

	return ((left > right ? left : right) + 1);
}

/**
 * update_balance - Rebalances a node
 * @node: Pointer to node
 *
 * Return: New root of subtree
 */
static avl_t *update_balance(avl_t *node)
{
	int balance;

	if (node == NULL)
		return (NULL);

	balance = (int)avl_height(node->left) -
		(int)avl_height(node->right);

	if (balance > 1)
	{
		if ((int)avl_height(node->left->left) <
		    (int)avl_height(node->left->right))
			node->left = binary_tree_rotate_left(node->left);
		return (binary_tree_rotate_right(node));
	}

	if (balance < -1)
	{
		if ((int)avl_height(node->right->right) <
		    (int)avl_height(node->right->left))
			node->right = binary_tree_rotate_right(node->right);
		return (binary_tree_rotate_left(node));
	}

	return (node);
}

/**
 * avl_insert_node - Inserts recursively and balances the tree
 * @root: Current subtree root
 * @value: Value to insert
 *
 * Return: New root of subtree
 */
static avl_t *avl_insert_node(avl_t *root, int value)
{
	if (root == NULL)
		return (binary_tree_node(NULL, value));

	if (value < root->n)
	{
		root->left = avl_insert_node(root->left, value);
		if (root->left != NULL)
			root->left->parent = root;
	}
	else if (value > root->n)
	{
		root->right = avl_insert_node(root->right, value);
		if (root->right != NULL)
			root->right->parent = root;
	}
	else
		return (root);

	return (update_balance(root));
}

/**
 * find_node - Finds the inserted node
 * @root: Tree root
 * @value: Value to find
 *
 * Return: Pointer to node, or NULL
 */
static avl_t *find_node(avl_t *root, int value)
{
	while (root != NULL)
	{
		if (value == root->n)
			return (root);

		if (value < root->n)
			root = root->left;
		else
			root = root->right;
	}

	return (NULL);
}

/**
 * avl_insert - Inserts a value in an AVL tree
 * @tree: Double pointer to tree root
 * @value: Value to insert
 *
 * Return: Pointer to created node, or NULL
 */
avl_t *avl_insert(avl_t **tree, int value)
{
	avl_t *node;

	if (tree == NULL)
		return (NULL);

	if (*tree != NULL && find_node(*tree, value) != NULL)
		return (NULL);

	*tree = avl_insert_node(*tree, value);
	if (*tree == NULL)
		return (NULL);

	(*tree)->parent = NULL;
	node = find_node(*tree, value);

	return (node);
}
