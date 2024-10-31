/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_strtrim.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davidga2 <davidga2@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-30 22:45:26 by davidga2          #+#    #+#             */
/*   Updated: 2024-10-30 22:45:26 by davidga2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*safe_strtrim(char const *s1, char const *set)
{
	size_t		i;
	size_t		j;
	char		*new_ptr;

	i = 0;
	j = ft_strlen(s1);
	if (!s1)
		return (0);
	if (!set)
		return (safe_strdup(s1));
	while (s1[i] && ft_strchr(set, s1[i]))
		i++;
	while (j > 0 && ft_strchr(set, s1[j]))
		j--;
	new_ptr = safe_substr(s1, i, (j + 1) - i);
	return (new_ptr);
}
