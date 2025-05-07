/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelikya <gmelikya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 15:55:22 by gmelikya          #+#    #+#             */
/*   Updated: 2025/01/19 15:55:24 by gmelikya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment_variables.h"

char	*get_env(t_handler *handler, char *key, t_shell *shell)
{
	t_node		*tmp;
	char		*tmp_chr;
	char		*tmp_case;

	tmp_chr = NULL;
	tmp = NULL;
	tmp_case = NULL;
	if (!key || !handler)
		return (NULL);
	if (ft_strcmp_env(key, "?") == 0)
		return (handle_qst_mark(handler, shell));
	if (key[0] == '?')
	{
		tmp_chr = convert_exit_status(handler, shell);
		tmp_case = cut_replace(key, "?", tmp_chr);
		return (tmp_case);
	}
	if (ft_strcmp_env(key, "_") == 0)
		return (handle_underscore(handler));
	tmp = search_node(handler->tree, key);
	if (!nodes_are_same(tmp, handler->tree->nill))
		return (tmp->value);
	return (NULL);
}

void	insert_oldpwd(t_handler *handler, t_node *node)
{
	free(node->value);
	node->value = NULL;
	insert_to_tree(node, handler->tree);
}

void	insert_std_var(t_handler *handler, t_node *node)
{
	insert_to_list(node, handler->list);
	insert_to_tree(node, handler->tree);
}

t_handler	*load_system_env(char **env, t_handler *handler)
{
	int		i;
	t_node	*node;

	i = 0;
	while (env && env[i])
	{
		node = new_nodes_from_env(env[i]);
		if (!node && get_status() == MALLOC_ERROR)
			return (delete_handler_ptr(&handler));
		if (ft_strcmp_env(node->key, "OLDPWD") == 0)
			insert_oldpwd(handler, node);
		else if (ft_strcmp_env(node->key, "_") == 0)
		{
			insert_to_list(node, handler->list);
			handler->tmp = ft_strdup_env(node->value);
			if (get_status() == MALLOC_ERROR)
				return (delete_handler_ptr(&handler));
		}
		else
			insert_std_var(handler, node);
		i++;
	}
	return (handler);
}

t_handler	*load_env(char **env)
{
	t_handler	*handler;
	t_node		*node;
	int			i;

	i = 0;
	set_unsigned_status(0);
	handler = make_handler();
	if (!handler)
		return (NULL);
	handler->tree = make_tree();
	handler->list = make_list();
	if (get_status() == MALLOC_ERROR)
		return (delete_handler_ptr(&handler));
	if (!load_system_env(env, handler))
		return (NULL);
	node = search_node(handler->tree, "SHLVL");
	if (nodes_are_same(node, handler->tree->nill) != 0)
	{
		node = new_node_k_v("SHLVL", "0");
		if (!node && get_status() == MALLOC_ERROR)
			return (delete_handler_ptr(&handler));
		insert_std_var(handler, node);
	}
	return (handler);
}
