/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_itoa.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davidga2 <davidga2@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-30 22:45:20 by davidga2          #+#    #+#             */
/*   Updated: 2024-10-30 22:45:20 by davidga2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_digitcounter(long int n)
{
	size_t	digits;

	if (n <= 0)
		digits = 1;
	else
	{
		digits = 0;
		n = n * 1;
	}
	while (n != 0)
	{
		n = n / 10;
		digits++;
	}
	return (digits);
}

char	*safe_itoa(int n)
{
	size_t		len;
	size_t		isneg;
	char		*new_ptr;

	if (n == -2147483648)
		return (safe_strdup("-2147483648"));
	len = ft_digitcounter(n);
	isneg = 0;
	new_ptr = safe_malloc((len + 1) * sizeof(char));
	if (!new_ptr)
		return (0);
	if (n < 0)
	{
		new_ptr[0] = '-';
		n = n * -1;
		isneg = 1;
	}
	new_ptr[len] = 0;
	while (len > (0 + isneg))
	{
		new_ptr[len - 1] = n % 10 + '0';
		n = n / 10;
		len--;
	}
	return (new_ptr);
}
