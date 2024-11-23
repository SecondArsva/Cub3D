/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_file_scraping.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davidga2 <davidga2@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-23 04:27:14 by davidga2          #+#    #+#             */
/*   Updated: 2024-11-23 04:27:14 by davidga2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	manage_parameter(t_data *data, char *line, int i)
{
	if (!ft_strncmp(&line[i], "NO ", 3))
		find_path(data, line, i + 2, NO);
	else if (!ft_strncmp(&line[i], "SO ", 3))
		find_path(data, line, i + 2, SO);
	else if (!ft_strncmp(&line[i], "EA ", 3))
		find_path(data, line, i + 2, EA);
	else if (!ft_strncmp(&line[i], "WE ", 3))
		find_path(data, line, i + 2, WE);
	else if (!ft_strncmp(&line[i], "F ", 2))
		get_rgb(data, line, i + 1, F);
	else if (!ft_strncmp(&line[i], "C ", 2))
		get_rgb(data, line, i + 1, C);
}

void	proccess_line(char *line, t_data *data)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if ((!ft_strncmp(&line[i], "NO ", 3)
			|| !ft_strncmp(&line[i], "SO ", 3)
			|| !ft_strncmp(&line[i], "EA ", 3)
			|| !ft_strncmp(&line[i], "WE ", 3)
			|| !ft_strncmp(&line[i], "F ", 2)
			|| !ft_strncmp(&line[i], "C ", 2))
		&& !data->map_finded)
		manage_parameter(data, line, i);
	else if (!ft_strncmp(&line[i], "\n", 1) && !data->map_finded)
		return ;
	else if (!ft_strncmp(&line[i], "1", 1))
		manage_map(data, line);
	else
	{
		free(line);
		wipe(data, "invalid parameter or empty line inside/after map section");
	}
}

void	get_cub_content(t_data *data)
{
	char	*line;

	line = NULL;
	while ("B.J. Blazkowicz")
	{
		line = get_next_line(data->cub_fd);
		data->line = line;
		if (line == NULL)
			break ;
		proccess_line(line, data);
		free(line);
	}
}
