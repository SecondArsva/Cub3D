/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmatos-d <bmatos-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 00:05:33 by bmatos-d          #+#    #+#             */
/*   Updated: 2024/11/20 23:30:43 by bmatos-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//  ┌──────────────────────────────────────────────────────────────────────────┐
//  │							 	MLX INIT								   │
//  └──────────────────────────────────────────────────────────────────────────┘
static void	window_init(t_parsed_data *global)
{
	global->mlx_con = mlx_init();
	if (global->mlx_con == NULL)
		return (free(global), exit(EXIT_FAILURE));
	global->mlx_win = mlx_new_window(global->mlx_con, WIN_WID, WIN_HEI, TITLE);
	if (global->mlx_win == NULL)
	{
		mlx_destroy_display(global->mlx_con);
		return (free(global->mlx_con), free(global), exit(EXIT_FAILURE));
	}
	global->mlx_img.img_ptr = mlx_new_image(global->mlx_con, WIN_WID, WIN_HEI);
	if (global->mlx_img.img_ptr == NULL)
	{
		mlx_destroy_window(global->mlx_con, global->mlx_win);
		mlx_destroy_display(global->mlx_con);
		return (free(global->mlx_con), free(global), exit(EXIT_FAILURE));
	}
	global->mlx_img.pixels_ptr = mlx_get_data_addr(global->mlx_img.img_ptr,
			&global->mlx_img.bpp, &global->mlx_img.line_len,
			&global->mlx_img.endian);
	events_init(global);
}

//  ┌──────────────────────────────────────────────────────────────────────────┐
//  │							    STRUCTINIT								   │
//  └──────────────────────────────────────────────────────────────────────────┘

int	file_exists(const char *path)
{
	return (access(path, F_OK) != -1);
}

void	load_texture(t_parsed_data *global, int direction, char *texture)
{
	int	img_height;
	//ERROR CHECK HERE

	global->texture_images[direction] = mlx_xpm_file_to_image(global->mlx_con,
			texture, &img_height, &img_height);
	global->texture_buffer[direction] = (unsigned int *)mlx_get_data_addr(\
			global->texture_images[direction], &img_height,
			&img_height, &img_height);
}

static void	load_textures(t_parsed_data *global, t_data *data)
{
	load_texture(global, NORTH, data->n_img_path);
	load_texture(global, EAST, data->e_img_path);
	load_texture(global, SOUTH, data->s_img_path);
	load_texture(global, WEST, data->w_img_path);
}

t_parsed_data	*parsing_temp(t_data *data)
{
	t_parsed_data	*ret;

	ret = calloc(sizeof(t_parsed_data), 1);
	ret->top_colour = data->c_red << 16 | data->c_green << 8 | data->c_blue;
	ret->btm_colour = data->f_red << 16 | data->f_green << 8 | data->f_blue;
	ret->map = ft_matrixdup(data->map);
	ret->angle = data->player_angle * M_PI / 2;
	ret->pos_y = data->player_pos_x;
	ret->pos_x = data->player_pos_y;
	window_init(ret);
	load_textures(ret, data);
	return (ret);
}
