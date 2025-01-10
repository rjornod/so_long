NAME = so_long
CFLAGS = -Wextra -Wall -Werror -Wunreachable-code -Ofast -g
SRC = map_validation.c textures.c so_long.c map_rules.c lib/get_next_line/get_next_line.c lib/get_next_line/get_next_line_utils.c
OBJS = $(SRC:.c=.o)
MLX_LIB_DIR = lib/mlx42/build
MLX_LIB = mlx42
MLX_FLAGS = -ldl -lglfw -pthread -lm
INCLUDES = -Imlx42/include -Ilibft -Iget_next_line -Ift_printf
#LIBFT = lib/libft/libft.a
PRINTF = lib/ft_printf/libftprintf.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(PRINTF)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -L$(MLX_LIB_DIR) -l$(MLX_LIB) $(MLX_FLAGS) $(LIBFT) $(PRINTF)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

#$(LIBFT):
#	make -C lib/libft

$(PRINTF):
	make -C lib/ft_printf

clean:
	rm -f $(OBJS)
#	make -C lib/libft clean
	make -C lib/ft_printf clean

fclean: clean
	rm -f $(NAME)
#	make -C lib/libft clean
	make -C lib/ft_printf fclean

re: fclean all

.PHONY: all clean fclean re