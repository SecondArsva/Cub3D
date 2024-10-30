NAME = cub3d
COMPILE = gcc
FLAGS = -Werror -Wextra -Wall -g3
LINKS = -LMLX-LNX -lmlx_Linux -lX11 -lXext -lm

# MLX Functions

MLX_PATH = ./MLX-LNX/libmlx_Linux.a

# OBJECTS
SRCS = Simulacion.c  
OBJECTS = $(SRCS:.c=.o)

all: $(MLX_PATH) $(NAME)

$(MLX_PATH):
	cd ./MLX-LNX && make 

$(NAME): $(OBJECTS)
	$(COMPILE) $(FLAGS) $(OBJECTS) $(LINKS) -o $(NAME)

%.o: %.c
	$(COMPILE) $(FLAGS) -c $< -o $@

clean:
	$(RM) $(OBJECTS) 

fclean: clean
	cd ./MLX-LNX && make clean && cd .. && $(RM) $(NAME)

re: fclean all

.PHONY: all