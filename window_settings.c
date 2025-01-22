/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_settings.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojornod <rojornod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 16:49:54 by roberto           #+#    #+#             */
/*   Updated: 2025/01/22 15:08:54 by rojornod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
this file defines the window size based on the map given initializes MLX42
with proper sizing 
*/
void	start_mlx_window(t_game *game)
{
	int	i;

	i = 0;
	game->w_width = (ft_strlen(game->map[0]) * 64);
	while (game->map[i] != NULL)
		i++;
	game->w_height = i * 64;
	game->mlx = mlx_init(game->w_width, game->w_height, "SAVE CHRISTMAS", true);
	if (!game->mlx)
	{
		perror("Failed to initialize MLX42");
		exit(EXIT_FAILURE);
	}
}

int	get_w_height(char **map)
{
	int	i;
	int	h_width;

	i = 0;
	while (map[i] != NULL)
		i++;
	h_width = i * 64;
	ft_printf("\nwindow height is [%d]\n", h_width);
	return (h_width);
}

int	get_w_width(char **map)
{
	int	w_width;

	w_width = (ft_strlen(map[0]) * 64);
	ft_printf("window width is [%d]\n", w_width);
	return (w_width);
}
