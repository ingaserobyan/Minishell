/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelikya <gmelikya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 17:35:26 by gmelikya          #+#    #+#             */
/*   Updated: 2025/01/19 17:35:28 by gmelikya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment_variables.h"

int	start_of_env_val(int *i, t_token **node, t_shell *shell, int *len)
{
	(*len) = 0;
	if (shell->input[(*i) + 1] == '"' || shell->input[(*i) + 1] == '\'')
	{
		(*i)++;
		(*node)->value = NULL;
		return (-1);
	}
	if (shell->input[(*i)] == '$' && shell->input[(*i) + 1] != '$')
		(*i)++;
	return (0);
}

void	while_is_not(int *i, int *len, t_shell *shell, int *tmp)
{
	(*tmp) = (*i);
	while (is_not_quotes_and_colon(shell->input[*i])
		&& is_not_white_space(shell->input[*i]))
	{
		(*i)++;
		(*len)++;
		if (shell->input[*i] == '$' && shell->input[(*i) - 1] != '$')
			break ;
	}
}

void	if_its_only_dollar(t_token **node, int *i)
{
	int	j;
	int	len;

	j = 0;
	len = 0;
	if ((*node)->value[j] == '$' && (*node)->value[j + 1] != '$')
		return ;
	while ((*node)->value[j] && (*node)->value[j] == '$')
	{
		j++;
		len++;
	}
	if (len % 2 != 0)
	{
		(*node)->value = ft_substr((*node)->value, 0, len - 1);
		(*i) = j -1;
		return ;
	}
	if (len > 1)
	{
		(*node)->value = ft_substr((*node)->value, 0, len);
		(*i) = j;
		return ;
	}
}

void	get_env_value(int *i, t_token **node, t_shell *shell, int *error_flag)
{
	int	len;
	int	tmp;

	if (start_of_env_val(i, node, shell, &len) == -1)
		return ;
	while_is_not(i, &len, shell, &tmp);
	if (shell->input[tmp - 1] == '$' && (shell->input[tmp] == '"'
			|| shell->input[tmp] == '\0' || is_white_space(shell->input[tmp])))
	{
		(*node)->value = ft_substr(shell->input, tmp - 1, 1);
		return ;
	}
	if (is_quotes(shell->input[*i]))
		len--;
	(*node)->value = ft_substr(shell->input, tmp, len);
	if (!((*node)->value))
		free_shell(shell, LAST_EXIT, DELETE_ENV, MALLOC_ERROR);
	checking_value((*node)->value, error_flag);
}
