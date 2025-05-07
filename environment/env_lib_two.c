/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lib_two.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelikya <gmelikya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 15:55:02 by gmelikya          #+#    #+#             */
/*   Updated: 2025/01/19 15:55:04 by gmelikya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment_variables.h"

int	is_alpha_env(unsigned int c)
{
	return ((c >= 'A' && c <= 'Z')
		|| (c >= 'a' && c <= 'z'));
}

int	is_underscore(unsigned int c)
{
	return (c == '_');
}

int	is_digit(unsigned int c)
{
	return (c >= '0' && c <= '9');
}

int	is_space(unsigned int c)
{
	return (c == 32 || (c >= 9 && c <= 13));
}
