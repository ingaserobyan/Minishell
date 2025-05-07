/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quates_value.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelikya <gmelikya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 17:38:16 by gmelikya          #+#    #+#             */
/*   Updated: 2025/01/19 17:38:16 by gmelikya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment_variables.h"

void	while_shell_input(t_quates *idx, t_shell *shell)
{
	while (shell->input[idx->i])
	{
		if (shell->input[idx->i] == shell->input[idx->tmp])
		{
			idx->count++;
			idx->flag++;
		}
		if (idx->flag % 2 == 0)
			break ;
		idx->i++;
	}
	if (shell->input[idx->i])
		idx->i++;
	while (shell->input[idx->i] && (shell->input[idx->i] != '"'
			&& shell->input[idx->i] != '\''))
		idx->i++;
}

int	checking_quates_counts(t_quates idx, t_token **node, t_shell *shell)
{
	char	*str;

	str = "minishell: there are unclosed quotes\n";
	(void)node;
	while (shell->input[idx.i] != '\'' && shell->input[idx.i] != '"')
		idx.i++;
	while (shell->input[idx.i])
	{
		idx.tmp = idx.i;
		idx.count = 0;
		idx.flag = 0;
		while_shell_input(&idx, shell);
	}
	if (idx.count % 2 != 0)
	{
		set_unsigned_status(SYNTAX_ERROR);
		error_message(str, NULL, NULL);
		return (-1);
	}
	return (0);
}

void	get_quotes_value(t_shell *shell, int *i, t_quates *idx, t_token **node)
{
	(idx->tmp) = *i;
	(*i)++;
	while (shell->input[*i])
	{
		(idx->len)++;
		if (shell->input[*i] == shell->input[(idx->tmp)])
		{
			(*i)++;
			break ;
		}
		(*i)++;
	}
	(*node)->value = ft_substr(shell->input, (idx->tmp) + 1, (idx->len) - 1);
	if (!((*node)->value))
		free_shell(shell, LAST_EXIT, DELETE_ENV, MALLOC_ERROR);
}
