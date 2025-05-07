/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelikya <gmelikya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 15:39:19 by gmelikya          #+#    #+#             */
/*   Updated: 2025/01/19 15:39:50 by gmelikya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment_variables.h"

char	ft_tolower_env(unsigned int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + 32);
	return (c);
}

int	ft_strcmp_ultra(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	while ((ft_tolower_env((unsigned char)s1[i])
			== ft_tolower_env((unsigned char)s2[i]))
		&& (s1[i] != '\0' && s2[i] != '\0'))
		i++;
	return (ft_tolower_env((unsigned char)s1[i])
		- ft_tolower_env((unsigned char)s2[i]));
}

int	ft_env(char **args, t_handler *handler, t_shell *shell)
{
	int		i;

	i = 0;
	if (!args || !handler)
		return (0);
	if (ft_strcmp_ultra(args[i], "env") != 0)
		return (1);
	i++;
	set_unsigned_status(0);
	if (args[i] == NULL)
		print_list(handler->list);
	else
	{
		set_unsigned_status(1);
		error_msg_env(shell->executable_name, args[0],
			"No arguments should be", NULL);
	}
	return (0);
}
