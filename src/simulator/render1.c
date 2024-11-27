/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmatos-d <bmatos-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 04:32:40 by davidga2          #+#    #+#             */
/*   Updated: 2024/11/27 17:44:28 by bmatos-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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
	int	img_height;
	int	img_width;
	int	hor_pix;
	int	ver_pix;

	img_width = global->dim[direction][0];
	img_height = global->dim[direction][1];
	hor_pix = global->wall_impact * img_width;
	if (global->wall_height < WIN_HEI)
		ver_pix = img_width * (int)(img_height * ((global->current_y_pixel
						- global->draw_start) / ((double)global->wall_height)));
	else
	{
		ver_pix = img_width * (int)(img_height * (((global->wall_height
							- WIN_HEI) / ((double)global->wall_height * 2))
					+ ((global->current_y_pixel - global->draw_start)
						/ ((double)global->wall_height))));
	}
	return ((int)(global->texture_buffer[direction][hor_pix + ver_pix]));
}

static void	draw_ceiling_floor(t_parsed_data *global)
{
	int	horizontal_pixel;
	int	vertical_pixel;

	horizontal_pixel = 0;
	while (horizontal_pixel < WIN_WID)
	{
		vertical_pixel = 0;
		while (vertical_pixel < WIN_HEI)
		{
			if (vertical_pixel < WIN_HEI / 2)
				my_pixel_put(horizontal_pixel, vertical_pixel,
					&global->mlx_img, global->top_colour);
			else
				my_pixel_put(horizontal_pixel, vertical_pixel,
					&global->mlx_img, global->btm_colour);
			vertical_pixel++;
		}
		horizontal_pixel++;
	}
}

void	render(t_parsed_data *global)
{
	draw_ceiling_floor(global);
	global->horizontal_pixel = -1;
	while (++global->horizontal_pixel < WIN_WID)
		data(global);
	mlx_put_image_to_window(global->mlx_con, global->mlx_win,
		global->mlx_img.img_ptr, 0, 0);
}
