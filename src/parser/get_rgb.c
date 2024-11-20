/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_rgb.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmatos-d <bmatos-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 08:28:39 by davidga2          #+#    #+#             */
/*   Updated: 2024/11/20 16:53:26 by bmatos-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Parsing.h"

void	storage_value(t_data *data, int num, t_type opcode, t_value value)
{
	if (num < 0 || num > 255)
	{
		free(data->line);
		wipe(data, "an introduced RGB value its out range. Range: 0 to 255");
	}
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

void	empty_value(t_data *data, char *val, char *line)
{
	if (!val || !ft_strncmp(val, "\0", 1))
	{
		if (val)
			free(val);
		free(line);
		wipe(data, "you forgot to declare a RGB value");
	}
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
		{
			free(line);
			wipe(data, ERR_CHAR_RGB);
		}
		data->j++;
	}
	val = ft_substr(line, data->i, data->j - data->i);
	empty_value(data, val, line);
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
		wipe(data, "duplicate RGB parameter");
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
