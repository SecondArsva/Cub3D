/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davidga2 <davidga2@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-30 22:27:39 by davidga2          #+#    #+#             */
/*   Updated: 2024-10-30 22:27:39 by davidga2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void err_exit(char *str)
{
	ft_printf_error("cub3D: ");
	ft_printf_error("error: ");
	ft_printf_error("%s", str);
	ft_printf_error("\n");
	exit(1);
}
// 
void incorrect_args(int argc)
{
	if (argc < 2)
		err_exit("you must introduce a map as an argument");
	else if (argc > 2)
		err_exit("you cant introduce more arguments than a map");
}

// inicialización de data para un uso correcto de la estructura.
void init_data(t_data *data)
{
	data->i = 0;
	data->j = 0;
	data->arg_path = NULL;
	data->cub_fd = 0;
	data->n_img_path = NULL;
	data->s_img_path = NULL;
	data->e_img_path = NULL;
	data->w_img_path = NULL;
	data->n_fd = 0;
	data->s_fd = 0;
	data->e_fd = 0;
	data->w_fd = 0;
	data->f_red = -1;
	data->f_gre = -1;
	data->f_blu = -1;
	data->c_red = -1;
	data->c_gre = -1;
	data->c_blu = -1;
	data->map = NULL;
	data->player_pos_x = 0.0;
	data->player_pos_y = 0.0;
	data->player_angle = UNKNOWN;
}

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
	err_exit("invalid file exension");
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

void parser(char *arg, t_data *data)
{
	init_data(data);
	check_arg_len(arg, data);
	check_file_extension(data);
	check_file_existence(data);
}

int main(int argc, char **argv)
{
	t_data *data;

	data = safe_malloc(sizeof(t_data));
	if (argc != 2)
		incorrect_args(argc);
	printf("%s\n", argv[1]);
	parser(argv[1], data);
	// print_data(data);
	return (0);
}