/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_file_preliminary.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmatos-d <bmatos-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 06:02:21 by davidga2          #+#    #+#             */
/*   Updated: 2024/11/20 16:53:15 by bmatos-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Parsing.h"

void	check_arg_len(char *arg, t_data *data)
{
	data->i = 0;
	data->j = 0;
	data->arg_path = safe_strtrim(arg, " ");
	ft_strlen(data->arg_path);
	if (ft_strchr(data->arg_path, '/'))
	{
		while (data->arg_path[data->i])
			data->i++;
		data->j = data->i;
		while (data->j > 0 && data->arg_path[data->j] != '/')
			data->j--;
		if ((data->i - 1 - data->j) < 4)
		{
			free(data->arg_path);
			free(data);
			err_exit("file name its too short to be a '.cub'");
		}
	}
	else if (ft_strlen(data->arg_path) < 4)
		err_exit("file name its too short to be a '.cub'");
}

void	check_file_extension(t_data *data)
{
	if (!data->i)
	{
		while (data->arg_path[data->i])
			data->i++;
	}
	data->i -= strlen(".cub");
	if (!ft_strncmp(&data->arg_path[data->i], ".cub", strlen(".cub") + 1))
		return ;
	free(data->arg_path);
	free(data);
	err_exit("invalid file extension, the map must be a .cub");
}

void	check_file_existence(t_data *data)
{
	data->cub_fd = open(data->arg_path, O_RDONLY);
	if (data->cub_fd == -1)
	{
		free(data->arg_path);
		free(data);
		err_exit("introduced map dont exist");
	}
}
