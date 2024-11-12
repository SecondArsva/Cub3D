/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmatos-d <bmatos-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 22:08:17 by davidga2          #+#    #+#             */
/*   Updated: 2024/11/01 01:08:07 by bmatos-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libs/libft/libft.h"
# include <stdbool.h>

# define ERR_CHAR_RGB "invalid char in RGB values, use only numbers and comas"

typedef enum	e_value
{
	RED,
	GREEN,
	BLUE,
}				t_value;

typedef enum	e_type
{
	NO,
	SO,
	EA,
	WE,
	F,
	C,
}				t_type;

typedef enum	e_angle
{
	UNKNOWN,
	NORTH,
	SOUTH,
	EAST,
	WEST,
}				t_angle;

typedef struct	s_data
{
	int		i;
	int		j;
	char	*arg_path;
	int		cub_fd;
	bool	map_finded;
	bool	player_finded;
	char	*n_img_path;
	char	*s_img_path;
	char	*e_img_path;
	char	*w_img_path;
	int		n_fd;
	int		s_fd;
	int		e_fd;
	int		w_fd;
	bool	f_finded;
	int		f_red;
	int		f_green;
	int		f_blue;
	bool	c_finded;
	int		c_red;
	int		c_green;
	int		c_blue;
	char	**map;
	float	player_pos_x;
	float	player_pos_y;
	t_angle	player_angle; // n, s, e, w
}				t_data;

typedef struct	s_keyval
{
	char *key;
	char *val;
}				t_keyval;

//		### --- PARSER --- ###
void	incorrect_args(t_data **data, int argc);
void	parser(char *arg, t_data *data);
void	init_data(t_data *data);
void	init_data_bools(t_data *data);

//		### --- CUB FILE PRELIMINARY--- ###
void	check_arg_len(char *arg, t_data *data);
void	check_file_extension(t_data *data);
void	check_file_existence(t_data *data);

//		### --- CUB FILE SCRAPING --- ###
void	get_cub_content(t_data *data);
void	proccess_line(char *line, t_data *data);
void	manage_parameter(t_data *data, char *line, int i);

//		### --- GET TEXTURE --- ###
void	find_path(t_data *data, char *line, int i, t_type opcode);
char	*build_relative_path(t_data *data, char *path, char *line);
void	storage_texture_path(t_data *data, char *relative_path, t_type opcode, char *line);

//		### --- GET TEXTURE UTILS --- ###
char	*get_head_path(t_data *data);
void	check_xpm_extension(char *relative_path, t_data *data, char *line);
void	open_xpm(t_data *data, char *relative_path, t_type opcode, char *line);
void	check_texture_duplicity(t_data *data, t_type opcode, int fd, char *line);

//		### --- GET RGB & MAP--- ###
void	get_rgb(t_data *data, char *line, int i, t_type opcode);
void	check_rgb_duplicity(t_data *data, char *line, t_type opcode);
void	get_value(t_data *data, char *line, t_type opcode, t_value value);
void	storage_value(t_data *data, int num, t_type opcode, t_value value);
void	manage_map(t_data *data, char *line);

//		### --- CHECK PARSED CONTENT--- ###
void	check_parsed_content(t_data *data);

//		### --- CHECK PARSED MAP --- ###
void	check_map(t_data *data);
void	map_chars(t_data *data);
int		is_valid_map_char(char c);
void	map_floor(t_data *data);
void	map_player(t_data *data);

//		### --- FAILURE --- ###
void	wipe(t_data *data, char *str);
void	free_data(t_data *data);
void	err_exit(char *str);

#endif
