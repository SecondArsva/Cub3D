/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_strdup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davidga2 <davidga2@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-30 22:45:23 by davidga2          #+#    #+#             */
/*   Updated: 2024-10-30 22:45:23 by davidga2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*safe_strdup(const char *s1)
{
	int		i;
	char	*new_ptr;

	i = 0;
	new_ptr = safe_malloc(ft_strlen(s1) + 1);
	if (!new_ptr)
		return (0);
	while (s1[i] != '\0')
	{
		new_ptr[i] = s1[i];
		i++;
	}
	new_ptr[i] = '\0';
	return (new_ptr);
}
