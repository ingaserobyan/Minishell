/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelikya <gmelikya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 15:35:44 by gmelikya          #+#    #+#             */
/*   Updated: 2025/01/19 20:10:56 by gmelikya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment_variables.h"

int	g_exit_status = 0;

int	get_status(void)
{
	return (g_exit_status);
}

void	set_unsigned_status(int status)
{
	if (status == 258)
	{
		g_exit_status = 258;
		return ;
	}
	g_exit_status = (unsigned char)status;
}

char	*convert_exit_status(t_handler *handler, t_shell *shell)
{
	if (!handler)
		return (NULL);
	if (handler->exit_status)
	{
		free(handler->exit_status);
		handler->exit_status = NULL;
	}
	handler->exit_status = ft_itoa(get_status());
	if (!handler->exit_status)
	{
		set_unsigned_status(MALLOC_ERROR);
		free_shell(shell, LAST_EXIT, DELETE_ENV, get_status());
	}
	return (handler->exit_status);
}
