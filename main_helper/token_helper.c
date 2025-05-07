/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelikya <gmelikya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 17:53:46 by gmelikya          #+#    #+#             */
/*   Updated: 2025/01/19 17:54:07 by gmelikya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <environment_variables.h>

void	from_val_value_to_val(t_shell *shell)
{
	t_token	*tmp_token;

	tmp_token = shell->token;
	while (tmp_token)
	{
		if (tmp_token->var_value != NULL)
		{
			free(tmp_token->value);
			tmp_token->value = tmp_token->var_value;
			tmp_token->var_value = NULL;
		}
		tmp_token = tmp_token->next;
	}
}

void	if_its_heredoc(t_shell *shell)
{
	t_token	*tmp_token;
	int		flag;

	flag = 0;
	tmp_token = shell->token;
	while (tmp_token)
	{
		if (tmp_token->type == 5)
		{
			if (if_its_not_dollar(shell) == 1)
			{
				flag++;
				break ;
			}
		}
		tmp_token = tmp_token->next;
	}
	if (flag != 0)
		add_dollar(shell);
	else
		from_val_value_to_val(shell);
}

void	join_tokens(t_shell *shell, t_token *tmp_token, int *flag)
{
	char	*str;
	t_token	*tmp;

	tmp = NULL;
	str = NULL;
	str = ft_strdup(tmp_token->value);
	free(tmp_token->value);
	tmp_token->value = ft_strjoin(str, tmp_token->next->value);
	if (!tmp_token->value)
		free_shell(shell, LAST_EXIT, DELETE_ENV, MALLOC_ERROR);
	free(str);
	tmp = tmp_token->next;
	tmp_token->next = tmp_token->next->next;
	(*flag)++;
	if (tmp->value)
		free(tmp->value);
	if (tmp->var_value)
		free(tmp->var_value);
	if (tmp->key)
		free(tmp->key);
	free(tmp);
}

void	checking_all_tokens(t_shell *shell)
{
	t_token	*tmp_token;
	int		flag;

	tmp_token = shell->token;
	flag = 0;
	if_its_heredoc(shell);
	while (tmp_token)
	{
		while (if_type_is(tmp_token) == 1)
			tmp_token = tmp_token->next;
		if (if_type_is_not(tmp_token) == 1)
			join_tokens(shell, tmp_token, &flag);
		if (flag == 0)
			tmp_token = tmp_token->next;
		flag = 0;
	}
}
