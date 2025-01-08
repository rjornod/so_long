/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojornod <rojornod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 16:00:30 by rojornod          #+#    #+#             */
/*   Updated: 2025/01/08 16:44:59 by rojornod         ###   ########.fr       */
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

char **read_map(const char *filename);
void place_map(mlx_t *mlx, char **map);
void place_player(mlx_t *mlx, char **map);