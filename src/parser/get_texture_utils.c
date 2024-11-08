/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_texture_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davidga2 <davidga2@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-08 05:54:30 by davidga2          #+#    #+#             */
/*   Updated: 2024-11-08 05:54:30 by davidga2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

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
}

void	check_xpm_extension(char *relative_path, t_data *data)
{
	int	i;

	i = 0;
	while (relative_path[i])
		i++;
	i -= strlen(".xpm");
	if (!ft_strncmp(&relative_path[i], ".xpm", strlen(".xpm") + 1))
		return ;
	free(relative_path);
	free_data(data);
	err_exit("invalid image extension, the texture must be an .xpm");
}

char	*get_head_path(t_data *data)
{
	int		i;
	char	*head;

	i = 0;
	while (data->arg_path[i])
		i++;
	i--;
	while (data->arg_path[i] && data->arg_path[i] != '/')
		i--;
	head = ft_substr(data->arg_path, 0, i + 1);
	return (head);
}
