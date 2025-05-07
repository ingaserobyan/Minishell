/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelikya <gmelikya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 15:40:01 by gmelikya          #+#    #+#             */
/*   Updated: 2025/01/19 15:40:01 by gmelikya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment_variables.h"

int	is_numeric(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (FALSE);
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (!is_digit(str[i]))
			return (FALSE);
		if (i > 19)
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int	is_numeric_checks(t_shell *shell, int i)
{
	if ((shell->word->args[i + 1]) != NULL)
	{
		error_msg_env(shell->executable_name,
			shell->word->args[0], "too many arguments", NULL);
		set_unsigned_status(1);
	}
	else
	{
		if (ft_strlen(shell->word->args[i]) < 19)
			set_unsigned_status(ft_atoi(shell->word->args[i]));
		else
		{
			error_msg_env(shell->executable_name,
				shell->word->args[1], "numeric argument required", NULL);
			set_unsigned_status(255);
		}
		exit(get_status());
	}
	return (i);
}

int	ft_exit(t_shell *shell)
{
	int	i;

	i = 0;
	printf("exit\n");
	if ((ft_strcmp(shell->word->args[i], "exit") == 0)
		&& (shell->word->args[1] == NULL))
		exit(get_status());
	i++;
	if (is_numeric(shell->word->args[i]))
	{
		i = is_numeric_checks(shell, i);
		return (0);
	}
	if (!is_numeric(shell->word->args[i]))
	{
		error_msg_env(shell->executable_name, shell->word->args[0],
			shell->word->args[1], "numeric argument required");
		set_unsigned_status(255);
		exit(get_status());
	}
	return (0);
}
