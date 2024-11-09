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

void	print_data(t_data *data)
{
	printf("\n----------------- DATA -----------------\n\n");
	printf("arg_path:		%s\n", data->arg_path);
	printf("cub_fd:			%i\n", data->cub_fd);
	printf("n_img_path:		%s\n", data->n_img_path);
	printf("s_img_path:		%s\n", data->s_img_path);
	printf("e_img_path:		%s\n", data->e_img_path);
	printf("w_img_path:		%s\n", data->w_img_path);
	printf("n_fd:			%i\n", data->n_fd);
	printf("s_fd:			%i\n", data->s_fd);
	printf("e_fd:			%i\n", data->e_fd);
	printf("w_fd:			%i\n", data->w_fd);
	printf("f_red:			%i\n", data->f_red);
	printf("f_green:		%i\n", data->f_green);
	printf("f_blue:			%i\n", data->f_blue);
	printf("c_red:			%i\n", data->c_red);
	printf("c_green:		%i\n", data->c_green);
	printf("c_blue:			%i\n", data->c_blue);
	ft_print_matrix(data->map, "map: ");
	printf("player_pos_x:	%f\n", data->player_pos_x);
	printf("player_pos_y:	%f\n", data->player_pos_y);
	printf("player_angle:	%i\n", data->player_angle);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	data = safe_malloc(sizeof(t_data));
	if (argc != 2)
		incorrect_args(data, argc);
	parser(argv[1], data);
	print_data(data);
	free_data(data);
	return (0);
}
