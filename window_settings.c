/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_settings.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roberto <roberto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 16:49:54 by roberto           #+#    #+#             */
/*   Updated: 2025/01/17 16:51:14 by roberto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

//define window size and initialize MLX42
void start_mlx_window(t_game *game)
{
    int i;
    i = 0;
    game->window_width = (ft_strlen(game->map[0]) * 64);
    while (game->map[i] != NULL)
        i++;
    game->window_height = i * 64;
    game->mlx = mlx_init(game->window_width, game->window_height, "So Long", true);
    if (!game->mlx)
    {
        perror("Failed to initialize MLX42");
        exit(EXIT_FAILURE);
    }
}
 