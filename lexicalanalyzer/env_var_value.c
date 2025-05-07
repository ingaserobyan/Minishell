/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelikya <gmelikya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 17:35:11 by gmelikya          #+#    #+#             */
/*   Updated: 2025/01/19 17:35:13 by gmelikya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment_variables.h"

void	if_type_six(t_shell *shell, t_token **node)
{
	(*node)->var_value = malloc(sizeof(char) * 2);
	if (!((*node)->var_value))
		free_shell(shell, LAST_EXIT, DELETE_ENV, MALLOC_ERROR);
	(*node)->var_value[0] = '$';
	(*node)->var_value[1] = '\0';
}

int	if_only_dollar(t_shell *shell, t_token **node)
{
	if ((*node)->value[0] == '$' && (*node)->value[1] == '$')
	{
		(*node)->var_value = ft_strdup((*node)->value);
		if (!((*node)->var_value))
			free_shell(shell, LAST_EXIT, DELETE_ENV, MALLOC_ERROR);
		return (1);
	}
	return (0);
}

void	get_env_var_value(char *value, t_shell *shell, t_token **node)
{
	int		j;

	j = 0;
	if (value == NULL || if_only_dollar(shell, node) == 1)
		return ;
	if ((*node)->type == 7)
	{
		if ((*node)->key != NULL)
			free((*node)->key);
		(*node)->key = ft_strdup(value);
		if (!(*node)->key)
			free_shell(shell, LAST_EXIT, NO_DELETE_ENV, MALLOC_ERROR);
	}
	if (value[j] == '$' && (value[j + 1] == '\0'
			|| value[j + 1] == 32
			|| (value[j + 1] >= 9 && value[j + 1] <= 13)))
	{
		if_type_six(shell, node);
		return ;
	}
	(*node)->var_value = ft_strdup_env(get_env(shell->handler, value, shell));
	if ((*node)->var_value == NULL)
		(*node)->var_value = ft_strdup("");
	if (!((*node)->var_value))
		free_shell(shell, LAST_EXIT, DELETE_ENV, MALLOC_ERROR);
}
