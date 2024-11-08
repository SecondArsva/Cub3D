/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_rgb_and_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davidga2 <davidga2@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-08 05:46:36 by davidga2          #+#    #+#             */
/*   Updated: 2024-11-08 05:46:36 by davidga2         ###   ########.fr       */
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

void	storage_value(t_data *data, int num, t_type opcode, t_value value)
{
	if (num < 0 || num > 255)
		wipe(data, "an introduced RGB value its out range. Range: 0 to 255");
	if (opcode == F && value == RED)
		data->f_red = num;
	else if (opcode == F && value == GREEN)
		data->f_green = num;
	else if (opcode == F && value == BLUE)
		data->f_blue = num;
	else if (opcode == C && value == RED)
		data->c_red = num;
	else if (opcode == C && value == GREEN)
		data->c_green = num;
	else if (opcode == C && value == BLUE)
		data->c_blue = num;
}

void	get_value(t_data *data, char *line, t_type opcode, t_value value)
{
	char	*val;
	int		num;

	val = NULL;
	while (line[data->i] && line[data->i] == ',')
		data->i++;
	data->j = data->i;
	while (line[data->j] && line[data->j] != ',' && line[data->j] != '\n')
	{
		if (line[data->j] < '0' || line[data->j] > '9')
			wipe(data, ERR_CHAR_RGB);
		data->j++;
	}
	val = ft_substr(line, data->i, data->j - data->i);
	if (!val || !ft_strncmp(val, "\0", 1))
		wipe(data, "you forgot to declare a RGB value");
	data->i = data->j + 1;
	num = atoi(val);
	free(val);
	storage_value(data, num, opcode, value);
}

void	check_rgb_duplicity(t_data *data, char *line, t_type opcode)
{
	if ((opcode == F
			&& (data->f_red != -1 || data->f_green != -1
				|| data->f_blue != -1))
		|| (opcode == C
			&& (data->c_red != -1 || data->c_green != -1
				|| data->c_blue != -1)))
	{
		free(line);
		free_data(data);
		err_exit("duplicate RGB parameter.");
	}
}

void	get_rgb(t_data *data, char *line, int i, t_type opcode)
{
	while (line[i] && line[i] == ' ')
		i++;
	data->i = i;
	check_rgb_duplicity(data, line, opcode);
	get_value(data, line, opcode, RED);
	get_value(data, line, opcode, GREEN);
	get_value(data, line, opcode, BLUE);
}
