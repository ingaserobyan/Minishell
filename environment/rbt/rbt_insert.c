/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbt_insert.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelikya <gmelikya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 15:53:49 by gmelikya          #+#    #+#             */
/*   Updated: 2025/01/19 15:53:51 by gmelikya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment_variables.h"

void	uncle_is_right_child(t_node *n_uncle, t_tree *tree, t_node *node)
{
	if (n_uncle->color == RED)
	{
		set_color_black(node->parent);
		set_color_black(n_uncle);
		set_color_red(node->parent->parent);
		node = node->parent->parent;
	}
	else if (nodes_are_same(node, node->parent->right))
	{
		node = node->parent;
		left_rotate(tree, node);
	}
	else
	{
		set_color_black(node->parent);
		set_color_red(node->parent->parent);
		right_rotate(tree, node->parent->parent);
	}
}

void	uncle_is_left_child(t_node *n_uncle, t_tree *tree, t_node *node)
{
	if (n_uncle->color == RED)
	{
		set_color_black(node->parent);
		set_color_black(n_uncle);
		set_color_red(node->parent->parent);
		node = node->parent->parent;
	}
	else
	{
		if (nodes_are_same(node, node->parent->left))
		{
			node = node->parent;
			right_rotate(tree, node);
		}
		set_color_black(node->parent);
		set_color_red(node->parent->parent);
		left_rotate(tree, node->parent->parent);
	}
}

void	insert_fixup(t_tree *tree, t_node *node)
{
	t_node	*n_uncle;

	n_uncle = tree->nill;
	while (node->parent->color == RED)
	{
		if (nodes_are_same(node->parent, node->parent->parent->left))
		{
			n_uncle = node->parent->parent->right;
			uncle_is_right_child(n_uncle, tree, node);
		}
		else
		{
			n_uncle = node->parent->parent->left;
			uncle_is_left_child(n_uncle, tree, node);
		}
	}
	set_color_black(tree->root);
}

void	tree_insert_helper(t_node *new_node, t_tree *tree)
{
	t_node	*parent;
	t_node	*current;

	parent = tree->nill;
	current = tree->root;
	while (!nodes_are_same(current, tree->nill))
	{
		parent = current;
		if (ft_strcmp_env(new_node->key, current->key) < 0)
			current = current->left;
		else
			current = current->right;
	}
	new_node->parent = parent;
	if (nodes_are_same(parent, tree->nill))
		tree->root = new_node;
	else if (ft_strcmp_env(new_node->key, parent->key) < 0)
		parent->left = new_node;
	else
		parent->right = new_node;
	set_color_red(new_node);
	put_nills(new_node, tree);
	insert_fixup(tree, new_node);
	tree->nodes_count++;
	tree->nill->right = tree->root;
}
