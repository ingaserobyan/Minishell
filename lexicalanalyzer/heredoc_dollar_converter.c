/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_dollar_converter.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelikya <gmelikya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 17:37:03 by gmelikya          #+#    #+#             */
/*   Updated: 2025/01/19 17:37:07 by gmelikya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment_variables.h"

void	handle_dollar(t_shell *shell, t_env_heredoc *idx)
{
	idx->var_value = get_env(shell->handler, idx->tmp_str, shell);
	if (!idx->var_value)
		idx->var_value = ft_strdup(" ");
	free(idx->tmp_str);
	idx->tmp_str = NULL;
	idx->tmp_str = ft_strdup(idx->var_value);
	if (!(idx->tmp_str))
		free_shell(shell, LAST_EXIT, DELETE_ENV, MALLOC_ERROR);
	idx->var_value = NULL;
}

char	*get_joined(t_shell *shell, char *input, t_env_heredoc idx)
{
	if (input[idx.j] == '$'
		&& (is_not_white_space(input[idx.j + 1]) && input[idx.j + 1] != '\0'))
		idx.tmp_str = ft_substr(input, (idx.j + 1), (idx.len - 1));
	else
		idx.tmp_str = ft_substr(input, idx.j, idx.len);
	if (input[idx.j] == '$')
		handle_dollar(shell, &idx);
	idx.temp = idx.join;
	idx.join = ft_strjoin(idx.temp, idx.tmp_str);
	free(idx.temp);
	idx.temp = NULL;
	if (!(idx.join))
		free_shell(shell, LAST_EXIT, DELETE_ENV, MALLOC_ERROR);
	free(idx.tmp_str);
	idx.tmp_str = NULL;
	idx.len = 0;
	return (idx.join);
}

void	hdoc_dollar_cvrtr_middle(t_shell *shell,
char **input, t_env_heredoc *idx)
{
	while ((*input)[idx->i] && (*input)[idx->i] != '$')
	{
		idx->i++;
		idx->len++;
	}
	if (idx->len != 0)
	{
		idx->join = get_joined(shell, *input, *idx);
		idx->len = 0;
	}
	if ((*input)[idx->i] == '$')
	{
		idx->j = idx->i;
		while ((*input)[idx->i] && is_not_white_space((*input)[idx->i])
			&& is_not_quotes_and_colon((*input)[idx->i])
				&& is_not_separator((*input)[idx->i]))
		{
			idx->i++;
			idx->len++;
			if ((*input)[idx->i] == '$' || (*input)[idx->i] == '\'')
				break ;
		}
			idx->join = get_joined(shell, *input, *idx);
	}
}

void	hdoc_dollar_cvrtr_start(char **input, t_env_heredoc *idx)
{
	int	i;

	i = 0;
	while ((*input)[i])
	{
		if ((*input)[i] == '$')
		{
			(idx->flag) = -1;
			break ;
		}
		i++;
	}
}

void	hdoc_dollar_cvrtr(char **input, t_shell *shell)
{
	t_env_heredoc	idx;

	idx = init_env_heredoc();
	hdoc_dollar_cvrtr_start(input, &idx);
	if (idx.flag != -1)
		return ;
	idx.i = 0;
	while ((*input)[idx.i])
	{
		idx.j = idx.i;
		hdoc_dollar_cvrtr_middle(shell, input, &idx);
	}
	free((*input));
	if (idx.join == NULL)
		(*input) = ft_strdup("");
	else
		(*input) = idx.join;
}
