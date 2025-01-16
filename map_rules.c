/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_rules.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojornod <rojornod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 10:46:24 by rojornod          #+#    #+#             */
/*   Updated: 2025/01/16 13:45:27 by rojornod         ###   ########.fr       */
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
   	mlx_texture_t *wall_texture = mlx_load_png("assets/ice.png");
    mlx_texture_t *floor_texture = mlx_load_png("assets/snow.png");

    if (!wall_texture || !floor_texture)
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
            else if (map[i][j] == '0' || map[i][j] == 'P' || map[i][j] == 'C' || map[i][j] == 'E')
        		image = mlx_texture_to_image(mlx, floor_texture);
            if (image)
                mlx_image_to_window(mlx, image, j * TILE_SIZE, i * TILE_SIZE);
            j++;
        }
        i++;
    }
    mlx_delete_texture(wall_texture);
    mlx_delete_texture(floor_texture);

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

void place_collectibles(mlx_t *mlx, char **map)
{
	mlx_texture_t *collectible_texture = mlx_load_png("assets/collectible.png");
    int i = 0;

    if (!collectible_texture)
    {
        perror("Failed to load textures");
        return;
    }
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
void place_exit(mlx_t *mlx, char **map)
{
	mlx_texture_t *exit_texture = mlx_load_png("assets/exit3.png");
    int i = 0;

    if (!exit_texture)
    {
        perror("Failed to load textures");
        return;
    }
    while (map[i] != NULL)
    {
        int j = 0;
        while (map[i][j] != '\0')
        {
            mlx_image_t *image = NULL;
				if (map[i][j] == 'E')
                image = mlx_texture_to_image(mlx, exit_texture);

            if (image)
                mlx_image_to_window(mlx, image, j * TILE_SIZE, i * TILE_SIZE);
            j++;
        }
        i++;
    }
    mlx_delete_texture(exit_texture);
}	
char **read_map(const char *filename)
{
	char	*line;
	int		i;
	int		fd;
	
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		error_message("Can't read the file. Make sure it exists and it's valid");
	char **map = malloc(100 * sizeof (char *));
	if (!map)
	{
		close(fd);
		error_message("Memory allocation failed");
	}
	i = 0;
	while ((line = get_next_line(fd)) != NULL)
    {
        size_t len = ft_strlen(line);
        if (len > 0 && line[len - 1] == '\n')
            line[len - 1] = '\0';
        map[i] = line;
        i++;
    }
    map[i] = NULL;
	close(fd);
	return (map);
}
