/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Simulacion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmatos-d <bmatos-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 18:16:39 by bmatos-d          #+#    #+#             */
/*   Updated: 2024/10/30 21:12:38 by bmatos-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



//  ┌──────────────────────────────────────────────────────────────────────────┐
//  │							 	HEADER									   │
//  └──────────────────────────────────────────────────────────────────────────┘
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include "./MLX-LNX/mlx.h"
#define NUM_TXT 	4
#define WIN_WID 	600
#define WIN_HEI 	500
#define TITLE__ 	"Cub3d Preliminary"
#define SPEED 		0.6
#define PLN_WID 	0.66
#define FORWARD 	1
#define BACKWARD 	-1



//  │────────────────────────────────STRUCT───────────────────────────────────│

typedef struct s_img
{
	void	*img_ptr;
	char	*pixels_ptr;
	int		bpp;
	int		endian;
	int		line_len;
}			t_img;

typedef struct s_parsed_data
{
																		// POS
	// Cuando parseas estes valores creo que 
	// es mejor que anades un 0.5 para estar 
	// en el medio del cuadrado no el rincon.
	double	pos_x;
	double	pos_y;


																		// ANGLE
			// Norte = 0
			// Este  = 0.5
			// Sur	 = 1
			// Oeste = 1.5
	double	angle;

																		// DIR / PLN
	// executa 
	// angletval(t_parsed_data *global);
	// despues y te da los proximos cuatro 
	// valores
	double	dir_x;
	double	dir_y;
	double	pln_x;
	double	pln_y;

																		// texturas and Colores
	//Hay que hacer una conversion
	int		top_colour;
	int		btm_colour;
	int		tmp_colour1;
	int		tmp_colour2;
	int		*texture_buffer[NUM_TXT];

																		//Map
	char	**map;
																		
																		
																		//RAY DATA
	//Informacion Temporania Por Cada Rayo
	double	horizontal_pixel;
	double	camera_angle_ratio;
	double	current_ray_x_component;
	double	current_ray_y_component;
	double	x_intercept_unit_distance;
	double	y_intercept_unit_distance;
	int 	current_cell_x;
	int 	current_cell_y;
	int		p_n_x_step;
	int		p_n_y_step;
	double	x_dist_traversed;
	double	y_dist_traversed;
	int		wall_type;
	float	wall_dist;
	int		wall_height;
	int		draw_start;
	int		draw_end;
	double	wall_impact;
	int		current_y_pixel;


																			//MLX
	void	*mlx_con;
	void	*mlx_win;
	t_img	mlx_img;
	
}	t_parsed_data;

//  ┌──────────────────────────────────────────────────────────────────────────┐
//  │							 	RENDER 									   │
//  └──────────────────────────────────────────────────────────────────────────┘
void	my_pixel_put(int x, int y, t_img *img, int colour)
{
	int	offset;

	offset = (y * img->line_len) + (x * (img->bpp / 8));
	*(unsigned int *)(img->pixels_ptr + offset) = colour;
}
//No hace falta ser asi podemos solo hacer colores.
void draw_ceiling_floor(t_parsed_data *global)
{
	int x;
	int y;

	x = -1;
	while (++x < WIN_WID)
	{
		y = -1;
		while (++y < WIN_HEI)
		{
			if (y < WIN_HEI/ 2)
				my_pixel_put(x, y, &global->mlx_img, global->btm_colour);
			else
				my_pixel_put(x, y, &global->mlx_img, global->top_colour);
		}
	}
	mlx_put_image_to_window(global->mlx_con, global->mlx_win, global->mlx_img.img_ptr, 0, 0);
}
void data(t_parsed_data *global)
{
	global->dir_x = cos(global->angle);
	global->dir_y = sin(global->angle);
	global->pln_x = -global->dir_y * PLN_WID;
	global->pln_y = global->dir_x * PLN_WID;
	global->camera_angle_ratio = (2 * global->horizontal_pixel / (double)WIN_WID) -1;
	global->current_ray_x_component = global->dir_x + global->pln_x * global->camera_angle_ratio;
	global->current_ray_y_component = global->dir_y + global->pln_y * global->camera_angle_ratio;
	global->x_intercept_unit_distance = fabs(1 / global->current_ray_x_component);
	global->y_intercept_unit_distance = fabs(1 / global->current_ray_y_component);
	global->current_cell_x = (int)(global->pos_x);
	global->current_cell_y = (int)(global->pos_y);
}
void initial_side_differences(t_parsed_data *global)
{
	global->p_n_x_step = 1;
	global->p_n_y_step = 1;
	if (global->current_ray_x_component < 0)
	{
		global->p_n_x_step = -1;
		global->x_dist_traversed = (global->pos_x - global->current_cell_x) * global->x_intercept_unit_distance; 
	}
	else
		global->x_dist_traversed = (1 + global->current_cell_x - global->pos_x) * global->x_intercept_unit_distance; 
	if (global->current_ray_y_component < 0)
	{
		global->p_n_y_step = -1;
		global->y_dist_traversed = (global->pos_y - global->current_cell_y) * global->y_intercept_unit_distance; 
	}
	else
		global->y_dist_traversed = (1 + global->current_cell_y - global->pos_y) * global->y_intercept_unit_distance; 
}
void dda(t_parsed_data *global)
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
			break;
	}
}
void wall_height(t_parsed_data *global)
{

	if (global->wall_type == 0)
		global->wall_dist = (global->current_cell_x - global->pos_x + (1 - global->p_n_x_step) / 2) / global->current_ray_x_component;
	else
		global->wall_dist = (global->current_cell_y - global->pos_y + (1 - global->p_n_y_step) / 2) / global->current_ray_y_component;
	global->wall_height = (int)(WIN_HEI / global->wall_dist);
	global->draw_start = -global->wall_height / 2 + WIN_HEI / 2;
	
	if (global->draw_start < 0)		
		global->draw_start = 0;
	
	global->draw_end = global->wall_height/ 2 + WIN_HEI / 2;
	
	if (global->draw_end >= WIN_HEI)
		global->draw_end = WIN_HEI - 1;

	if (global->wall_type == 0)
		global->wall_impact = global->pos_y + global->wall_dist * global->current_ray_y_component;
	else		
		global->wall_impact = global->pos_x + global->wall_dist * global->current_ray_x_component;
	global->wall_impact -= floor(global->wall_impact);
}
void drawing(t_parsed_data *global)
{
	//TODO->Textures
	global->current_y_pixel = global->draw_start;
	while (global->current_y_pixel <= global->draw_end)
	{
		if (global->wall_type == 0)
			my_pixel_put(WIN_WID - global->horizontal_pixel, global->current_y_pixel++, &global->mlx_img, global->tmp_colour1);
		else
			my_pixel_put(WIN_WID - global->horizontal_pixel, global->current_y_pixel++, &global->mlx_img, global->tmp_colour2);
	}
}
void find_walls(t_parsed_data *global)
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
void render(t_parsed_data *global)
{
	draw_ceiling_floor(global);
	find_walls(global);
	mlx_do_sync(global->mlx_con);
}
//  ┌──────────────────────────────────────────────────────────────────────────┐
//  │							 	EVENTS								   	   │
//  └──────────────────────────────────────────────────────────────────────────┘
int	close_handler(t_parsed_data *global)
{
	mlx_destroy_image(global->mlx_con, global->mlx_img.img_ptr);
	mlx_destroy_window(global->mlx_con, global->mlx_win);
	mlx_destroy_display(global->mlx_con);
	free(global->mlx_con);
	exit(EXIT_SUCCESS);
}

void move(int direction, t_parsed_data *global)
{
	global->pos_x += global->dir_x * SPEED * direction;
	if (global->map[(int)global->pos_x][(int)global->pos_y] == '1')
		global->pos_x -= global->dir_x * SPEED * direction;
	global->pos_y += global->dir_y * SPEED * direction;
	if (global->map[(int)global->pos_x][(int)global->pos_y] == '1')
		global->pos_y -= global->dir_y * SPEED * direction;
}

int	key_handler(int keysym, t_parsed_data *global)
{
	if (keysym == XK_Escape)
		return(close_handler(global), 1);
	else if (keysym == XK_Left)
		return((void)(global->angle += 0.1), render(global), 1);
	else if (keysym == XK_Right)
		return((void)(global->angle -= 0.1), render(global), 1);
	else if (keysym == XK_Up)
		return(move(FORWARD, global), render(global), 1);
	else if (keysym == XK_Down)
			return(move(BACKWARD, global), render(global), 1);
	return(0);
}
static void	events_init(t_parsed_data *global)
{
	mlx_hook(global->mlx_win, KeyPress, KeyPressMask, key_handler, global);
	mlx_hook(global->mlx_win, DestroyNotify, StructureNotifyMask, close_handler, global);
}

//  ┌──────────────────────────────────────────────────────────────────────────┐
//  │							 	MLX INIT								   │
//  └──────────────────────────────────────────────────────────────────────────┘
void window_init(t_parsed_data *global)
{
	global->mlx_con = mlx_init();
	if (global->mlx_con == NULL)
		return(free(global), exit(EXIT_FAILURE));
	global->mlx_win = mlx_new_window(global->mlx_con, WIN_WID, WIN_HEI, TITLE__);
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
			&global->mlx_img.bpp, &global->mlx_img.line_len, &global->mlx_img.endian);
	events_init(global);
}

//  ┌──────────────────────────────────────────────────────────────────────────┐
//  │							 	MAIN 									   │
//  └──────────────────────────────────────────────────────────────────────────┘


t_parsed_data *parsing_temp()
{
	t_parsed_data *ret;

	ret = malloc(sizeof(t_parsed_data));
	ret->top_colour = 11594476;
	ret->btm_colour = 12551447;
	ret->tmp_colour1 = 00000000;
	ret->tmp_colour2 = 55555555;
	ret->tmp_colour3 = 10000000;
	ret->tmp_colour4 = 15000000;
	return(ret);
}
int main()
{
	t_parsed_data   *global;
	char			**temp_map;

	global = parsing_temp(); 
	if (!global)
		exit(EXIT_FAILURE);
	//DELETE//////////////////////////////////////////////////////////////////
	temp_map = malloc(sizeof(char *) * 20);
	temp_map[0]  = strdup("1111111111111111111111111");
	temp_map[1]  = strdup("1000000000000000000000001");
	temp_map[2]  = strdup("1000000000000000000000011");
	temp_map[3]  = strdup("1000000000000000000000001");
	temp_map[4]  = strdup("1000000000000000000000001");
	temp_map[5]  = strdup("1000000000000000000000001");
	temp_map[6]  = strdup("1000000000000000000000001");
	temp_map[7]  = strdup("1000000000000000000000001");
	temp_map[8]  = strdup("1000000000000000000000001");
	temp_map[9]  = strdup("1000000111111111100000001");
	temp_map[10] = strdup("1000000000000000000000001");
	temp_map[11] = strdup("1000000000000000000000001");
	temp_map[12] = strdup("1000000000000000000000001");
	temp_map[13] = strdup("1000000000000000000000001");
	temp_map[14] = strdup("1000000000000000000000001");
	temp_map[15] = strdup("1000000000000000000000001");
	temp_map[16] = strdup("1000000000000000000000001");
	temp_map[17] = strdup("1000000000000000000000001");
	temp_map[18] = strdup("1000000000000000000000001");
	temp_map[19] = strdup("1111111111111111111111111");
	global->angle = 1 * M_PI;
	global->pos_x = 2;
	global->pos_y = 2;
	global->map = temp_map;
	//////////////////////////////////////////////////////////////////////

	
	window_init(global);
	render(global);
	render(global);
	mlx_loop(global->mlx_con);
	exit (EXIT_SUCCESS);
}

