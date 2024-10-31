/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmatos-d <bmatos-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 18:16:39 by bmatos-d          #+#    #+#             */
/*   Updated: 2024/11/01 00:19:15 by bmatos-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(void)
{
	t_parsed_data	*global;

	global = parsing_temp();
	if (!global)
		exit(EXIT_FAILURE);
	render(global);
	mlx_loop(global->mlx_con);
	exit (EXIT_SUCCESS);
}

//Directions still a bit off