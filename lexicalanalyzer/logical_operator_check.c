/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logical_operator_check.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelikya <gmelikya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 17:37:58 by gmelikya          #+#    #+#             */
/*   Updated: 2025/01/19 17:38:00 by gmelikya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <environment_variables.h>

int	checking_log_op(t_token *tmp, char *str)
{
	if (ft_strcmp(tmp->value, "&") == 0)
	{
		error_message(str, "&", NULL);
		set_unsigned_status(SYNTAX_ERROR);
		return (-1);
	}
	else if (tmp->value[0] == '&' && tmp->value[1] != '&')
	{
		error_message(str, "&", NULL);
		set_unsigned_status(SYNTAX_ERROR);
		return (-1);
	}
	else if (tmp->value[0] == '&' && tmp->value[1] == '&')
	{
		error_message(str, "&&", NULL);
		set_unsigned_status(SYNTAX_ERROR);
		return (-1);
	}
	return (0);
}

int	if_its_control_operator(t_shell *shell)
{
	t_token	*tmp;
	char	*str;

	str = "minishell: syntax error near unexpected token ";
	tmp = shell->token;
	while (tmp)
	{
		if (checking_log_op(tmp, str) == -1)
			return (-1);
		tmp = tmp->next;
	}
	return (0);
}
