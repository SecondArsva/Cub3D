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

/*******************************************************
	-TO DO-
	[v] Open File
	[x] Get lines in a list
	[x] Parse content
		[x] Open textures path and get FDs
		[x] RGB values of Floor and Ceiling
		[x] Extern Map
	[x] Check Map
		[x] Get player axis
		[x] Get Angle                                                                                                           
*******************************************************/

void free_data(t_data *data)
{
	if (data->arg_path)
		free(data->arg_path);
	if (data->cub_fd)
		close(data->cub_fd);
	if (data->n_img_path)
		free(data->n_img_path);
	if (data->s_img_path)
		free(data->s_img_path);
	if (data->e_img_path)
		free(data->e_img_path);
	if (data->w_img_path)
		free(data->w_img_path);
	if (data->n_fd)
		close(data->n_fd);
	if (data->s_fd)
		close(data->s_fd);
	if (data->e_fd)
		close(data->e_fd);
	if (data->w_fd)
		close(data->w_fd);
	if (data->map)
		ft_free_matrix(data->map);
	free(data);
}

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
	data->map_finded = 0;
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

char *get_head_path(t_data *data)
{
	int	i;
	char *head;

	i = 0;
	while (data->arg_path[i])
		i++;
	i--;
	while (data->arg_path[i] && data->arg_path[i] != '/')
		i--;
	head = ft_substr(data->arg_path, 0, i + 1);
	printf("head: %s\n", head);
	return (head);
}

void check_xpm_extension(char *relative_path, t_data *data)
{
	int	i;

	i = 0;
	while (relative_path[i])
		i++;
	i -= strlen(".xpm");
	printf("%i\n", i);
	if (!ft_strncmp(&relative_path[i], ".xpm", strlen(".xpm") + 1))
		return ;
	free(relative_path);
	free_data(data);
	err_exit("invalid image extension, the texture must be an .xpm");
}

void	open_xpm(t_data *data, char *relative_path, t_type opcode)
{
	int	fd;

	fd = open(relative_path, O_RDONLY);
	if (fd == -1)
	{
		ft_printf_error("cub3D: error: %s", relative_path);
		ft_printf_error(" texture dont exists\n");
		free_data(data);
		exit(1);
	}
	if (opcode == NO)
		data->n_fd = fd;
	else if (opcode == SO)
		data->s_fd = fd;
	else if (opcode == EA)
		data->e_fd = fd;
	else if (opcode == WE)
		data->w_fd = fd;
	printf("xpm_fd: %i\n", fd);
}

void	storage_texture_path(t_data *data, char *relative_path, t_type opcode)
{
	check_xpm_extension(relative_path, data);
	if (opcode == NO)
		data->n_img_path = relative_path;
	else if (opcode == SO)
		data->s_img_path = relative_path;
	else if (opcode == EA)
		data->e_img_path = relative_path;
	else if (opcode == WE)
		data->w_img_path = relative_path;
	open_xpm(data, relative_path, opcode);
}

char	*build_relative_path(t_data *data, char *path)
{
	char	*head_path;
	char	*relative_path;

	head_path = get_head_path(data);
	if (!head_path)
	{
		free(path);
		free_data(data);
		exit(1);
	}
	relative_path = ft_strjoin(head_path, path);
	if (!relative_path)
	{
		free(head_path);
		free(path);
		free_data(data);
		exit(1);
	}
	printf("relative_path: '%s'\n", relative_path);
	free(path);
	free(head_path);
	return (relative_path);
}

void	find_path(t_data *data, char *line, int i, t_type opcode)
{
	int	j;
	char *path;

	path = NULL;
	j = 0;
	while (line[i] && line[i] == ' ')
		i++;
	j = i;
	while (line[j] && (line[j] != ' ' && line[j] != '\n'))
		j++;
	path = ft_substr(line, i, j - i);
	if (!path)
		return (free_data(data), exit(1));
	printf("path: %s", path);
	storage_texture_path(data, build_relative_path(data, path), opcode);
}

/*
	El path de la textura es relativo a la ubicación del archivo .cub,
	el que tiene el mapa, y no desde la ruta en la que se ejecuta el 
	programa cub3D, por lo que he de hacer un join de parte de la ruta 
	del mapa recibido a las texturas que me encuentre.

	
	Ejemplo A:
		./cub3D maps/map.cub

		map.cub:
			NO ../textures/texture.xpm
	
		new_texture_path to open: maps/../textures/texture.xpm

	Ejemplo B:
		./cub3D map.cub

		map.cub:
			NO texture.xpm

		new_texture_path to open: texture.xpm

	El "i + 2" en manage_texture es para saltarse el identificador y pasar
	a los espacios que preceden al supuesto contenido especificado,
	a la ruta de la textura.
	De igual forma tendré que hacer un "i + 1" en manage_rgb.
*/
void	manage_texture(t_data *data, char *line, int i)
{
	printf("Manage texture\n");
	if (!ft_strncmp(&line[i], "NO ", 3))
		find_path(data, line, i + 2, NO);
	else if (!ft_strncmp(&line[i], "SO ", 3))
		find_path(data, line, i + 2, SO);
	else if (!ft_strncmp(&line[i], "EA ", 3))
		find_path(data, line, i + 2, EA);
	else if (!ft_strncmp(&line[i], "WE ", 3))
		find_path(data, line, i + 2, WE);
}

void	proccess_line(char *line, t_data *data)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
			i++;
	if ((!ft_strncmp(&line[i], "NO ", 3) || !ft_strncmp(&line[i], "SO ", 3)
		|| !ft_strncmp(&line[i], "EA ", 3) || !ft_strncmp(&line[i], "WE ", 3))
		&& !data->map_finded)
		manage_texture(data, line, i);
	else if ((!ft_strncmp(&line[i], "F ", 2) || !ft_strncmp(&line[i], "C ", 2))
		&& !data->map_finded)
		printf("Manage RGB\n");
	else if (!ft_strncmp(&line[i], "\n", 1))
		printf("Empty line\n");
	else if (!ft_strncmp(&line[i], "1", 1))
		printf("Map\n");
	else
		printf("Vete tu a saber que coño es esto\n");
}

// Me salto los espacios y evalúo según lo que me encuentre inmediatamente.
// Si me encuentro un 1 quiere decir que esa línea forma parte del mapa
// jugable. A partir de él encapsulo todo el contenido que le siga como parte
// del mapa. Luego lo analizo y ya veo los posibles errores que pueda haber.
void get_cub_content(t_data *data)
{
	char	*line;

	line = NULL;
	while ("B.J. Blazkowicz")
	{
		line = get_next_line(data->cub_fd);
		if (line == NULL)
			exit (1);// clear list, close fd, free arg_path, data and exit;
		printf("%s", line);
		proccess_line(line, data);
		free(line);
	}
}

// Con esta función verificaré que todo lo que le debo pasar
// al ray-tracer esté y sino termino el programa.
void check_content(t_data *data)
{
	(void)data;
}

void parser(char *arg, t_data *data)
{
	init_data(data);

	check_arg_len(arg, data);
	check_file_extension(data);
	check_file_existence(data);

	get_cub_content(data);
	check_content(data);
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