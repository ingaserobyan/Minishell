/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_rb_node.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelikya <gmelikya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 15:53:32 by gmelikya          #+#    #+#             */
/*   Updated: 2025/01/19 15:59:36 by gmelikya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment_variables.h"

static void	replace_nodes(t_tree *tree, t_node *current, t_node *replace_with)
{
	if (nodes_are_same(current->parent, tree->nill))
		tree->root = replace_with;
	else if (nodes_are_same(current->parent->left, current))
		current->parent->left = replace_with;
	else
		current->parent->right = replace_with;
	replace_with->parent = current->parent;
}

static t_node	*find_minimum(t_tree *tree, t_node *root)
{
	if (nodes_are_same(root, tree->nill))
		return (root);
	while (!nodes_are_same(root->left, tree->nill))
		root = root->left;
	return (root);
}

void	delete_fixup(t_tree *tree, t_node *node)
{
	t_node	*sibling;

	sibling = tree->nill;
	while (!nodes_are_same(tree->root, node)
		&& node->color == BLACK)
	{
		if (nodes_are_same(node, node->parent->left))
		{
			sibling = node->parent->right;
			node = del_left_of_sibling(tree, node, &sibling);
		}
		else
		{
			sibling = node->parent->left;
			node = del_right_of_sibling(tree, node, &sibling);
		}
	}
	node->color = BLACK;
}

t_node	*del_replace_rotate(t_tree *tree, t_node *node, int *color_of_wr)
{
	t_node	*will_remove;
	t_node	*tmp;

	will_remove = find_minimum(tree, node->right);
	(*color_of_wr) = will_remove->color;
	tmp = will_remove->right;
	if (nodes_are_same(will_remove->parent, node))
		tmp->parent = will_remove;
	else
	{
		replace_nodes(tree, will_remove, will_remove->right);
		will_remove->right = node->right;
		will_remove->right->parent = will_remove;
	}
	replace_nodes(tree, node, will_remove);
	will_remove->left = node->left;
	will_remove->left->parent = will_remove;
	will_remove->color = node->color;
	return (tmp);
}

void	delete_from_tree(t_tree *tree, t_node *node)
{
	t_node	*will_remove;
	t_node	*tmp;
	int		color_of_wr;

	will_remove = node;
	color_of_wr = will_remove->color;
	if (nodes_are_same(node->left, tree->nill))
	{
		tmp = node->right;
		replace_nodes(tree, node, node->right);
	}
	else if (nodes_are_same(node->right, tree->nill))
	{
		tmp = node->left;
		replace_nodes(tree, node, node->left);
	}
	else
		tmp = del_replace_rotate(tree, node, &color_of_wr);
	if (color_of_wr == BLACK)
		delete_fixup(tree, tmp);
}
