# ************************************************************************** #
#                                                                            #
#                                                        :::      ::::::::   #
#   Makefile                                           :+:      :+:    :+:   #
#                                                    +:+ +:+         +:+     #
#   By: davidga2 <davidga2@student.42madrid.com>   #+#  +:+       +#+        #
#                                                +#+#+#+#+#+   +#+           #
#   Created: 2024-11-23 03:28:17 by davidga2          #+#    #+#             #
#   Updated: 2024-11-23 03:28:17 by davidga2         ###   ########.fr       #
#                                                                            #
# ************************************************************************** #

NAME = cub3d

CC = cc

CFLAGS = -Werror -Wextra -Wall

LIBFT_DIR = libs/libft/

LIBFT = $(LIBFT_DIR)libft.a

MLX_DIR = libs/minilibx/

MLX = $(MLX_DIR)libmlx_Linux.a

LINKS = -L$(MLX_DIR) -lmlx_Linux -lX11 -lXext -lm

PARSE_DIR =		src/parser/

PARSE_FILES =	main.c					\
				parser.c				\
				cub_file_preliminary.c	\
				cub_file_scraping.c		\
				get_texture.c			\
				get_texture_utils.c		\
				get_rgb.c				\
				get_map.c				\
				check_parsed_content.c	\
				check_parsed_map.c		\
				failure.c

RAYCAST_DIR =	src/simulator/

RAYCAST_FILES =	events.c		\
				render1.c		\
				render2.c		\
				init.c

SOURCES  := $(addprefix $(PARSE_DIR),$(PARSE_FILES)) \
			$(addprefix $(RAYCAST_DIR),$(RAYCAST_FILES))

OBJECTS = $(SOURCES:.c=.o)

all: $(MLX) $(LIBFT) $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(MLX):
	make -C $(MLX_DIR)

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(NAME) $(LINKS) $(MLX) $(LIBFT)

clean:
	$(RM) $(OBJECTS)
	make clean -C $(LIBFT_DIR)
	make clean -C $(MLX_DIR)

fclean: clean
	$(RM) $(NAME)
	make fclean -C $(LIBFT_DIR)
	make clean -C $(MLX_DIR)

re: fclean all
