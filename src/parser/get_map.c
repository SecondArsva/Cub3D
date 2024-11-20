/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmatos-d <bmatos-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 08:27:33 by davidga2          #+#    #+#             */
/*   Updated: 2024/11/20 16:53:22 by bmatos-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Parsing.h"

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
