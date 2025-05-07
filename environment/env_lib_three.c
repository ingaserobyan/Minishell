/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lib_three.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelikya <gmelikya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 15:54:50 by gmelikya          #+#    #+#             */
/*   Updated: 2025/01/19 15:54:52 by gmelikya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment_variables.h"

static int	update_combined_with(char *combined, char *str, int i)
{
	int	k;

	k = 0;
	if (!str || !combined)
		return (i);
	while (str[k] && k < ft_strlen_env(str))
	{
		combined[i] = str[k];
		i++;
		k++;
	}
	return (i);
}

char	*ft_strjoin_ultra(char *s1, char *s2, char *s3)
{
	int		i;
	int		j;
	char	*combined;

	i = 0;
	j = 0;
	combined = NULL;
	if (!s1)
		return (NULL);
	if (!s3)
		return (ft_strdup_env(s1));
	combined = (char *) malloc(ft_strlen_env(s1)
			+ ft_strlen_env(s2) + ft_strlen_env(s3) + 1);
	if (!combined)
	{
		set_unsigned_status(MALLOC_ERROR);
		return (NULL);
	}
	i = update_combined_with(combined, s1, i);
	i = update_combined_with(combined, s2, i);
	i = update_combined_with(combined, s3, i);
	combined[i] = '\0';
	return (combined);
}

char	*free_chr_ptr(char *chr_ptr)
{
	if (chr_ptr)
		free(chr_ptr);
	return (NULL);
}

char	**free_double_chr_ptr(char **chr_ptr_ptr)
{
	int	i;

	i = 0;
	if (!chr_ptr_ptr)
		return (NULL);
	while (chr_ptr_ptr[i])
	{
		chr_ptr_ptr[i] = free_chr_ptr(chr_ptr_ptr[i]);
		i++;
	}
	free(chr_ptr_ptr);
	return (NULL);
}
