/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelikya <gmelikya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 15:39:06 by gmelikya          #+#    #+#             */
/*   Updated: 2025/01/19 15:39:10 by gmelikya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment_variables.h"

int	is_flag(char *line, char *flag, int i, int j)
{
	while (line[i] && flag[j])
	{
		if (line[i] != flag[j])
			return (FALSE);
		i++;
		j++;
	}
	if (line[i] == '\0' && line[j] == '\0')
		return (TRUE);
	else if (line[i] == '\0' && line[j] != '\0')
		return (FALSE);
	else
	{
		j--;
		while (line[i] != '\0')
		{
			if (line[i] != flag[j])
				return (FALSE);
			i++;
		}
	}
	return (TRUE);
}

int	echo_printing(char **args, int i)
{
	while (args[i] != NULL)
	{
		if (ft_strcmp_env(args[i], " ") != 0)
			write(STDOUT_FILENO, args[i], ft_strlen_env(args[i]));
		if (args[i + 1] != NULL && ft_strcmp_env(args[i], " ") != 0)
			write(STDOUT_FILENO, " ", ft_strlen_env(" "));
		i++;
	}
	return (i);
}

int	ft_echo(char **args)
{
	int	with_new_line;
	int	i;

	if (!args)
		return (0);
	i = 0;
	with_new_line = TRUE;
	if (ft_strcmp_ultra(args[i], "echo") != 0)
		return (1);
	i++;
	while (args[i] != NULL && is_flag(args[i], "-n", 0, 0))
	{
		with_new_line = FALSE;
		i++;
	}
	if (args[i] != NULL)
		i = echo_printing(args, i);
	if (with_new_line)
		write(STDOUT_FILENO, "\n", 1);
	set_unsigned_status(0);
	return (0);
}
