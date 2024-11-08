/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_file_preliminary.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davidga2 <davidga2@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-08 06:02:21 by davidga2          #+#    #+#             */
/*   Updated: 2024-11-08 06:02:21 by davidga2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

// - Comprobar que sea ".cub"
//		Medir leng del string y retroceder 4 si es >4,
//		sino, error.
//		Comprobar que termina en ".cub"
// - Comprobar la validez del archivo recibido
// 		Hacer open y ver que existe un fd válido,
//		esto permite ver la existencia del archívo.
//		Si el open falla, error.
//
//		map.cub - ./textures/map.cub
//		"map.cub" - "        map.cub" "../../textures/map.cub     "
void check_arg_len(char *arg, t_data *data)
{
	data->i = 0;
	data->j = 0;

	data->arg_path = safe_strtrim(arg, " ");
	ft_strlen(data->arg_path);
	printf("arg len: %li\n", ft_strlen(data->arg_path));
	if (ft_strchr(data->arg_path, '/'))
	{
		printf("Hay barra\n");
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

void check_file_extension(t_data *data)
{
	printf("%i\n", data->i);
	printf("%i\n", data->j);
	printf("%s\n", data->arg_path);

	if (!data->i)
	{
		while (data->arg_path[data->i])
			data->i++;
	}
	data->i -= strlen(".cub");
	printf("%i\n", data->i);
	if (!ft_strncmp(&data->arg_path[data->i], ".cub", strlen(".cub") + 1))
		return ;
	free(data->arg_path);
	free(data);
	err_exit("invalid file extension");
}

void check_file_existence(t_data *data)
{
	data->cub_fd = open(data->arg_path, O_RDONLY);
	printf("cub_fd: %i\n", data->cub_fd);
	if (data->cub_fd == -1)
	{
		free(data->arg_path);
		free(data);
		err_exit("introduced map dont exist");
	}
}
