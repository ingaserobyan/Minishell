/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separator_checking.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelikya <gmelikya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 17:38:32 by gmelikya          #+#    #+#             */
/*   Updated: 2025/01/19 17:38:34 by gmelikya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment_variables.h"

void	cnt_env_more_than_one(int *error_flag)
{
	error_message("minishell: syntax error near unexpected token\n", NULL, NULL);
	set_unsigned_status(SYNTAX_ERROR);
	(*error_flag) = -1;
}

void	cnt_r_more_than_two(int *error_flag)
{
	error_message("minishell: syntax error near unexpected token\n", NULL, NULL);
	set_unsigned_status(SYNTAX_ERROR);
	(*error_flag) = -1;
}

void	checking_value(char *str, int *error_flag)
{
	t_count	val_count;

	val_count = init_count();
	while (str[val_count.i])
	{
		if (str[val_count.i] == '$')
			val_count.count_env++;
		else if (str[val_count.i] == '|')
			val_count.count_pipe++;
		else if (str[val_count.i] == '<')
			val_count.count_r_in++;
		else if (str[val_count.i] == '>')
			val_count.count_r_out++;
		val_count.i++;
	}
	if ((*error_flag) == 0 && (val_count.count_pipe > 1))
		cnt_env_more_than_one(error_flag);
	else if ((*error_flag) == 0 && (val_count.count_r_in > 2
			|| val_count.count_r_out > 2))
		cnt_r_more_than_two(error_flag);
	if ((*error_flag) == -1)
		free(str);
}

void	checking_separator_value(char *input, int *i, t_init *idx)
{
	while (input[*i])
	{
		if (input[(*i)] == '|')
		{
			idx->len_pipe++;
			if (idx->len_pipe > 1 && input[(*i) + 1] == '|')
				break ;
		}
		else if ((idx->len_pipe <= 0) && (input[(*i)] == '<'
				|| input[(*i)] == '>'))
		{
			idx->len_redir++;
			if (input[*i + 1] != input[*i] || idx->len_redir > 2)
			{
				(*i)++;
				break ;
			}
		}
		else
			break ;
		(*i)++;
	}
}

void	get_spr_value(int *i, t_token **node, t_shell *shell, int *error_flag)
{
	t_init	idx;

	idx = init_idx();
	idx.tmp = (*i);
	checking_separator_value(shell->input, i, &idx);
	if (idx.len_pipe > 0)
		(*node)->value = ft_substr(shell->input, idx.tmp, idx.len_pipe);
	else
		(*node)->value = ft_substr(shell->input, idx.tmp, idx.len_redir);
	if (!((*node)->value))
		free_shell(shell, LAST_EXIT, DELETE_ENV, MALLOC_ERROR);
	checking_value((*node)->value, error_flag);
}
