/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojornod <rojornod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 14:07:47 by rojornod          #+#    #+#             */
/*   Updated: 2025/01/10 15:05:00 by rojornod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_image *add_player_texture(mlx_t *mlx, t_image *image)
{
	mlx_texture_t   *player_texture;

	player_texture = mlx_load_png("texture/player.png");
	if (player_texture == NULL)
		ft_printf("Problem with loading image");
	image->player = mlx_texture_to_image(mlx, player_texture);
	if (image->player == NULL)
		ft_printf("Problem adding texture P.Image");
	mlx_delete_texture(player_texture);
	return (image);
}

t_image *add_wall_texture(mlx_t *mlx, t_image *image)
{
	mlx_texture_t   *wall_texture;

	wall_texture = mlx_load_png("texture/wall.png");
	if (wall_texture == NULL)
		ft_printf("Problem with loading P.Image");
	image->wall = mlx_texture_to_image(mlx, wall_texture);
	if (image->wall == NULL)
		ft_printf("Problem adding texture P.Image");
	mlx_delete_texture(wall_texture);
	return (image);
}

t_image *add_floor_texture(mlx_t *mlx, t_image *image)
{
	mlx_texture_t   *floor_texture;

	floor_texture = mlx_load_png("texture/wall.png");
	if (!floor_texture)
		ft_printf("Problem with loading P.Image");
	image->floor = mlx_texture_to_image(mlx, floor_texture);
	if (image->floor == NULL)
		ft_printf("Problem adding texture P.Image");
	mlx_delete_texture(floor_texture);
	return (image);
}

t_image *add_exit_texture(mlx_t *mlx, t_image *image)
{
	mlx_texture_t   *exit_texture;

	exit_texture = mlx_load_png("texture/wall.png");
	if (!exit_texture)
		ft_printf("Problem with loading P.Image");
	image->exit = mlx_texture_to_image(mlx, exit_texture);
	if (image->exit == NULL)
		ft_printf("Problem adding texture P.Image");
	mlx_delete_texture(exit_texture);
	return (image);
}

t_image *add_collectible_texture(mlx_t *mlx, t_image *image)
{
	mlx_texture_t   *collectible_texture;

	collectible_texture = mlx_load_png("texture/snow.png");
	if (!collectible_texture)
		ft_printf("Problem with loading P.Image");
	image->collect = mlx_texture_to_image(mlx, collectible_texture);
	if (image->collect == NULL)
		ft_printf("Problem adding texture P.Image");
	mlx_delete_texture(collectible_texture);
	return (image);
}
