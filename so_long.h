/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojornod <rojornod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 16:00:30 by rojornod          #+#    #+#             */
/*   Updated: 2025/01/22 16:28:09 by rojornod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib/mlx42/include/MLX42/MLX42.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include "lib/libft/libft.h"
#include "lib/get_next_line/get_next_line.h"
#include "lib/ft_printf/ft_printf.h"
#define T_SIZE 64
#define MAX_MAP_HEIGHT 1000
#define MAX_MAP_WIDTH 1000

typedef struct s_game
{
	mlx_t			*mlx;
	mlx_image_t		*floor;
	mlx_image_t		*wall;
	mlx_image_t		*exit;
	mlx_image_t		*collect;
	mlx_image_t		*player;
	mlx_image_t		*collect_images[MAX_MAP_HEIGHT][MAX_MAP_WIDTH];
	mlx_image_t		*image;
	int				move_count;
	int				collectible_count;
	int				collectible_total;
	int				player_count;
	int				exit_count;
	char			**map;
	int				player_pos_x;
	int				player_pos_y;
	int				exit_position_x;
	int				exit_position_y;
	int				w_height;
	int				w_width;
	int				map_x;
	int				map_y;
	bool			game_over;
}	t_game;

mlx_image_t	*load_texture(mlx_t *mlx, const char *path);
t_game		*add_wall_texture(mlx_t *mlx, t_game *image);
t_game		*add_floor_texture(mlx_t *mlx, t_game *image);
t_game		*add_c_texture(mlx_t *mlx, t_game *image);
t_game		*add_exit_texture(mlx_t *mlx, t_game *image);
t_game		*add_player_texture(mlx_t *mlx, t_game *image);


void		game_struct_init(t_game *game);
int			get_w_width(char **map);
int			get_w_height(char **map);
void		start_mlx_window(t_game *game);
void		error_message(char *message);
char		**read_map(const char *filename);
void		place_map(t_game *game);
void		place_collectibles(t_game *game);
void		place_exit(t_game *game);
void		place_player(t_game *game);
void		validation_messages(int player_count, int collect_count, int exit_count);
//void		validate_characters(t_game *game);
void		validate_map_elements(t_game *game);
void		validate_map_closure(t_game *game);

void		val_payer_pos(t_game *game, mlx_key_data_t keydata);
void		check_end_game(t_game *game);
void		winning_screen(t_game *game);
void		clean_images(t_game *game);

