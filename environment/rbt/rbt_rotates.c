/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbt_rotates.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelikya <gmelikya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 15:53:56 by gmelikya          #+#    #+#             */
/*   Updated: 2025/01/19 15:53:59 by gmelikya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment_variables.h"

void	left_rotate(t_tree *tree, t_node *n_x)
{
	t_node	*n_y;

	n_y = n_x->right;
	n_x->right = n_y->left;
	if (!nodes_are_same(n_y->left, tree->nill))
		n_y->left->parent = n_x;
	n_y->parent = n_x->parent;
	if (nodes_are_same(n_x->parent, tree->nill))
		tree->root = n_y;
	else if (nodes_are_same(n_x, n_x->parent->left))
		n_x->parent->left = n_y;
	else
		n_x->parent->right = n_y;
	n_y->left = n_x;
	n_x->parent = n_y;
}

void	right_rotate(t_tree *tree, t_node *n_y)
{
	t_node	*n_x;

	n_x = n_y->left;
	n_y->left = n_x->right;
	if (!nodes_are_same(n_x->right, tree->nill))
		n_x->right->parent = n_y;
	n_x->parent = n_y->parent;
	if (nodes_are_same(n_y->parent, tree->nill))
		tree->root = n_x;
	else if (nodes_are_same(n_y->parent->left, n_y))
		n_y->parent->left = n_x;
	else
		n_y->parent->right = n_x;
	n_x->right = n_y;
	n_y->parent = n_x;
}
