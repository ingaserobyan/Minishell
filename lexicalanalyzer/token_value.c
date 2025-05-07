/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_value.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelikya <gmelikya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 17:38:55 by gmelikya          #+#    #+#             */
/*   Updated: 2025/01/19 17:38:57 by gmelikya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment_variables.h"

void	space_checking( t_token **node, t_shell *shell)
{
	(*node)->value = (char *)malloc(sizeof(char) * 1 + 1);
	if (!(*node)->value)
	{
		free((*node)->value);
		free_shell(shell, LAST_EXIT, DELETE_ENV, MALLOC_ERROR);
	}
	(*node)->value[0] = ' ';
	(*node)->value[1] = '\0';
	return ;
}

void	get_word_value(t_shell *shell, int *i, t_token **node)
{
	int	len;
	int	tmp;

	len = 0;
	tmp = (*i);
	while (shell->input[*i] && (shell->input[*i] != '<'
			&& shell->input[*i] != '>' && shell->input[*i] != '|'
			&& shell->input[*i] != '$' && shell->input[*i] != '"'
			&& shell->input[*i] != '\'')
		&& is_not_white_space(shell->input[*i]))
	{
		(*i)++;
		len++;
	}
	(*node)->value = ft_substr(shell->input, tmp, len);
	if (!(*node)->value)
		free_shell(shell, LAST_EXIT, DELETE_ENV, MALLOC_ERROR);
}

void	dollar_or_sep(int *i, t_shell *shell, t_token **node, int *error_flag)
{
	if (shell->input[*i] == '>' || shell->input[*i] == '<'
		|| shell->input[*i] == '|')
		get_spr_value(i, node, shell, error_flag);
	else if (shell->input[*i] == '$')
	{
		get_env_value(i, node, shell, error_flag);
		get_env_var_value((*node)->value, shell, node);
	}
}

void	spc_or_word(int *i, t_shell *shell, t_token **node)
{
	if (is_white_space(shell->input[*i]))
		space_checking(node, shell);
	else
		get_word_value(shell, i, node);
}

void	token_value(int *i, t_shell *shell, t_token **node, int *error_flag)
{
	t_quates	idx;

	idx = quates_idx();
	idx.error_flag = 0;
	if (shell->input[*i] == '>' || shell->input[*i] == '<'
		|| shell->input[*i] == '|' || shell->input[*i] == '$')
		dollar_or_sep(i, shell, node, error_flag);
	else if (shell->input[*i] == '\'')
	{
		(*error_flag) = checking_quates_counts(idx, node, shell);
		if ((*error_flag) == -1)
			return ;
		get_quotes_value(shell, i, &idx, node);
	}
	else if (shell->input[*i] == '"')
	{
		(*error_flag) = checking_quates_counts(idx, node, shell);
		if ((*error_flag) == -1)
			return ;
		get_quotes_value(shell, i, &idx, node);
		get_var_value_quates_cause(shell, node);
	}
	else
		spc_or_word(i, shell, node);
}
