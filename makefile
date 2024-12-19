NAME = so_long
CFLAGS = -Wextra -Wall -Werror
SRC = so_long.c
OBJS = $(SRC:.c=.o)
MLX_LIB = mlx42
MLX_FLAGS = -lglfw -pthread -lm

all: $(NAME)

$(NAME): $OBJS
