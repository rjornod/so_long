/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roberto <roberto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 16:00:30 by rojornod          #+#    #+#             */
/*   Updated: 2025/01/17 17:13:39 by roberto          ###   ########.fr       */
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
#define TILE_SIZE 64

typedef struct s_image
{
	mlx_image_t	*floor;
	mlx_image_t	*wall;
	mlx_image_t	*exit;
	mlx_image_t	*collect;
	mlx_image_t	*player;
}	t_image;

t_image	*add_wall_texture(mlx_t *mlx, t_image *image);
t_image	*add_floor_texture(mlx_t *mlx, t_image *image);
t_image	*add_collectible_texture(mlx_t *mlx, t_image *image);
t_image	*add_exit_texture(mlx_t *mlx, t_image *image);
t_image	*add_player_texture(mlx_t *mlx, t_image *image);

typedef struct s_game
{
	mlx_t		*mlx;
	mlx_image_t	*player;
	int			move_count;
	int			collectible_count;
	char		**map;
	int			player_position_x;
	int			player_position_y;
	int			exit_position_x;
	int			exit_position_y;
	int			window_height;
	int			window_width;
	t_image		*textures;
}	t_game;

//window
// int		get_window_height(char **map);
// int 	get_window_width(char **map);
//void 	get_window_size(t_game *game);
void	start_mlx_window(t_game *game);

void	error_message(char *message);

//map
char 	**read_map(const char *filename);
void 	place_map(mlx_t *mlx, char **map);
void 	place_collectibles(mlx_t *mlx, char **map);
void 	place_exit(mlx_t *mlx, char **map);
void	place_player(t_game *game);

//validation
void 	validation_messages(int player_count, int collect_count, int exit_count);
void    validate_characters(char **map);
void	validate_map_elements(char **map);
void 	validate_map_closure(char **map);

// void	validate_map_height_width(char *map);

//path check
void check_player_position(t_game *game);