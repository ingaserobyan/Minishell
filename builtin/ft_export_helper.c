/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelikya <gmelikya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 15:40:26 by gmelikya          #+#    #+#             */
/*   Updated: 2025/01/19 15:40:44 by gmelikya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment_variables.h"

void	init_export_data(t_export_data *f_data)
{
	f_data->i = 0;
	f_data->key = NULL;
	f_data->node = NULL;
}

void	handle_malloc_error(t_shell *shell)
{
	if (MALLOC_ERROR == get_status())
	{
		set_unsigned_status(MALLOC_ERROR);
		error_msg_env("Not enough memory\n", NULL, NULL, NULL);
		free_shell(shell, LAST_EXIT, DELETE_ENV, get_status());
	}
}

int	is_valid_identifier(char *key)
{
	int	i;

	i = 0;
	if (!key || (!is_alpha_env(key[0]) && !is_underscore(key[0])))
		return (FALSE);
	i = 1;
	while (key[i])
	{
		if (!(is_alpha_env(key[i]) || is_digit(key[i])
				|| is_underscore(key[i]) || key[i] == 32))
			return (FALSE);
		i++;
	}
	return (TRUE);
}
