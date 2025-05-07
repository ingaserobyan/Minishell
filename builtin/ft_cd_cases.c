/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_cases.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelikya <gmelikya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 15:37:14 by gmelikya          #+#    #+#             */
/*   Updated: 2025/01/19 15:37:20 by gmelikya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment_variables.h"

char	*tilda_case(char *args, t_handler *handler, t_shell *shell)
{
	char	*temp;
	char	*tmp_str;

	tmp_str = NULL;
	temp = NULL;
	tmp_str = get_env(handler, "HOME", shell);
	if (!tmp_str)
	{
		error_msg_env("cd", args, "HOME not set", NULL);
		set_unsigned_status(1);
		temp = ft_strdup("");
		if (!temp)
			free_shell(shell, LAST_EXIT, DELETE_ENV, MALLOC_ERROR);
	}
	else
	{
		temp = cut_replace(args, "~", tmp_str);
		if (!temp)
			free_shell(shell, LAST_EXIT, DELETE_ENV, MALLOC_ERROR);
	}
	return (temp);
}

int	home_case(char **args, t_shell *shell, t_cd *cd_vars, char *exec_name)
{
	t_handler	*handler;

	handler = shell->handler;
	cd_vars->tmp_str = get_env(handler, "HOME", shell);
	if (cd_vars->tmp_str)
	{
		cd_vars->new_path = ft_strdup_env(cd_vars->tmp_str);
		if (!cd_vars->new_path)
		{
			set_unsigned_status(MALLOC_ERROR);
			free_shell(shell, LAST_EXIT, DELETE_ENV, get_status());
		}
	}
	else
	{
		set_unsigned_status(1);
		error_msg_env(exec_name, args[0], "HOME not set", NULL);
		return (-1);
	}
	return (0);
}

int	oldpwd_case(char **args, t_shell *shell, t_cd *cd_vars, char *exec_name)
{
	t_handler	*handler;

	handler = shell->handler;
	cd_vars->tmp_str = get_env(handler, "OLDPWD", shell);
	if (!cd_vars->tmp_str)
	{
		error_msg_env(exec_name, args[0], "OLDPWD not set", NULL);
		set_unsigned_status(1);
		return (-1);
	}
	else
	{
		cd_vars->new_path = ft_strdup_env(cd_vars->tmp_str);
		if (!cd_vars->new_path)
		{
			set_unsigned_status(MALLOC_ERROR);
			free_shell(shell, LAST_EXIT, DELETE_ENV, get_status());
		}
	}
	return (0);
}

int	path_is_valid(char **args, t_cd *cd_vars, char *exec_name)
{
	if (stat(cd_vars->new_path, &(cd_vars->path_info)) == -1)
	{
		error_msg_env(exec_name, args[0], args[1], strerror(errno));
		set_unsigned_status(1);
		return (FALSE);
	}
	if (!S_ISDIR(cd_vars->path_info.st_mode))
	{
		error_msg_env(exec_name, args[0], args[1], "Not a directory");
		set_unsigned_status(1);
		return (FALSE);
	}
	return (TRUE);
}

int	oldpwd_already_exist(t_handler *handler, char *old_path, t_node *old_pwd)
{
	int	status;

	status = 0;
	if (old_pwd->value == NULL)
		insert_to_list(old_pwd, handler->list);
	else
	{
		old_pwd->temp_value = old_pwd->value;
		old_pwd->value = NULL;
	}
	old_pwd->value = ft_strdup_env(old_path);
	if (!old_pwd->value)
		status = -1;
	free(old_pwd->temp_value);
	old_pwd->temp_value = NULL;
	return (status);
}
