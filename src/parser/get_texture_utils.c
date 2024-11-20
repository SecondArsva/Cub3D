/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_texture_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmatos-d <bmatos-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 05:54:30 by davidga2          #+#    #+#             */
/*   Updated: 2024/11/20 16:53:29 by bmatos-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Parsing.h"

void	check_texture_duplicity(t_data *data, t_type opcode, char *line,
			char *relative_path)
{
	if ((opcode == NO && data->n_fd != -1)
		|| (opcode == SO && data->s_fd != -1)
		|| (opcode == EA && data->e_fd != -1)
		|| (opcode == WE && data->w_fd != -1)
		|| (opcode == F && data->f_finded)
		|| (opcode == C && data->c_finded))
	{
		free(line);
		free(relative_path);
		wipe(data, "duplicate texture parameter");
	}
}

void	open_xpm(t_data *data, char *relative_path, t_type opcode, char *line)
{
	int	fd;

	fd = open(relative_path, O_RDONLY);
	if (fd == -1)
	{
		free(line);
		wipe(data, "texture dont exists");
	}
	if (opcode == NO)
		data->n_fd = fd;
	else if (opcode == SO)
		data->s_fd = fd;
	else if (opcode == EA)
		data->e_fd = fd;
	else if (opcode == WE)
		data->w_fd = fd;
}

void	check_xpm_extension(char *relative_path, t_data *data, char *line)
{
	int	i;

	i = 0;
	while (relative_path[i])
		i++;
	i -= strlen(".xpm");
	if (!ft_strncmp(&relative_path[i], ".xpm", strlen(".xpm") + 1))
		return ;
	free(line);
	free(relative_path);
	wipe(data, "invalid image extension, the texture must be a .xpm");
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
