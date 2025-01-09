/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojornod <rojornod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 14:07:47 by rojornod          #+#    #+#             */
/*   Updated: 2025/01/09 14:42:26 by rojornod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
void load_textures(t_textures *textures, mlx_t *mlx)
{
    textures->player = mlx_texture_to_image(mlx, mlx_load_png("assets/santa.png"));
    textures->collect = mlx_texture_to_image(mlx, mlx_load_png("assets/collectible2.png"));
    textures->wall = mlx_texture_to_image(mlx, mlx_load_png("assets/wall.png"));
    textures->floor = mlx_texture_to_image(mlx, mlx_load_png("assets/snowfloor.png"));
    textures->enemy = mlx_texture_to_image(mlx, mlx_load_png("assets/enemy.png"));

    if (!textures->player || !textures->collect || !textures->wall || !textures->floor || !textures->enemy)
    {
        perror("Failed to load textures");
        exit(EXIT_FAILURE);
    }
}
