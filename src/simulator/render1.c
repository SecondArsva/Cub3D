/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmatos-d <bmatos-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 04:32:40 by davidga2          #+#    #+#             */
/*   Updated: 2024/11/25 17:25:29 by bmatos-d         ###   ########.fr       */
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
	return ((int)(global->texture_buffer[direction]
		[(int)(global->wall_impact * 160) + 160 * (int)
		(160 * ((global->current_y_pixel - (double)global->draw_start) \
			/ ((double)global->wall_height)))]));
}

static void	draw_ceiling_floor(t_parsed_data *global)
{
	int	horizontal_pixel;
	int	vertical_pixel;

	horizontal_pixel = 0; // Start from 0, not -1
	while (horizontal_pixel < WIN_WID) // Loop correctly for all pixels
	{
		vertical_pixel = 0; // Start from 0 for vertical pixels
		while (vertical_pixel < WIN_HEI)
		{
			if (vertical_pixel < WIN_HEI / 2)
				my_pixel_put(horizontal_pixel, vertical_pixel,
					&global->mlx_img, global->top_colour);
			else
				my_pixel_put(horizontal_pixel, vertical_pixel,
					&global->mlx_img, global->btm_colour);
			vertical_pixel++; // Increment vertical_pixel correctly
		}
		horizontal_pixel++; // Increment horizontal_pixel
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
