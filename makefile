NAME = so_long
CFLAGS = -Wextra -Wall -Werror
SRC = so_long.c map_rules.c
OBJS = $(SRC:.c=.o)
MLX_LIB = mlx42
MLX_FLAGS = -lglfw -pthread -lm
INCLUDES = -Imlx42/include -Ilibft -Iget_next_line
LIBFT = libft/libft.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
		$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -L$(MLX_LIB) $(MLX_FLAGS) $(LIBFT) 

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	make -C libft


clean:
	rm -f $(OBJS)
	make -C libft clean

fclean: clean
	rm -f $(NAME)
	make -C libft fclean

re: fclean all