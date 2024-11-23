/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davidga2 <davidga2@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-23 04:29:03 by davidga2          #+#    #+#             */
/*   Updated: 2024-11-23 04:29:03 by davidga2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	incorrect_args(t_data **data, int argc)
{
	free(*data);
	if (argc < 2)
		err_exit("you must introduce a map as an argument");
	else if (argc > 2)
		err_exit("you cant introduce more arguments than a single map");
}

void	init_data_bools(t_data *data)
{
	data->map_finded = false;
	data->player_finded = false;
	data->f_finded = false;
	data->c_finded = false;
}

/*	data initialization for correct use of the structure */
void	init_data(t_data *data)
{
	data->i = 0;
	data->j = 0;
	data->arg_path = NULL;
	data->cub_fd = 0;
	data->n_img_path = NULL;
	data->s_img_path = NULL;
	data->e_img_path = NULL;
	data->w_img_path = NULL;
	data->n_fd = -1;
	data->s_fd = -1;
	data->e_fd = -1;
	data->w_fd = -1;
	data->f_red = -1;
	data->f_green = -1;
	data->f_blue = -1;
	data->c_red = -1;
	data->c_green = -1;
	data->c_blue = -1;
	data->map = NULL;
	data->player_pos_x = 0.0;
	data->player_pos_y = 0.0;
	data->player_angle = UNKNOWN;
	data->line = NULL;
	init_data_bools(data);
}

void	parser(char *arg, t_data *data)
{
	init_data(data);
	check_arg_len(arg, data);
	check_file_extension(data);
	check_file_existence(data);
	get_cub_content(data);
	check_parsed_content(data);
}
