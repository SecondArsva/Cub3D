/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davidga2 <davidga2@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-30 22:27:39 by davidga2          #+#    #+#             */
/*   Updated: 2024-10-30 22:27:39 by davidga2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void incorrect_args(int argc)
{
	if (argc < 2)
		ft_printf_error("You must introduce a map as an argument\n");
	else if (argc > 2)
		ft_printf_error("You cant introduce more arguments than a map\n");
}

int main(int argc, char **argv)
{
	t_cub3d *data;

	data = safe_malloc(sizeof(t_cub3d));
	if (argc != 2)
		return (incorrect_args(argc), 1);
	ft_parser(data);	
	return (0);
}