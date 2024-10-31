/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davidga2 <davidga2@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-30 22:08:17 by davidga2          #+#    #+#             */
/*   Updated: 2024-10-30 22:08:17 by davidga2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../../libs/libft/libft.h"

typedef struct	s_cub3d
{
	char	*n_img_path;
	char	*s_img_path;
	char	*e_img_path;
	char	*w_img_path;
	int		f_red;
	int		f_gre;
	int		f_blu;
	int		c_red;
	int		c_gre;
	int		c_blu;
	char	**map;
}				t_cub3d;

#endif
