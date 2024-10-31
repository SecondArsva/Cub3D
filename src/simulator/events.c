/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmatos-d <bmatos-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 23:43:48 by bmatos-d          #+#    #+#             */
/*   Updated: 2024/11/01 00:55:48 by bmatos-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
		return (close_handler(global), 1);
	else if (keysym == XK_Left)
		return ((void)(global->angle += 0.1), render(global), 1);
	else if (keysym == XK_Right)
		return ((void)(global->angle -= 0.1), render(global), 1);
	else if (keysym == XK_W || keysym == XK_w)
		return (move(FORWARD * M_PI * 0.5, global), render(global), 1);
	else if (keysym == XK_S || keysym == XK_s)
		return (move(BACKWARD * M_PI * 0.5, global), render(global), 1);
	else if (keysym == XK_A || keysym == XK_a)
		return (move(LEFT * M_PI * 0.5, global), render(global), 1);
	else if (keysym == XK_D || keysym == XK_d)
		return (move(RIGHT * M_PI * 0.5, global), render(global), 1);
	return (0);
}

void	events_init(t_parsed_data *global)
{
	mlx_hook(global->mlx_win, KeyPress, KeyPressMask, key_handler, global);
	mlx_hook(global->mlx_win, DestroyNotify, StructureNotifyMask, \
	close_handler, global);
}
