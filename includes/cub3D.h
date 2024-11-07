/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmatos-d <bmatos-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 22:08:17 by davidga2          #+#    #+#             */
/*   Updated: 2024/11/01 01:08:07 by bmatos-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libs/libft/libft.h"
# include <stdbool.h>

# define ERR_CHAR_RGB "invalid char in RGB values, use only numbers and comas"

typedef enum	e_value
{
	RED,
	GREEN,
	BLUE,
}				t_value;

typedef enum	e_type
{
	NO,
	SO,
	EA,
	WE,
	F,
	C,
}				t_type;

typedef enum	e_angle
{
	UNKNOWN,
	NORTH,
	SOUTH,
	EAST,
	WEST,
}				t_angle;

typedef struct	s_data
{
	int		i;
	int		j;
	char	*arg_path;
	int		cub_fd;
	bool	map_finded;
	bool	player_finded;
	char	*n_img_path;
	char	*s_img_path;
	char	*e_img_path;
	char	*w_img_path;
	int		n_fd;
	int		s_fd;
	int		e_fd;
	int		w_fd;
	bool	f_finded;
	int		f_red;
	int		f_green;
	int		f_blue;
	bool	c_finded;
	int		c_red;
	int		c_green;
	int		c_blue;
	char	**map;
	float	player_pos_x;
	float	player_pos_y;
	t_angle	player_angle; // n, s, e, w
}				t_data;

typedef struct	s_keyval
{
	char *key;
	char *val;
}				t_keyval;


#endif
