/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelikya <gmelikya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 15:55:32 by gmelikya          #+#    #+#             */
/*   Updated: 2025/01/19 16:01:22 by gmelikya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment_variables.h"

void	print_node_tree(t_node *node, int print)
{
	if (print)
	{
		printf("declare -x %s", node->key);
		if (node->value != NULL)
			printf("=\"%s\"", node->value);
		printf("\n");
	}
}

void	print_node_list(t_node *node, int print)
{
	if (print)
	{
		printf("%s", node->key);
		if (node->value != NULL)
			printf("=%s", node->value);
		printf("\n");
	}
}

void	print_list(t_list *list)
{
	t_node	*tmp_node;

	tmp_node = list->head;
	while (tmp_node)
	{
		print_node_list(tmp_node, TRUE);
		tmp_node = tmp_node->next;
	}
}

void	print_tree_inorder(t_tree *tree, t_node *node)
{
	if (nodes_are_same(node, tree->nill))
		return ;
	print_tree_inorder(tree, node->left);
	print_node_tree(node, TRUE);
	print_tree_inorder(tree, node->right);
}
