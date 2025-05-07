/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_updates.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelikya <gmelikya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 15:38:11 by gmelikya          #+#    #+#             */
/*   Updated: 2025/01/19 15:38:24 by gmelikya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment_variables.h"

int	update_old_pwd(t_handler *handler, char *old_path)
{
	t_node	*old_pwd;
	int		status;

	status = 0;
	old_pwd = search_node(handler->tree, "OLDPWD");
	if (!nodes_are_same(old_pwd, handler->tree->nill))
		status = oldpwd_already_exist(handler, old_path, old_pwd);
	else
	{
		old_pwd = new_node_k_v("OLDPWD", old_path);
		if (!old_pwd)
			status = -1;
		else
		{
			insert_to_tree(old_pwd, handler->tree);
			if (old_path)
				insert_to_list(old_pwd, handler->list);
		}
	}
	return (status);
}

int	update_pwd(t_handler *handler, char *new_path)
{
	t_node	*pwd;
	int		status;

	status = 0;
	pwd = search_node(handler->tree, "PWD");
	if (!nodes_are_same(pwd, handler->tree->nill))
	{
		if (pwd->value == NULL)
			insert_to_list(pwd, handler->list);
		else
			free(pwd->value);
		pwd->value = ft_strdup_env(new_path);
		if (new_path && !pwd->value)
			status = -1;
	}
	return (status);
}

int	do_env_updates(t_handler *handler, t_shell *shell, t_cd *cd_vars)
{
	if (update_old_pwd(handler, cd_vars->old_path) == -1)
	{
		cd_vars->new_path = free_chr_ptr(cd_vars->new_path);
		cd_vars->old_path = free_chr_ptr(cd_vars->old_path);
		free_shell(shell, LAST_EXIT, DELETE_ENV, get_status());
		return (-1);
	}
	if (update_pwd(handler, cd_vars->new_path) == -1)
	{
		cd_vars->new_path = free_chr_ptr(cd_vars->new_path);
		cd_vars->old_path = free_chr_ptr(cd_vars->old_path);
		free_shell(shell, LAST_EXIT, DELETE_ENV, get_status());
		return (-1);
	}
	return (0);
}

char	*update_exec_name(char *exec_name, t_shell *shell)
{
	char	*executable;

	executable = NULL;
	executable = cut_after(exec_name, '/');
	if (!executable)
		free_shell(shell, LAST_EXIT, DELETE_ENV, MALLOC_ERROR);
	return (executable);
}
