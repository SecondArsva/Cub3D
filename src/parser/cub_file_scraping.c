/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_file_scraping.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davidga2 <davidga2@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-08 05:59:42 by davidga2          #+#    #+#             */
/*   Updated: 2024-11-08 05:59:42 by davidga2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

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
void	get_cub_content(t_data *data)
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
