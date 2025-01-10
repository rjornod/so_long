/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojornod <rojornod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 16:00:30 by rojornod          #+#    #+#             */
/*   Updated: 2025/01/10 16:48:09 by rojornod         ###   ########.fr       */
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

// typedef struct s_game
// {
//    	mlx_t		*mlx;
//     int			move_count;
// 	int			collectible_count;
//     char		**map;
//     mlx_image_t	*player;
// 	mlx_image_t	*collectible;
// } t_game;
void place_collectibes(mlx_t *mlx, char **map);
// typedef struct s_textures
// {
//     mlx_t *mlx;
//     mlx_image_t *player;
// 	mlx_image_t *collect;
// 	mlx_image_t *wall;
// 	mlx_image_t *floor;
// 	mlx_image_t *enemy;
// } t_textures;

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
	int			height;
	int			width;
	t_image		*textures;
}	t_game;

void	validate_map_elements(char *map);
void	error_message(char *message);
char 	**read_map(const char *filename);
void 	place_map(mlx_t *mlx, char **map);
void 	place_collectibles(mlx_t *mlx, char **map);
void 	place_exit(mlx_t *mlx, char **map);
void	place_player(t_game *game);