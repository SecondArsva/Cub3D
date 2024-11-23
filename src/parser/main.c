/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davidga2 <davidga2@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-23 04:29:25 by davidga2          #+#    #+#             */
/*   Updated: 2024-11-23 04:29:25 by davidga2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	main(int argc, char **argv)
{
	t_parsed_data	*global;
	t_data			*data;

	data = safe_malloc(sizeof(t_data));
	if (argc != 2)
		incorrect_args(&data, argc);
	parser(argv[1], data);
	global = parsing_temp(data);
	free_data(data);
	render(global);
	mlx_loop(global->mlx_con);
	exit (EXIT_SUCCESS);
}
