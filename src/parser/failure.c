/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   failure.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmatos-d <bmatos-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 05:41:25 by davidga2          #+#    #+#             */
/*   Updated: 2024/11/14 02:24:39 by bmatos-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	free_data(t_data *data)
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

void	err_exit(char *str)
{
	ft_printf_error("cub3D: ");
	ft_printf_error("error: ");
	ft_printf_error("%s", str);
	ft_printf_error("\n");
	exit(1);
}

void	wipe(t_data *data, char *str)
{
	char	*line;

	line = NULL;
	while ("B.J. Blazkowicz")
	{
		line = get_next_line(data->cub_fd);
		if (line == NULL)
			break ;
		free(line);
	}
	free_data(data);
	err_exit(str);
}
