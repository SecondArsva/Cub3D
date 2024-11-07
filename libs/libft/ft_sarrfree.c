/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sarrfree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davidga2 <davidga2@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-07 03:57:07 by davidga2          #+#    #+#             */
/*   Updated: 2024-11-07 03:57:07 by davidga2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_sarrfree(char ***arr)
{
	int	i;

	if (!arr || !arr[0])
		return ;
	i = -1;
	while (arr[0][++i])
	{
		if (arr[0][i])
		{
			free(arr[0][i]);
			arr[0][i] = NULL;
		}
	}
	free (*arr);
	*arr = NULL;
}
