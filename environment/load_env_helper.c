/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_env_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelikya <gmelikya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 15:55:17 by gmelikya          #+#    #+#             */
/*   Updated: 2025/01/19 15:55:19 by gmelikya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment_variables.h"

t_node	*new_nodes_from_env(char *line)
{
	t_node	*node;

	if (!line || !(*line))
		return (NULL);
	node = make_node();
	if (!node)
		return (NULL);
	node->key = cut_until(line, SEPARATOR);
	if (get_status() == MALLOC_ERROR)
	{
		free_node(node);
		return (NULL);
	}
	node->value = cut_after(line, SEPARATOR);
	if (get_status() == MALLOC_ERROR)
	{
		free_node(node);
		return (NULL);
	}
	return (node);
}

int	key_vs_node(char *key, t_node *node)
{
	return (ft_strcmp_env(key, node->key));
}

t_node	*search_node(t_tree *tree, char *key)
{
	t_node	*tmp;
	int		cmp_result;

	tmp = tree->root;
	while (!nodes_are_same(tmp, tree->nill))
	{
		cmp_result = key_vs_node(key, tmp);
		if (cmp_result == 0)
			return (tmp);
		else if (cmp_result < 0)
			tmp = tmp->left;
		else
			tmp = tmp->right;
	}
	return (tree->nill);
}

char	*handle_underscore(t_handler *handler)
{
	t_node		*tmp;

	tmp = handler->list->tail;
	while (tmp && ft_strcmp_env(tmp->key, "_") != 0)
	{
		tmp = tmp->prev;
	}
	if (tmp)
		return (tmp->value);
	else
		return (NULL);
}

char	*handle_qst_mark(t_handler *handler, t_shell *shell)
{
	char		*tmp_chr;

	tmp_chr = convert_exit_status(handler, shell);
	if (!tmp_chr)
		set_unsigned_status(MALLOC_ERROR);
	return (tmp_chr);
}
