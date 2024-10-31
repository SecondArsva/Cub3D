/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_malloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davidga2 <davidga2@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-30 22:45:22 by davidga2          #+#    #+#             */
/*   Updated: 2024-10-30 22:45:22 by davidga2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*safe_malloc(size_t bytes)
{
	void	*reserve;

	reserve = malloc(bytes);
	if (!reserve)
		exit(EXIT_FAILURE);
	return (reserve);
}
