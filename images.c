/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojornod <rojornod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 14:33:21 by rojornod          #+#    #+#             */
/*   Updated: 2025/01/22 15:15:04 by rojornod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_game	*add_wall_texture(mlx_t *mlx, t_game *game)
{
	game->wall = load_texture(mlx, "assets/ice.png");
	if (!game->wall)
        error_message("Failed to load wall texture");
	return (game);
}

t_game	*add_floor_texture(mlx_t *mlx, t_game *game)
{
	game->floor = load_texture(mlx, "assets/snow.png");
	return (game);
}

t_game	*add_c_texture(mlx_t *mlx, t_game *game)
{
	game->collect = load_texture(mlx, "assets/collect64.png");
	return (game);
}

t_game	*add_exit_texture(mlx_t *mlx, t_game *game)
{
	game->exit = load_texture(mlx, "assets/exit64.png");
	return (game);
}

t_game	*add_player_texture(mlx_t *mlx, t_game *game)
{
	game->player = load_texture(mlx, "assets/santa.png");
	return (game);
}
