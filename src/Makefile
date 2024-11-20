# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bmatos-d <bmatos-d@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/20 12:57:01 by bmatos-d          #+#    #+#              #
#    Updated: 2024/11/20 16:50:50 by bmatos-d         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

COMPILE = gcc
CFLAGS = -Werror -Wextra -Wall -g3 -fPIE
LIBFT_DIR = ../libs/libft/
LIBFT = $(LIBFT_DIR)libft.a
LINKS = -L./simulator/MLX-LNX -lmlx_Linux -lX11 -lXext -lm

MLX_PATH = ./simulator/MLX-LNX/
MLX = $(MLX_PATH)libmlx_Linux.a

PARS_PATH = ./parser
PARS_SRCS =	main.c					\
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

EXEC_PATH = ./simulator
EXEC_SRCS = simulation.c	\
			events.c		\
			render1.c		\
			render2.c		\
			init.c

SOURCES  := $(addprefix $(PARS_PATH)/,$(PARS_SRCS)) \
			$(addprefix $(EXEC_PATH)/,$(EXEC_SRCS))

OBJECTS = $(SOURCES:.c=.o)


all: $(MLX) $(LIBFT) $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(MLX):
	cd $(MLX_PATH) && make

$(NAME): $(OBJECTS)
	$(COMPILE) $(LIBFT) -pie $(LINKS) $(CFLAGS) $(OBJECTS) -o $(NAME)

clean:
	$(RM) $(OBJECTS)
	make clean -C $(LIBFT_DIR)
	make clean -C $(MLX_PATH)

fclean: clean
	$(RM) $(NAME)
	make fclean -C $(LIBFT_DIR)
	make clean -C $(MLX_PATH)

re: fclean all