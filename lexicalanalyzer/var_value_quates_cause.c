/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_value_quates_cause.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelikya <gmelikya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 17:39:36 by gmelikya          #+#    #+#             */
/*   Updated: 2025/01/19 17:39:38 by gmelikya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment_variables.h"

void	start_of_join(t_env_init *idx, t_shell *shell, t_token **node)
{
	if ((*node)->value[idx->j] == '$'
		&& (is_not_white_space((*node)->value[idx->j + 1])
			&& (*node)->value[idx->j + 1] != '\0'))
		idx->tmp_str = ft_substr((*node)->value, (idx->j + 1), (idx->len - 1));
	else
		idx->tmp_str = ft_substr((*node)->value, idx->j, idx->len);
	if (!(idx->tmp_str))
	{
		del_env_init_idx(idx, -1);
		free_shell(shell, LAST_EXIT, DELETE_ENV, MALLOC_ERROR);
	}
}

void	join_value_var_value(t_env_init *idx, t_shell *shell, t_token **node)
{
	start_of_join(idx, shell, node);
	if ((*node)->value[idx->j] == '$')
	{
		get_env_var_value(idx->tmp_str, shell, node);
		free(idx->tmp_str);
		idx->tmp_str = NULL;
		idx->tmp_str = ft_strdup((*node)->var_value);
		if (!(idx->tmp_str))
		{
			del_env_init_idx(idx, -1);
			free_shell(shell, LAST_EXIT, DELETE_ENV, MALLOC_ERROR);
		}
		free((*node)->var_value);
		(*node)->var_value = NULL;
	}
	idx->temp = ft_strdup(idx->join);
	free(idx->join);
	idx->join = NULL;
	idx->join = ft_strjoin(idx->temp, idx->tmp_str);
	if (!(idx->join))
	{
		free_shell(shell, LAST_EXIT, DELETE_ENV, MALLOC_ERROR);
		del_env_init_idx(idx, -1);
	}
	del_env_init_idx(idx, 0);
}

void	checking_join(t_token **node, t_env_init *idx)
{
	if (idx->join == NULL)
		(*node)->value = ft_strdup("");
	else
	{
		(*node)->var_value = ft_strdup(idx->join);
		free(idx->join);
	}
}

void	start_of_quates_cause(t_shell *shell, t_token **node, t_env_init *idx)
{
	idx->j = idx->i;
	while ((*node)->value[idx->i] && (*node)->value[idx->i] != '$')
	{
		idx->i++;
		idx->len++;
	}
	if (idx->len != 0)
		join_value_var_value(idx, shell, node);
}

void	get_var_value_quates_cause(t_shell *shell, t_token **node)
{
	t_env_init	idx;

	idx = env_init_idx();
	while ((*node)->value[idx.i])
	{
		start_of_quates_cause(shell, node, &idx);
		if ((*node)->value[idx.i] == '$')
		{
			idx.j = idx.i;
			while ((*node)->value[idx.i]
				&& is_not_white_space((*node)->value[idx.i])
				&& is_not_quotes_and_colon((*node)->value[idx.i])
				&& is_not_separator((*node)->value[idx.i]))
			{
				idx.i++;
				idx.len++;
				if ((*node)->value[idx.i] == '$'
					|| (*node)->value[idx.i] == '\'')
					break ;
			}
			join_value_var_value(&idx, shell, node);
		}
	}
	checking_join(node, &idx);
}
