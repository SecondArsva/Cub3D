/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmatos-d <bmatos-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 22:27:39 by davidga2          #+#    #+#             */
/*   Updated: 2024/11/20 23:08:19 by bmatos-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Parsing.h"
#include "../simulator/cub3d.h"

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
