/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_case.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelikya <gmelikya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 17:00:01 by gmelikya          #+#    #+#             */
/*   Updated: 2025/01/19 17:24:37 by gmelikya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment_variables.h"

int	is_directory(t_command *cmd)
{
	DIR	*dir;

	dir = opendir(cmd->command);
	if (dir != NULL && (cmd->command[0] == '/' || cmd->command[0] == '.'))
	{
		error_message("minishell: ", cmd->command, "is a directory");
		set_unsigned_status(126);
		return (-1);
	}
	return (0);
}

int	path_check(t_command *cmd, char **full_path)
{
	if (is_directory(cmd) == -1)
		return (-1);
	if (ft_strlen(cmd->command) == 0 && cmd->type_command != 6)
	{
		error_message("minishell: ", cmd->command, "command not found");
		set_unsigned_status(127);
		return (-1);
	}
	if (!(*full_path) && (cmd->command[0] == '.' || cmd->command[0] == '/'))
	{
		error_message("minishell: ", cmd->command, "No such file or directory");
		set_unsigned_status(127);
		return (-1);
	}
	return (0);
}

int	path_case(t_shell *shell, t_command *cmd, char **full_path)
{
	if ((cmd->command[0] == '.' || cmd->command[0] == '/')
		&& access(cmd->command, X_OK) == 0)
	{
		(*full_path) = ft_strdup(cmd->command);
		if (!(*full_path))
			free_shell(shell, LAST_EXIT, DELETE_ENV, MALLOC_ERROR);
	}
	else if (((cmd->command[0] == '.' || cmd->command[0] == '/')
			&& access(cmd->command, X_OK) != 0))
	{
		error_message("minishell: ", cmd->command, strerror(errno));
		if (errno == ENOENT)
			set_unsigned_status(127);
		else if (errno == EACCES)
			set_unsigned_status(126);
		return (-1);
	}
	else if ((cmd->command[0] != '.'
			&& cmd->command[0] != '/') && (*full_path) == NULL)
		(*full_path) = find_executable(cmd->command, shell->handler, shell);
	if (path_check(cmd, full_path) == -1)
		return (-1);
	return (0);
}
