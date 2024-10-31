/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmatos-d <bmatos-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 23:40:35 by bmatos-d          #+#    #+#             */
/*   Updated: 2024/11/01 00:25:14 by bmatos-d         ###   ########.fr       */
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
#include <X11/X.h>
#include <X11/keysym.h>
#include <fcntl.h>
#include "./MLX-LNX/mlx.h"
#define NUM_TXT 	4
#define WIN_WID 	396
#define WIN_HEI 	218
#define TITLE	 	"Cub3d Preliminary"
#define SCALE		1
#define SPEED 		0.3
#define PLN_WID 	0.66
#define FORWARD 	0
#define BACKWARD 	2
#define LEFT	 	1
#define RIGHT	 	3
#define NORTH		0
#define EAST		1
#define SOUTH		2
#define WEST		3
//redefine me

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
													//MLX
	void				*mlx_con;
	void				*mlx_win;
	t_img				mlx_img;
													//Player
	double				pos_x;
	double				pos_y;
	double				angle;
	double				dir_x;
	double				dir_y;
													//Plane
	double				pln_x;
	double				pln_y;
													//Colours / Textures
	int					top_colour;
	int					btm_colour;
	unsigned int		*texture_buffer[NUM_TXT];
	void				*texture_images[NUM_TXT];
	char				**map;
													//Ray
	double				horizontal_pixel;
	double				camera_angle_ratio;
	double				current_ray_x_component;
	double				current_ray_y_component;
	double				x_intercept_unit_distance;
	double				y_intercept_unit_distance;
	int					current_cell_x;
	int					current_cell_y;
	int					p_n_x_step;
	int					p_n_y_step;
	double				x_dist_traversed;
	double				y_dist_traversed;
	int					wall_type;
	float				wall_dist;
	int					wall_height;
	int					draw_start;
	int					draw_end;
	double				wall_impact;
	int					current_y_pixel;

}	t_parsed_data;

//  ┌──────────────────────────────────────────────────────────────────────────┐
//  │							 	FUNCTIONS								   │
//  └──────────────────────────────────────────────────────────────────────────┘

int				close_handler(t_parsed_data *global);
void			render(t_parsed_data *global);
void			events_init(t_parsed_data *global);
t_parsed_data	*parsing_temp(void);
