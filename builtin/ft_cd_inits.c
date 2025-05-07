/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_inits.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelikya <gmelikya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 15:37:46 by gmelikya          #+#    #+#             */
/*   Updated: 2025/01/19 15:37:57 by gmelikya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment_variables.h"

int	init_cut_helper(t_cut_helper *cut_helper,
	char *stack, char *needle, char *replace)
{
	cut_helper->i = 0;
	cut_helper->j = 0;
	cut_helper->k = 0;
	cut_helper->new_str = (char *) malloc(sizeof(char)
			* (ft_strlen_env(stack) - ft_strlen_env(needle)
				+ ft_strlen_env(replace) + 1));
	if (!cut_helper->new_str)
		return (1);
	return (0);
}

void	init_cd_vars(t_cd *cd_vars)
{
	cd_vars->new_path = NULL;
	cd_vars->tmp_str = NULL;
	cd_vars->old_path = NULL;
}
