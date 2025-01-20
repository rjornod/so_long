/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roberto <roberto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 16:49:49 by roberto           #+#    #+#             */
/*   Updated: 2025/01/18 14:15:25 by roberto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void check_player_position(t_game *game)
{
	int i;
	i = 0;
	int j;
	while(game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			if (game->map[i][j] == 'P')
			{
				game->player_position_x = j * 64;
				game->player_position_y = i * 64;
			}
			if (game->map[i][j] == 'E')
			{
				game->exit_position_x = j * 64;
				game->exit_position_y = i * 64;
			}
			if (game->map[i][j] == 'C')
			{
				game->exit_position_x = j * 64;
				game->exit_position_y = i * 64;
			}
			j++;
		}
		i++;
	}
	ft_printf("The player is positioned at: [%dx] and [%dy]\n", game->player_position_x, game->player_position_y );
	ft_printf("The exit is positioned at: [%dx] and [%dy]\n", game->exit_position_x, game->exit_position_y );
}

