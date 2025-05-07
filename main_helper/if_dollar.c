/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if_dollar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelikya <gmelikya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 17:48:00 by gmelikya          #+#    #+#             */
/*   Updated: 2025/01/19 17:53:01 by gmelikya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <environment_variables.h>

int	if_its_not_dollar(t_shell *shell)
{
	t_token	*token_tmp;
	int		i;

	i = 0;
	token_tmp = shell->token;
	while (token_tmp)
	{
		if (token_tmp->type == 6)
			return (1);
		else if (token_tmp->type == 7)
		{
			while (token_tmp->value[i])
			{
				if (token_tmp->value[i] == '$')
					return (1);
				i++;
			}
		}
		token_tmp = token_tmp->next;
	}
	return (0);
}

void	handle_tkn_value(t_token *tmp_token, char **join)
{
	if (tmp_token->type == 7)
		(*join) = ft_strdup(tmp_token->value);
	else if (tmp_token->type == 6 && tmp_token->value[0] == '$')
		(*join) = ft_strdup(tmp_token -> value);
	else if (tmp_token->type == 6 && tmp_token->value[0] != '$')
		(*join) = ft_strjoin("$", tmp_token->value);
	else
		(*join) = ft_strjoin("$", tmp_token->key);
}

void	add_dollar(t_shell *shell)
{
	t_token	*tmp_token;
	char	*join;

	join = NULL;
	tmp_token = shell->token;
	while (tmp_token)
	{
		if (tmp_token->type == 6 || tmp_token->key != NULL)
		{
			handle_tkn_value(tmp_token, &join);
			if (!join)
				free_shell(shell, LAST_EXIT, DELETE_ENV, MALLOC_ERROR);
			free(tmp_token->value);
			tmp_token->value = ft_strdup(join);
			if (!tmp_token->value)
				free_shell(shell, LAST_EXIT, DELETE_ENV, MALLOC_ERROR);
		}
		tmp_token = tmp_token->next;
	}
}
