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

// 
void incorrect_args(int argc)
{
	if (argc < 2)
		ft_printf_error("You must introduce a map as an argument.\n");
	else if (argc > 2)
		ft_printf_error("You cant introduce more arguments than a map.\n");
}

// inicialización de data para un uso correcto de la estructura.
void init_data(t_data **data)
{
	(*data)->cub_fd = 0;
	(*data)->n_img_path = NULL;
	(*data)->s_img_path = NULL;
	(*data)->e_img_path = NULL;
	(*data)->w_img_path = NULL;
	(*data)->n_fd = 0;
	(*data)->s_fd = 0;
	(*data)->e_fd = 0;
	(*data)->w_fd = 0;
	(*data)->f_red = 0;
	(*data)->f_gre = 0;
	(*data)->f_blu = 0;
	(*data)->c_red = 0;
	(*data)->c_gre = 0;
	(*data)->c_blu = 0;
	(*data)->map = NULL;
	(*data)->player_pos_x = 0.0;
	(*data)->player_pos_y = 0.0;
	(*data)->player_angle = UNKNOWN;
}

// - Comprobar que sea ".cub"
//		Medir leng del string y retroceder 4 si es >4,
//		sino, error.
//		Comprobar que termina en ".cub"
// - Comprobar la validez del archivo recibido
// 		Hacer open y ver que existe un fd válido,
//		esto permite ver la existencia del archívo.
//		Si el open falla, error.
void check_arg()


void parser(char *arg, t_data **data)
{
	init_data(data);
	check_arg(arg, data);
}

int main(int argc, char **argv)
{
	t_data *data;

	data = safe_malloc(sizeof(t_data));
	if (argc != 2)
		return (incorrect_args(argc), 1);	
	parser(argv[1], &data);
	// print_data(data);
	return (0);
}