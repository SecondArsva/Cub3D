/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmatos-d <bmatos-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 23:46:37 by bmatos-d          #+#    #+#             */
/*   Updated: 2024/11/19 17:24:03 by bmatos-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//  ┌──────────────────────────────────────────────────────────────────────────┐
//  │							 	RENDER 									   │
//  └──────────────────────────────────────────────────────────────────────────┘
void	my_pixel_put(int x, int y, t_img *img, int colour)
{
	*(unsigned int *)(img->pixels_ptr + (y * img->line_len)
			+ (x * (img->bpp / 8))) = colour;
}

void	draw_ceiling_floor(t_parsed_data *global)
{
	int	horizontal_pixel;
	int	vertical_pixel;

	horizontal_pixel = -1;
	while (++horizontal_pixel < WIN_WID)
	{
		vertical_pixel = -1;
		while (++vertical_pixel < WIN_HEI)
		{
			if (vertical_pixel < WIN_HEI / 2)
				my_pixel_put(horizontal_pixel, vertical_pixel,
					&global->mlx_img, global->top_colour);
			else
				my_pixel_put(horizontal_pixel, vertical_pixel,
					&global->mlx_img, global->btm_colour);
		}
	}
	mlx_put_image_to_window(global->mlx_con, global->mlx_win,
		global->mlx_img.img_ptr, 0, 0);
}

void	data(t_parsed_data *global)
{
	global->dir_x = cos(global->angle);
	global->dir_y = sin(global->angle);
	global->pln_x = -global->dir_y * PLN_WID;
	global->pln_y = global->dir_x * PLN_WID;
	global->camera_angle_ratio = (2 * global->horizontal_pixel
			/ (double)WIN_WID) - 1;
	global->current_ray_x_component = global->dir_x \
	+ global->pln_x * global->camera_angle_ratio;
	global->current_ray_y_component = global->dir_y \
	+ global->pln_y * global->camera_angle_ratio;
	global->x_intercept_unit_distance = fabs(1 \
	/ global->current_ray_x_component);
	global->y_intercept_unit_distance = fabs(1 \
	/ global->current_ray_y_component);
	global->current_cell_x = (int)(global->pos_x);
	global->current_cell_y = (int)(global->pos_y);
}

void	initial_side_differences(t_parsed_data *global)
{
	global->p_n_x_step = 1;
	global->p_n_y_step = 1;
	if (global->current_ray_x_component < 0)
	{
		global->p_n_x_step = -1;
		global->x_dist_traversed = (global->pos_x - global->current_cell_x) \
		* global->x_intercept_unit_distance;
	}
	else
		global->x_dist_traversed = (1 + global->current_cell_x - \
		global->pos_x) * global->x_intercept_unit_distance;
	if (global->current_ray_y_component < 0)
	{
		global->p_n_y_step = -1;
		global->y_dist_traversed = (global->pos_y - global->current_cell_y) \
		* global->y_intercept_unit_distance;
	}
	else
		global->y_dist_traversed = (1 + global->current_cell_y - \
		global->pos_y) * global->y_intercept_unit_distance;
}

void	dda(t_parsed_data *global)
{
	while (42)
	{
		if (global->x_dist_traversed < global->y_dist_traversed)
		{
			global->x_dist_traversed += global->x_intercept_unit_distance;
			global->current_cell_x += global->p_n_x_step;
			global->wall_type = 0;
		}
		else
		{
			global->y_dist_traversed += global->y_intercept_unit_distance;
			global->current_cell_y += global->p_n_y_step;
			global->wall_type = 1;
		}
		if (global->map[global->current_cell_x][global->current_cell_y] == '1')
			break ;
	}
}

void	wall_height(t_parsed_data *global)
{
	if (global->wall_type == 0)
		global->wall_dist = (global->current_cell_x - global->pos_x
				+ (1 - global->p_n_x_step) / 2)
			/ global->current_ray_x_component;
	else
		global->wall_dist = (global->current_cell_y - global->pos_y + \
		(1 - global->p_n_y_step) / 2) / global->current_ray_y_component;
	global->wall_height = (int)(WIN_HEI / global->wall_dist);
	global->draw_start = (-global->wall_height * SCALE / 2 + WIN_HEI / 2);
	if (global->draw_start < 0)
		global->draw_start = 0;
	global->draw_end = (global->wall_height * SCALE / 2 + WIN_HEI / 2);
	if (global->draw_end >= WIN_HEI)
		global->draw_end = WIN_HEI - 1;
	if (global->wall_type == 0)
		global->wall_impact = global->pos_y + global->wall_dist \
		* global->current_ray_y_component;
	else
		global->wall_impact = global->pos_x + global->wall_dist \
		* global->current_ray_x_component;
	global->wall_impact -= floor(global->wall_impact);
}

int	colour(t_parsed_data *global, int direction)
{
	return ((int)(global->texture_buffer[direction][(int)(global->wall_impact * 160) + 160 * (int)(160 * ((global->current_y_pixel - (double)global->draw_start) / ((double)global->wall_height)))]));
}

void	drawing(t_parsed_data *global)
{
	global->current_y_pixel = global->draw_start -1;
	while (++global->current_y_pixel <= global->draw_end)
	{
		if (global->wall_type == 0 && (global->current_ray_x_component) > 0)
			my_pixel_put(WIN_WID - global->horizontal_pixel,
				global->current_y_pixel,
				&global->mlx_img,
				colour(global, WEST));
		else if (global->wall_type == 0 && global->current_ray_x_component <= 0)
			my_pixel_put(WIN_WID - global->horizontal_pixel,
				global->current_y_pixel,
				&global->mlx_img,
				colour(global, EAST));
		else if (global->wall_type == 1 && global->current_ray_y_component > 0)
			my_pixel_put(WIN_WID - global->horizontal_pixel,
				global->current_y_pixel,
				&global->mlx_img,
				colour(global, SOUTH));
		else if (global->wall_type == 1 && global->current_ray_y_component <= 0)
			my_pixel_put(WIN_WID - global->horizontal_pixel,
				global->current_y_pixel,
				&global->mlx_img,
				colour(global, NORTH));
	}
}

void	find_walls(t_parsed_data *global)
{
	global->horizontal_pixel = 0;
	while (global->horizontal_pixel < WIN_WID)
	{
		data(global);
		initial_side_differences(global);
		dda(global);
		wall_height(global);
		drawing(global);
		global->horizontal_pixel++;
	}
}

void	render(t_parsed_data *global)
{
	draw_ceiling_floor(global);
	global->horizontal_pixel = 0;
	while (global->horizontal_pixel < WIN_WID)
	{
		data(global);
		initial_side_differences(global);
		dda(global);
		wall_height(global);
		drawing(global);
		global->horizontal_pixel++;
	}
}
