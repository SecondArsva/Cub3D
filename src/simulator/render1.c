/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmatos-d <bmatos-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 23:46:37 by bmatos-d          #+#    #+#             */
/*   Updated: 2024/11/20 23:24:58 by bmatos-d         ###   ########.fr       */
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

int	colour(t_parsed_data *global, int direction)
{
	return ((int)(global->texture_buffer[direction]
		[(int)(global->wall_impact * 160) + 160 * (int)
		(160 * ((global->current_y_pixel - (double)global->draw_start) \
			/ ((double)global->wall_height)))]));
}

static void	draw_ceiling_floor(t_parsed_data *global)
{
	int	horizontal_pixel;
	int	vertical_pixel;

	horizontal_pixel = -1;
	while (++horizontal_pixel <= WIN_WID)
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
}

void	render(t_parsed_data *global)
{
	draw_ceiling_floor(global);
	global->horizontal_pixel = 0;
	while (global->horizontal_pixel < WIN_WID)
	{
		data(global);
		global->horizontal_pixel++;
	}
	mlx_put_image_to_window(global->mlx_con, global->mlx_win,
		global->mlx_img.img_ptr, 0, 0);
}
