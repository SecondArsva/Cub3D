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
	char	*n_img_path;
	char	*s_img_path;
	char	*e_img_path;
	char	*w_img_path;
	int		n_fd;
	int		s_fd;
	int		e_fd;
	int		w_fd;
	int		f_red;
	int		f_gre;
	int		f_blu;
	int		c_red;
	int		c_gre;
	int		c_blu;
	char	**map;
	int		player_pos_x;
	int		player_pos_y;
	char	player_angle; // n, s, e, w
}				t_cub3d;

#endif
