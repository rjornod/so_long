/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_rules.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojornod <rojornod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 10:46:24 by rojornod          #+#    #+#             */
/*   Updated: 2025/01/09 15:51:17 by rojornod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib/get_next_line/get_next_line.h"
#include "lib/ft_printf/ft_printf.h"
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include "so_long.h"
#include "lib/mlx42/include/MLX42/MLX42.h"

void place_map(mlx_t *mlx, char **map)
{
   	mlx_texture_t *wall_texture = mlx_load_png("assets/wall.png");
    mlx_texture_t *floor_texture = mlx_load_png("assets/floor.png");
    mlx_texture_t *exit_texture = mlx_load_png("assets/exit.png");
    //mlx_texture_t *collectible_texture = mlx_load_png("assets/collectible.png");

    if (!wall_texture || !exit_texture || !floor_texture)
    {
        perror("Failed to load textures");
        return;
    }
    int i = 0;
    while (map[i] != NULL)
    {
        int j = 0;
        while (map[i][j] != '\0')
        {
            mlx_image_t *image = NULL;
            if (map[i][j] == '1')
                image = mlx_texture_to_image(mlx, wall_texture);
            else if (map[i][j] == '0' || map[i][j] == 'P' || map[i][j] == 'C')
        		image = mlx_texture_to_image(mlx, floor_texture);
            else if (map[i][j] == 'E')
                image = mlx_texture_to_image(mlx, exit_texture);
            // else if (map[i][j] == 'C')
            //     image = mlx_texture_to_image(mlx, collectible_texture);

            if (image)
                mlx_image_to_window(mlx, image, j * TILE_SIZE, i * TILE_SIZE);
            j++;
        }
        i++;
    }
    mlx_delete_texture(wall_texture);
    mlx_delete_texture(floor_texture);
    mlx_delete_texture(exit_texture);
    // mlx_delete_texture(collectible_texture);
}	

void place_collectibes(mlx_t *mlx, char **map)
{
	mlx_texture_t *collectible_texture = mlx_load_png("assets/collectible.png");

    if (!collectible_texture)
    {
        perror("Failed to load textures");
        return;
    }
    int i = 0;
    while (map[i] != NULL)
    {
        int j = 0;
        while (map[i][j] != '\0')
        {
            mlx_image_t *image = NULL;
				if (map[i][j] == 'C')
                image = mlx_texture_to_image(mlx, collectible_texture);

            if (image)
                mlx_image_to_window(mlx, image, j * TILE_SIZE, i * TILE_SIZE);
            j++;
        }
        i++;
    }
    mlx_delete_texture(collectible_texture);
}	
void place_player(t_game *game)
{
    int i = 0;
    while (game->map[i] != NULL)
    {
        int j = 0;
        while (game->map[i][j] != '\0')
        {
            if (game->map[i][j] == 'P')
            {
				game->player->instances[0].x = j * TILE_SIZE;
				game->player->instances[0].y = i * TILE_SIZE;
                return;
            }
            j++;
        }
        i++;
    }
}
char **read_map(const char *filename)
{
	char	*line;
	int		i;
	int		fd;
	int		player_counter;
	int		exit_counter;
	
	player_counter = 0;
	exit_counter = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("Error reading file");
		return (NULL);
	}
	char **map = malloc(100 * sizeof (char *));
	if (!map)
	{
		perror("memory allocation failed");
		close(fd);
		return (NULL);
	}
	i = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		map[i] = line;
		i++;
	}
	map[i] = NULL;
	i = 0;
	while(map[i] != NULL)
	{
		int j = 0;
		while (map[i][j] != '\0')
		{
			if (map[i][j] == 9 || map[i][j] == 11 || map[i][j] == 12 || map[i][j] == 13 || map[i][j] == 32)
				j++;
			if (map[i][j] == 'P')
            	player_counter++;
        	if (map[i][j] == 'E')
            	exit_counter++;
       	 	j++;
			//ft_printf("%c", map[i][j]);
		}
		i++;
	}
	if (exit_counter != 1 || player_counter != 1)
	{
		ft_printf("Error : invalid number of players or exits\n");
		ft_printf("exits: %d\n", exit_counter);
		ft_printf("players: %d\n", player_counter);
		exit(EXIT_FAILURE);
	}
	map[i] = NULL;
	close(fd);
	return (map);
}
