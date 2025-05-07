/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelikya <gmelikya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 15:38:39 by gmelikya          #+#    #+#             */
/*   Updated: 2025/01/19 15:38:49 by gmelikya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment_variables.h"

static char	*expand_path(char *args, t_handler *handler, t_shell *shell)
{
	char	*temp;

	temp = NULL;
	if (!args)
		return (NULL);
	if (args[0] == '~')
		temp = tilda_case(args, handler, shell);
	else
	{
		temp = ft_strdup_env(args);
		if (!temp)
		{
			set_unsigned_status(MALLOC_ERROR);
			free_shell(shell, LAST_EXIT, DELETE_ENV, get_status());
		}
	}
	return (temp);
}

static int	cd_preparation(char **args, t_shell *shell,
				t_cd *cd_vars, char *exec_name)
{
	t_handler	*handler;

	handler = shell->handler;
	if (args[1] == NULL || ft_strcmp_env(args[1], "") == 0)
	{
		if (home_case(args, shell, cd_vars, exec_name) == -1)
			return (-1);
	}
	else if (ft_strcmp_env(args[1], "-") == 0)
	{
		if (oldpwd_case(args, shell, cd_vars, exec_name) == -1)
			return (-1);
	}
	else
	{
		cd_vars->new_path = expand_path(args[1], handler, shell);
		if (ft_strcmp_env(cd_vars->new_path, "") == 0)
		{
			cd_vars->new_path = free_chr_ptr(cd_vars->new_path);
			cd_vars->new_path = NULL;
			set_unsigned_status(1);
			return (-1);
		}
	}
	return (0);
}

static int	save_current_pwd(char **args, t_cd *cd_vars, char *exec_name)
{
	cd_vars->old_path = getcwd(NULL, 0);
	if (cd_vars->old_path == NULL)
	{
		error_msg_env(exec_name, args[0], strerror(errno), NULL);
		set_unsigned_status(errno);
		if (errno == ENOENT)
			error_msg_env(exec_name, args[0],
				"Please, restart minishell", NULL);
		return (-1);
	}
	return (0);
}

static int	do_chdir(char **args, t_cd *cd_vars, char *exec_name)
{
	if (chdir(cd_vars->new_path) == -1)
	{
		cd_vars->old_path = free_chr_ptr(cd_vars->old_path);
		error_msg_env(exec_name, args[0], strerror(errno), NULL);
		set_unsigned_status(errno);
		return (-1);
	}
	free(cd_vars->new_path);
	cd_vars->new_path = getcwd(NULL, 0);
	return (0);
}

int	ft_cd(char **args, t_handler *handler, char *exec_name, t_shell *shell)
{
	t_cd		cd_vars;

	if (!args)
		return (-1);
	init_cd_vars(&cd_vars);
	if (ft_strcmp_env(args[0], "cd") != 0)
		return (1);
	if (cd_preparation(args, shell, &cd_vars, exec_name) == -1)
		return (-1);
	if (!path_is_valid(args, &cd_vars, exec_name))
		return (-1);
	if (save_current_pwd(args, &cd_vars, exec_name) == -1)
		return (-1);
	if (do_chdir(args, &cd_vars, exec_name) == -1)
		return (-1);
	if (do_env_updates(handler, shell, &cd_vars) == -1)
		return (-1);
	cd_vars.new_path = free_chr_ptr(cd_vars.new_path);
	cd_vars.old_path = free_chr_ptr(cd_vars.old_path);
	set_unsigned_status(0);
	return (0);
}
