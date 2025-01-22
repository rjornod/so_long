/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_rules.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojornod <rojornod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 10:46:24 by rojornod          #+#    #+#             */
/*   Updated: 2025/01/22 16:15:46 by rojornod         ###   ########.fr       */
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

void	place_map(t_game *game)
{
	int				i;
	int				j;

	i = 0;
	while (game->map[i] != NULL)
	{
		j = 0;
		while (game->map[i][j] != '\0')
		{
			if (game->map[i][j] == '1')
			{
				if (!game->wall)
					error_message("Wall texture not loaded");
                printf("Placing wall at (%d, %d)\n", j, i);
				mlx_image_to_window(game->mlx, game->wall, j * T_SIZE, i * T_SIZE);

			}
			else if (game->map[i][j] == '0' || game->map[i][j] == 'P'
					|| game->map[i][j] == 'C' || game->map[i][j] == 'E')
				mlx_image_to_window(game->mlx, game->floor, j * T_SIZE, i * T_SIZE);
			j++;
		}
		i++;
	}
}

void	place_player(t_game *game)
{
	int				i;
	int				j;

	i = 0;
	if (!game->player)
		error_message("Failed to load player texture");
	mlx_image_to_window(game->mlx, game->player, 0, 0);
	while (game->map[i] != NULL)
	{
		j = 0;
		while (game->map[i][j] != '\0')
		{
			if (game->map[i][j] == 'P')
			{
				game->player->instances[0].x = j * T_SIZE;
				game->player->instances[0].y = i * T_SIZE;
				return ;
			}
			j++;
		}
		i++;
	}
	error_message("Player not found on the map");
}

void place_collectibles(t_game *game)
{
    int i = 0;
    while (game->map[i] != NULL)
    {
        int j = 0;
        while (game->map[i][j] != '\0')
        {
            if (game->map[i][j] == 'C')
            {
                mlx_image_t *collectible_image = load_texture(game->mlx, "assets/collect64.png");
                if (!collectible_image)
                    error_message("Failed to load collectible texture");
                int status = mlx_image_to_window(game->mlx, collectible_image, j * T_SIZE, i * T_SIZE);
                if (status != 0)
                    error_message("Failed to place collectible image in window");
                game->collect_images[i][j] = collectible_image;
            }
            j++;
        }
        i++;
    }
}

void	place_exit(t_game *game)
{
	int				i;
	int				j;

	i = 0;
	while (game->map[i] != NULL)
	{
		j = 0;
		while (game->map[i][j] != '\0')
		{
			if (game->map[i][j] == 'E')
				mlx_image_to_window(game->mlx, game->exit, j * T_SIZE, i * T_SIZE);
			j++;
		}
		i++;
	}
}

char	**read_map(const char *filename)
{
	char	*line;
	int		i;
	int		fd;
	size_t	len;
	char	**map;

	map = malloc(100 * sizeof (char *));
	line = NULL;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		error_message("Can't read file. Make sure it exists and it's valid");
	if (!map)
	{
		close(fd);
		error_message("Memory allocation failed");
	}
	i = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		len = ft_strlen(line);
		if (len > 0 && line[len - 1] == '\n')
			line[len - 1] = '\0';
		map[i] = line;
		i++;
	}
	map[i] = NULL;
	close(fd);
	return (map);
}
