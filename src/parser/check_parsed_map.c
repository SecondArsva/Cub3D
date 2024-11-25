/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parsed_map.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmatos-d <bmatos-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 04:26:36 by davidga2          #+#    #+#             */
/*   Updated: 2024/11/25 18:26:38 by bmatos-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_parser.h"

void	map_floor(t_data *data)
{
	int	i;
	int	j;

	i = data->i;
	j = data->j;
	if (!data->map[i - 1][j] || data->map[i - 1][j] == ' '
		|| !data->map[i + 1][j] || data->map[i + 1][j] == ' '
		|| !data->map[i][j - 1] || data->map[i][j - 1] == ' '
		|| !data->map[i][j + 1] || data->map[i][j + 1] == ' ')
		wipe(data, "open map, all floor tiles must be sorrounded by walls");
}

void	map_player(t_data *data)
{
	int	i;
	int	j;

	if (data->player_finded)
		wipe(data, "multiple player positions finded");
	i = data->i;
	j = data->j;
	data->player_finded = true;
	if (!data->map[i - 1][j] || data->map[i - 1][j] == ' '
		|| !data->map[i + 1][j] || data->map[i + 1][j] == ' '
		|| !data->map[i][j - 1] || data->map[i][j - 1] == ' '
		|| !data->map[i][j + 1] || data->map[i][j + 1] == ' ')
		wipe(data, "open map, player tile must be sorrounded by walls");
	data->player_pos_y = data->i + 0.5;
	data->player_pos_x = data->j + 0.5;
	if (data->map[i][j] == 'N')
		data->player_angle = NORTH;
	else if (data->map[i][j] == 'S')
		data->player_angle = SOUTH;
	else if (data->map[i][j] == 'E')
		data->player_angle = EAST;
	else if (data->map[i][j] == 'W')
		data->player_angle = WEST;
}

int	is_valid_map_char(char c)
{
	if (c == '1' || c == '0' || c == ' '
		|| c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

void	map_chars(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (data->map[i])
	{
		while (data->map[i][j])
		{
			if (!is_valid_map_char(data->map[i][j]))
				wipe(data, "invalid map, use only 0, 1, N, S, E, W or spaces");
			j++;
		}
		j = 0;
		i++;
	}
}

void	check_map(t_data *data)
{
	data->i = 0;
	data->j = 0;
	map_chars(data);
	while (data->map[data->i])
	{
		while (data->map[data->i][data->j])
		{
			if (data->map[data->i][data->j] == '0')
				map_floor(data);
			else if (data->map[data->i][data->j] == 'N'
				|| data->map[data->i][data->j] == 'S'
				|| data->map[data->i][data->j] == 'E'
				|| data->map[data->i][data->j] == 'W')
				map_player(data);
			data->j++;
		}
		data->i++;
		data->j = 0;
	}
	if (!data->player_finded)
		wipe(data, "player position not declared, use N, S, E or W");
}
