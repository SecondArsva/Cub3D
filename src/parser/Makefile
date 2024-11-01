NAME = cub3D

CC = cc -Wall -Wextra -Werror
LDFLAGS = -lreadline
RM = rm -f

LIBFT_DIR = ../../libs/libft/
LIBFT = $(LIBFT_DIR)libft.a

SRC =	main.c			\

OBJS = $(SRC:%.c=%.o)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(OBJS) $(LIBFT) -o $(NAME) $(LDFLAGS)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

%.o: %.c
	$(CC) -c $< -o $@

clean:
	$(RM) $(OBJS)
	$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	$(RM) $(NAME)
	$(MAKE) fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re