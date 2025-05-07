/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelikya <gmelikya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 15:45:43 by gmelikya          #+#    #+#             */
/*   Updated: 2025/01/19 15:45:46 by gmelikya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment_variables.h"

int	ft_pwd(char **args, t_shell *shell)
{
	char	*cwd;

	cwd = NULL;
	if (ft_strcmp_ultra(args[0], "pwd") != 0)
		return (1);
	set_unsigned_status(0);
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		error_msg_env(shell->executable_name,
			args[0], "Please, restart minishell", NULL);
		set_unsigned_status(1);
	}
	else
	{
		printf("%s\n", cwd);
		free(cwd);
		cwd = NULL;
	}
	return (0);
}
