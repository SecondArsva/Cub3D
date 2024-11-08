/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parsed_content.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davidga2 <davidga2@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-08 05:43:57 by davidga2          #+#    #+#             */
/*   Updated: 2024-11-08 05:43:57 by davidga2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	check_parsed_content(t_data *data)
{
	if (data->n_fd == -1 || data->s_fd == -1
		|| data->e_fd == -1 || data->w_fd == -1)
		wipe(data, "you forgot to declare a texture");
	else if (data->f_red == -1 || data->f_green == -1 || data->f_blue == -1
		|| data->c_red == -1 || data->c_green == -1 || data->c_blue == -1)
		wipe(data, "you forgot to declare a RGB value");
	else if (!data->map_finded)
		wipe(data, "no map finded in the cub file");
	check_map(data);
}
