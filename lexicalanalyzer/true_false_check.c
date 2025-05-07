/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   true_false_check.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelikya <gmelikya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 17:39:25 by gmelikya          #+#    #+#             */
/*   Updated: 2025/01/19 17:39:27 by gmelikya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment_variables.h"

int	is_white_space(char c)
{
	return (c == SPACE || (c >= TAB && c <= CR));
}

int	is_not_white_space(char c)
{
	return (c != 32 && !(c >= 9 && c <= 13));
}

int	is_not_quotes_and_colon(char c)
{
	return (c && (c != '"' && c != '\'' && c != ':'
			&& c != '/' && c != '=' && c != '-' && c != '+'));
}

int	is_quotes(char c)
{
	return (c == '"' && c == '\'');
}

int	is_not_separator(char c)
{
	return (c && (c != '|' && c != '<' && c != '>'));
}
