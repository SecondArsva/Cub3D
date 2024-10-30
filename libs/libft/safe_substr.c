/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_substr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davidga2 <davidga2@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-30 22:45:27 by davidga2          #+#    #+#             */
/*   Updated: 2024-10-30 22:45:27 by davidga2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*safe_substr(char const *s, unsigned int start, size_t len)
{
	size_t	j;
	char	*new_ptr;

	j = 0;
	if (!s)
		return (0);
	if (start < ft_strlen(s))
	{
		if (len > ft_strlen(s) - start)
			len = ft_strlen(s) - start;
		new_ptr = safe_calloc(len + 1, sizeof(char));
		if (!new_ptr)
			return (0);
		while (s[start] != '\0' && j < len)
		{
			new_ptr[j] = s[start + j];
			j++;
		}
		new_ptr[j] = '\0';
		return (new_ptr);
	}
	new_ptr = safe_calloc(1, sizeof(char));
	if (!new_ptr)
		return (0);
	return (new_ptr);
}
