/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davidga2 <davidga2@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-23 04:31:29 by davidga2          #+#    #+#             */
/*   Updated: 2024-11-23 04:31:29 by davidga2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

//  ┌──────────────────────────────────────────────────────────────────────────┐
//  │							 	EXIT 									   │
//  └──────────────────────────────────────────────────────────────────────────┘

static void	free_dbl(char **ptr)
{
	int	count;

	count = 0;
	while (ptr[count] != NULL)
		free(ptr[count++]);
	free(ptr);
}

int	close_handler(t_parsed_data *global)
{
	if (global)
	{
		if (global->mlx_img.img_ptr)
			mlx_destroy_image(global->mlx_con, global->mlx_img.img_ptr);
		if (global->mlx_win)
			mlx_destroy_window(global->mlx_con, global->mlx_win);
		if (global->texture_images[NORTH])
			mlx_destroy_image(global->mlx_con, global->texture_images[NORTH]);
		if (global->texture_images[EAST])
			mlx_destroy_image(global->mlx_con, global->texture_images[EAST]);
		if (global->texture_images[SOUTH])
			mlx_destroy_image(global->mlx_con, global->texture_images[SOUTH]);
		if (global->texture_images[WEST])
			mlx_destroy_image(global->mlx_con, global->texture_images[WEST]);
		if (global->mlx_con)
			mlx_destroy_display(global->mlx_con);
		if (global->mlx_con)
			free(global->mlx_con);
		if (global->map)
			free_dbl(global->map);
		free(global);
	}
	exit(EXIT_SUCCESS);
}
//  ┌──────────────────────────────────────────────────────────────────────────┐
//  │							 	EVENTS								   	   │
//  └──────────────────────────────────────────────────────────────────────────┘

static void	move(double dir, t_parsed_data *global)
{
	double	move_x;
	double	move_y;

	move_x = (global->dir_x * cos(dir) - global->dir_y * sin(dir)) * SPEED;
	move_y = (global->dir_x * sin(dir) + global->dir_y * cos(dir)) * SPEED;
	if (global->map[(int)(global->pos_x + move_x)][(int)global->pos_y] != '1')
		global->pos_x += move_x;
	if (global->map[(int)global->pos_x][(int)(global->pos_y + move_y)] != '1')
		global->pos_y += move_y;
}

static int	key_handler(int keysym, t_parsed_data *global)
{
	if (keysym == XK_Escape)
		close_handler(global);
	if (keysym == XK_Left)
		global->angle += 0.1;
	if (keysym == XK_Right)
		global->angle -= 0.1;
	if (keysym == XK_W || keysym == XK_w)
		move(FORWARD * M_PI * 0.5, global);
	if (keysym == XK_S || keysym == XK_s)
		move(BACKWARD * M_PI * 0.5, global);
	if (keysym == XK_A || keysym == XK_a)
		move(LEFT * M_PI * 0.5, global);
	if (keysym == XK_D || keysym == XK_d)
		move(RIGHT * M_PI * 0.5, global);
	render(global);
	return (0);
}

void	events_init(t_parsed_data *global)
{
	mlx_hook(global->mlx_win, KeyPress, KeyPressMask, key_handler, global);
	mlx_hook(global->mlx_win, DestroyNotify, StructureNotifyMask, \
	close_handler, global);
}
