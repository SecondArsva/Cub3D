/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sarrsize.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davidga2 <davidga2@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-07 03:57:53 by davidga2          #+#    #+#             */
/*   Updated: 2024-11-07 03:57:53 by davidga2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_sarrsize(char **arr)
{
	int	size;

	if (!arr)
		return (0);
	size = 0;
	while (arr[size])
		size++;
	return (size);
}