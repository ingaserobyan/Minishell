/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_executable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelikya <gmelikya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 17:36:44 by gmelikya          #+#    #+#             */
/*   Updated: 2025/01/19 17:36:46 by gmelikya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment_variables.h"

int	if_access(t_find_executable *idx, int *i)
{
	int	flag_access;

	flag_access = 0;
	if (access(idx->full_path, X_OK) == 0)
	{
		free(idx->path_copy);
		free(idx->tmp_full_path);
		while (idx->token && idx->token[*i])
		{
			free(idx->token[*i]);
			(*i)++;
		}
		free(idx->token);
		return (1);
	}
	return (0);
}

int	init_executable(t_find_executable *idx,
t_shell *shell, int *i, char *command)
{
	while (idx->token[idx->i] != NULL)
	{
		idx->tmp_full_path = ft_strjoin(idx->token[idx->i], "/");
		if (!idx->tmp_full_path)
			free_shell(shell, LAST_EXIT, DELETE_ENV, MALLOC_ERROR);
		idx->full_path = ft_strjoin(idx->tmp_full_path, command);
		if (!idx->full_path)
			free_shell(shell, LAST_EXIT, DELETE_ENV, MALLOC_ERROR);
		if (if_access(idx, i) == 1)
			return (1);
		free(idx->full_path);
		free(idx->tmp_full_path);
		idx->i++;
	}
	return (0);
}

void	start_executable(t_find_executable *idx, t_shell *shell, int *i)
{
	idx->path_copy = ft_strdup(idx->path_env);
	if (!idx->path_copy)
		free_shell(shell, LAST_EXIT, DELETE_ENV, MALLOC_ERROR);
	idx->token = ft_split(idx->path_copy, ':');
	if (!idx->token)
	{
		while (idx->token && idx->token[*i])
		{
			free(idx->token[*i]);
			i++;
		}
		free(idx->token);
		free_shell(shell, LAST_EXIT, DELETE_ENV, MALLOC_ERROR);
	}
}

char	*find_executable(char *command, t_handler *handler, t_shell *shell)
{
	t_find_executable	idx;
	int					i;

	idx = find_executable_idx();
	idx.path_env = get_env(handler, "PATH", shell);
	i = 0;
	if (!idx.path_env)
	{
		set_unsigned_status(127);
		return (NULL);
	}
	start_executable(&idx, shell, &i);
	if (init_executable(&idx, shell, &i, command) == 1)
	{
		return (idx.full_path);
	}
	while (idx.token[i])
	{
		free(idx.token[i]);
		i++;
	}
	free(idx.token);
	free(idx.path_copy);
	return (NULL);
}
