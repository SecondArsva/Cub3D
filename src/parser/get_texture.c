/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davidga2 <davidga2@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-08 05:57:56 by davidga2          #+#    #+#             */
/*   Updated: 2024-11-08 05:57:56 by davidga2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

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
	relative_path = ft_strjoin(head_path, path);
	if (!relative_path)
	{
		free(head_path);
		free(path);
		wipe(data, "memory allocation failed");
	}
	free(path);
	free(head_path);
	return (relative_path);
}

void	find_path(t_data *data, char *line, int i, t_type opcode)
{
	int		j;
	char	*path;

	path = NULL;
	j = 0;
	while (line[i] && line[i] == ' ')
		i++;
	j = i;
	while (line[j] && (line[j] != ' ' && line[j] != '\n'))
		j++;
	path = ft_substr(line, i, j - i);
	free(line);
	if (!path)
		wipe(data, "memory allocation failed");
	storage_texture_path(data, build_relative_path(data, path), opcode);
}
