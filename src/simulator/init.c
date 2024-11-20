/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmatos-d <bmatos-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 00:05:33 by bmatos-d          #+#    #+#             */
/*   Updated: 2024/11/20 12:49:59 by bmatos-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//  ┌──────────────────────────────────────────────────────────────────────────┐
//  │							 	MLX INIT								   │
//  └──────────────────────────────────────────────────────────────────────────┘
static void	window_init(t_parsed_data *global)
{
	global->mlx_con = mlx_init();
	if (global->mlx_con == NULL)
		return (free(global), exit(EXIT_FAILURE));
	global->mlx_win = mlx_new_window(global->mlx_con, WIN_WID, WIN_HEI, TITLE);
	if (global->mlx_win == NULL)
	{
		mlx_destroy_display(global->mlx_con);
		return (free(global->mlx_con), free(global), exit(EXIT_FAILURE));
	}
	global->mlx_img.img_ptr = mlx_new_image(global->mlx_con, WIN_WID, WIN_HEI);
	if (global->mlx_img.img_ptr == NULL)
	{
		mlx_destroy_window(global->mlx_con, global->mlx_win);
		mlx_destroy_display(global->mlx_con);
		return (free(global->mlx_con), free(global), exit(EXIT_FAILURE));
	}
	global->mlx_img.pixels_ptr = mlx_get_data_addr(global->mlx_img.img_ptr,
			&global->mlx_img.bpp, &global->mlx_img.line_len,
			&global->mlx_img.endian);
	events_init(global);
}

//  ┌──────────────────────────────────────────────────────────────────────────┐
//  │							    STRUCTINIT								   │
//  └──────────────────────────────────────────────────────────────────────────┘
int file_exists(const char *path) {
    return access(path, F_OK) != -1;
}

void load_texture(t_parsed_data *global, int direction,  char *texture)
{
	int img_height;
    if (!file_exists(texture))
	{
        fprintf(stderr, "Error: Texture file %s not found!\n", texture);
        return;
    }
	if (!global->mlx_con)
		printf("ERROR\n");
    global->texture_images[direction] = mlx_xpm_file_to_image(global->mlx_con, texture, &img_height, &img_height);

    if (!global->texture_images[direction]) {
        fprintf(stderr, "Error: Failed to load texture from file %s!\n", texture);
        return;
    }

    global->texture_buffer[direction] = (unsigned int *)mlx_get_data_addr(
        global->texture_images[direction], &img_height, &img_height, &img_height);
    if (!global->texture_buffer[direction]) {
        fprintf(stderr, "Error: Failed to get texture data for %s!\n", texture);
        return;
    }
}

static void	load_textures(t_parsed_data *global)
{
	load_texture(global, NORTH, "../../textures/amethyst_160x160.xpm");
	load_texture(global, EAST, "../../textures/end_stone_160x160.xpm");
	load_texture(global, SOUTH, "../../textures/grass_block_160x160.xpm");
	load_texture(global, WEST, "../../textures/warped_nylium_160x160.xpm");
}

t_parsed_data *parsing_temp()
{
	t_parsed_data *ret;
	// HAY QUE HACER LASS TEXTURAS NULAS AQUI
	ret = calloc(sizeof(t_parsed_data), 1);
	ret->top_colour = 11594476;
	ret->btm_colour = 7951674;
	char    **temp_map;
	temp_map = malloc(sizeof(char *) * 20);
	temp_map[0]  = strdup("                  1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111");
	temp_map[1]  = strdup("1111111111111111111111111111111111000000000000000000000000000000000000000000000000000000000000000000000000000000001");
	temp_map[2]  = strdup("1000000000000000000000000000000000000000010000000010000000010000000010000000010000000010000000010000000010000000011");
	temp_map[3]  = strdup("1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001");
	temp_map[4]  = strdup("1000000000000000001100000001100000001100000001100000001100000001100000001100000001100000001100000001100000001100001");
	temp_map[5]  = strdup("1000100001000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001");
	temp_map[6]  = strdup("1000000000000000111100000111100000111100000111100000111100000111100000111100000111100000111100000111100000111100001");
	temp_map[7]  = strdup("1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001");
	temp_map[8]  = strdup("1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001");
	temp_map[9]  = strdup("1000000111111111100000001100000001100000001100000001100000001100000001100000001100000001100000001100000001100000001");
	temp_map[10] = strdup("1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001");
	temp_map[11] = strdup("1000000000000000111100000111100000111100000111100000111100000111100000111100000111100000111100000111100000111100001");
	temp_map[12] = strdup("1000000110000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001");
	temp_map[13] = strdup("1000000000000000000100000000100000000100000000100000000100000000100000000100000000100000000100000000100000000100001");
	temp_map[14] = strdup("1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001");
	temp_map[15] = strdup("1000100000000001000000001000000001000000001000000001000000001000000001000000001000000001000000001000000001000000001");
	temp_map[16] = strdup("1000000001000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001");
	temp_map[17] = strdup("1000100000000000100000000100000000100000000100000000100000000100000000100000000100000000100000000100000000100000001");
	temp_map[18] = strdup("1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111");
	temp_map[19] = NULL;
	ret->map = temp_map;
	ret->angle = 1 * M_PI;
	ret->pos_y = 2.5;
	ret->pos_x = 2.5;
    window_init(ret);
    load_textures(ret);
	return(ret);
}