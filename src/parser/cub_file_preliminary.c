/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_file_preliminary.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davidga2 <davidga2@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-23 04:26:56 by davidga2          #+#    #+#             */
/*   Updated: 2024-11-23 04:26:56 by davidga2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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
