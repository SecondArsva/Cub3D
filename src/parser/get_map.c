/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davidga2 <davidga2@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-17 08:27:33 by davidga2          #+#    #+#             */
/*   Updated: 2024-11-17 08:27:33 by davidga2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	manage_map(t_data *data, char *line)
{
	char	*no_break;
	int		i;

	no_break = NULL;
	i = 0;
	data->map_finded = true;
	while (line[i] && line[i] != '\n')
		i++;
	no_break = ft_substr(line, 0, i);
	if (!no_break)
	{
		free(line);
		wipe(data, "substr alloc failed");
	}
	data->map = ft_sarradd(data->map, no_break);
	free(no_break);
}
