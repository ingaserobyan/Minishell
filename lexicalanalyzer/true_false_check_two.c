/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   true_false_check_two.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelikya <gmelikya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 17:39:16 by gmelikya          #+#    #+#             */
/*   Updated: 2025/01/19 17:44:51 by gmelikya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment_variables.h"

int	is_redir(char *str, t_shell *shell)
{
	char	*error_mes;

	error_mes = "minishell: syntax error near unexpected token ";
	if (ft_strcmp(str, "|") == 0
		|| ft_strcmp(str, ">") == 0
		|| ft_strcmp(str, "<") == 0
		|| ft_strcmp(str, ">>") == 0
		|| ft_strcmp(str, "<<") == 0)
	{
		error_message(error_mes, str, NULL);
		set_unsigned_status(SYNTAX_ERROR);
		shell->seperator_error = -1;
		return (1);
	}
	return (0);
}

int	if_type_is(t_token *tmp_token)
{
	if (tmp_token->next && (tmp_token->type == 8
			|| tmp_token->type == 2
			|| tmp_token->type == 3
			|| tmp_token->type == 4
			|| tmp_token->type == 5
			|| tmp_token->type == 1))
		return (1);
	else
		return (0);
}

int	if_type_is_not(t_token *tmp_token)
{
	if (tmp_token->next && (tmp_token->next->type != 8
			&& tmp_token->next->type != 2
			&& tmp_token->next->type != 3
			&& tmp_token->next->type != 4
			&& tmp_token->next->type != 5
			&& tmp_token->next->type != 1))
		return (1);
	else
		return (0);
}

int	if_cmd_srct_init_is(t_token **tmp_token,
t_command **tmp_word)
{
	if ((*tmp_word)->command == NULL
		&& (*tmp_token)->type != 8 && (*tmp_token)->type != 2
		&& (*tmp_token)->type != 3 && (*tmp_token)->type != 4
		&& (*tmp_token)->type != 5 && ft_strcmp((*tmp_token)->value, "") != 0)
		return (1);
	else
		return (0);
}

int	if_srct_init_is(t_token **tmp_token)
{
	if ((*tmp_token)->type != 8 && (*tmp_token)->type != 2
		&& (*tmp_token)->type != 3
		&& (*tmp_token)->type != 4 && (*tmp_token)->type != 5
		&& ft_strcmp((*tmp_token)->value, "") != 0)
		return (1);
	else
		return (0);
}
