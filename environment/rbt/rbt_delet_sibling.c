/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbt_delet_sibling.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelikya <gmelikya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 15:53:42 by gmelikya          #+#    #+#             */
/*   Updated: 2025/01/19 15:53:44 by gmelikya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment_variables.h"

void	del_sibiling_is_red(t_tree *tree, t_node *node, t_node	**sibling)
{
	(*sibling)->color = BLACK;
	node->parent->color = RED;
	left_rotate(tree, node->parent);
	(*sibling) = node->parent->right;
}

t_node	*del_s_black_n_red(t_tree *tree, t_node *node, t_node	**sibling)
{
	if ((*sibling)->right->color == BLACK)
	{
		(*sibling)->left->color = BLACK;
		(*sibling)->color = RED;
		right_rotate(tree, (*sibling));
		(*sibling) = node->parent->right;
	}
	(*sibling)->color = node->parent->color;
	node->parent->color = BLACK;
	(*sibling)->right->color = BLACK;
	left_rotate(tree, node->parent);
	node = tree->root;
	return (node);
}

t_node	*del_left_of_sibling(t_tree *tree, t_node *node, t_node	**sibling)
{
	if ((*sibling)->color == RED)
		del_sibiling_is_red(tree, node, sibling);
	if ((*sibling)->left->color == BLACK
		&& (*sibling)->right->color == BLACK)
	{
		(*sibling)->color = RED;
		node = node->parent;
	}
	else
		node = del_s_black_n_red(tree, node, sibling);
	return (node);
}

void	del_r_sibling_is_red(t_tree *tree, t_node *node, t_node	**sibling)
{
	(*sibling)->color = BLACK;
	node->parent->color = RED;
	right_rotate(tree, node->parent);
	(*sibling) = node->parent->left;
}

t_node	*del_right_of_sibling(t_tree *tree, t_node *node, t_node	**sibling)
{
	if ((*sibling)->color == RED)
		del_r_sibling_is_red(tree, node, sibling);
	if ((*sibling)->left->color == BLACK
		&& (*sibling)->right->color == BLACK)
	{
		(*sibling)->color = RED;
		node = node->parent;
	}
	else
	{
		if ((*sibling)->right->color == RED)
		{
			(*sibling)->right->color = BLACK;
			(*sibling)->color = RED;
			left_rotate(tree, (*sibling));
			(*sibling) = node->parent->left;
		}
		(*sibling)->color = node->parent->color;
		node->parent->color = BLACK;
		(*sibling)->left->color = BLACK;
		right_rotate(tree, node->parent);
		node = tree->root;
	}
	return (node);
}
