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
	if (data->n_fd != -1)
		close(data->n_fd);
	if (data->s_fd != -1)
		close(data->s_fd);
	if (data->e_fd != -1)
		close(data->e_fd);
	if (data->w_fd != -1)
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

void	incorrect_args(int argc)
{
	if (argc < 2)
		err_exit("you must introduce a map as an argument");
	else if (argc > 2)
		err_exit("you cant introduce more arguments than a single map");
}

void	init_data_bools(t_data *data)
{
	data->map_finded = false;
	data->player_finded = false;
	data->f_finded = false;
	data->c_finded = false;
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
	data->n_fd = -1;
	data->s_fd = -1;
	data->e_fd = -1;
	data->w_fd = -1;
	data->f_red = -1;
	data->f_green = -1;
	data->f_blue = -1;
	data->c_red = -1;
	data->c_green = -1;
	data->c_blue = -1;
	data->map = NULL;
	data->player_pos_x = 0.0;
	data->player_pos_y = 0.0;
	data->player_angle = UNKNOWN;
	init_data_bools(data);
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

void	check_texture_duplicity(t_data *data, t_type opcode, int fd)
{
	if ((opcode == NO && data->n_fd != -1)
		|| (opcode == SO && data->s_fd != -1)
		|| (opcode == EA && data->e_fd != -1)
		|| (opcode == WE && data->w_fd != -1)
		|| (opcode == F && data->f_finded)
		|| (opcode == C && data->c_finded))
	{
		close(fd);
		free_data(data);
		err_exit("duplicate texture parameter");
	}
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
	check_texture_duplicity(data, opcode, fd);
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

void	storage_value(t_data *data, int num, t_type opcode, t_value value)
{
	if (num < 0 || num > 255)
	{
		free_data(data);
		err_exit("an introduced RGB value its out range. Range: 0 to 255");
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

void	wipe(t_data *data, char *str)
{
	free_data(data);
	err_exit(str);
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
		printf("line[j]: %c		", line[data->j]);
		if (line[data->j] < '0' || line[data->j] > '9')
			wipe(data, ERR_CHAR_RGB);
		data->j++;
	}
	val = ft_substr(line, data->i, data->j - data->i);
	if (!val || !ft_strncmp(val, "\0", 1))
		wipe(data, "you forgot to declare a RGB value");
	data->i = data->j + 1;
	printf("num: %s\n", val);
	num = atoi(val);
	printf("atoi: %i\n", num);
	free(val);
	storage_value(data, num, opcode, value);
}

void	check_rgb_duplicity(t_data *data, char *line, t_type opcode)
{
	if ((opcode == F
		&& (data->f_red != -1|| data->f_green != -1 || data->f_blue != -1))
		|| (opcode == C
		&& (data->c_red != -1 || data->c_green != -1 || data->c_blue != -1)))
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
void	manage_parameter(t_data *data, char *line, int i)
{
	printf("Manage parameter\n");
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

void	manage_map(t_data *data, char *line)
{
	char	*no_break;
	int		i;

	no_break = NULL;
	i = 0;
	printf("Map\n");
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

void	proccess_line(char *line, t_data *data)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
			i++;
	if ((!ft_strncmp(&line[i], "NO ", 3) || !ft_strncmp(&line[i], "SO ", 3)
		|| !ft_strncmp(&line[i], "EA ", 3) || !ft_strncmp(&line[i], "WE ", 3)
		|| !ft_strncmp(&line[i], "F ", 2) || !ft_strncmp(&line[i], "C ", 2))
		&& !data->map_finded)
		manage_parameter(data, line, i);
	else if (!ft_strncmp(&line[i], "\n", 1) && !data->map_finded)
		printf("Empty line\n");
	else if (!ft_strncmp(&line[i], "1", 1))
		manage_map(data, line);
	else
	{
		free(line);
		wipe(data, "invalid parameter or empty line inside/after map section");
	}
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
			break ; // revisa esto porque en caso de error no se libera una mierda.
		printf("%s", line);
		proccess_line(line, data);
		free(line);
	}
}

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
	int i;
	int j;
	
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
			// meter un check 10NSEW\0
			printf("----: '%c'\n", data->map[data->i][data->j]);
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

// Con esta función verificaré que todo lo que le debo pasar
// al ray-tracer esté y sino termino el programa.
void check_parsed_content(t_data *data)
{
	if (data->n_fd == -1 || data->s_fd == -1
		|| data->e_fd == -1 || data->w_fd == -1)
		wipe(data, "you forgot to declare a texture");
	else if (data->f_red == -1 || data->f_green == -1 || data->f_blue == -1
		|| data->c_red == -1 || data->c_green == -1 || data->c_blue == -1)
		wipe(data, "you forgot to declare a RGB value");
	else if (!data->map_finded)
		wipe(data, "no map finded in the cub file");
	check_map(data);
}

void parser(char *arg, t_data *data)
{
	init_data(data);

	check_arg_len(arg, data);
	check_file_extension(data);
	check_file_existence(data);

	get_cub_content(data);
	check_parsed_content(data);
}

void	print_data(t_data *data)
{
	printf("\n----------------- DATA -----------------\n\n");
	printf("arg_path:		%s\n", data->arg_path);
	printf("cub_fd:			%i\n", data->cub_fd);
	printf("n_img_path:		%s\n", data->n_img_path);
	printf("s_img_path:		%s\n", data->s_img_path);
	printf("e_img_path:		%s\n", data->e_img_path);
	printf("w_img_path:		%s\n", data->w_img_path);
	printf("n_fd:			%i\n", data->n_fd);
	printf("s_fd:			%i\n", data->s_fd);
	printf("e_fd:			%i\n", data->e_fd);
	printf("w_fd:			%i\n", data->w_fd);
	printf("f_red:			%i\n", data->f_red);
	printf("f_green:		%i\n", data->f_green);
	printf("f_blue:			%i\n", data->f_blue);
	printf("c_red:			%i\n", data->c_red);
	printf("c_green:		%i\n", data->c_green);
	printf("c_blue:			%i\n", data->c_blue);
	ft_print_matrix(data->map, "map: ");
	printf("player_pos_x:	%f\n", data->player_pos_x);	
	printf("player_pos_y:	%f\n", data->player_pos_y);
	printf("player_angle:	%i\n", data->player_angle);
}

int main(int argc, char **argv)
{
	t_data *data;

	data = safe_malloc(sizeof(t_data));
	if (argc != 2)
		incorrect_args(argc);
	printf("%s\n", argv[1]);
	parser(argv[1], data);
	print_data(data);
	free_data(data);
	return (0);
}
