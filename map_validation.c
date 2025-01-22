/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojornod <rojornod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 14:00:17 by rojornod          #+#    #+#             */
/*   Updated: 2025/01/22 15:07:51 by rojornod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	validate_map_elements(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j] != '\0')
		{
			if (game->map[i][j] == 'P')
				game->player_count++;
			else if (game->map[i][j] == 'C')
				game->collectible_total++;
			else if (game->map[i][j] == 'E')
				game->exit_count++;
			else if ((game->map[i][j] != '1') && (game->map[i][j] != '0') && (game->map[i][j] != 'E') && (game->map[i][j] != 'P') && (game->map[i][j] != 'C'))
                error_message("Invalid character on the map. Only 10EPC allowed");
			j++;
		}
		i++;
	}
	ft_printf("Player count: %d\n", game->player_count);
	ft_printf("Collectible count: %d\n", game->collectible_total);
	ft_printf("Exit count: %d\n", game->exit_count);
	validate_map_closure(game);
	//validate_characters(game->map);
	validation_messages(game->player_count, game->collectible_total, game->exit_count);
}

void	validate_map_closure(t_game *game)
{
	int		i;
	int		j;
	size_t	row_length;

	row_length = ft_strlen(game->map[0]) - 1;
	i = 0;
	j = 0;
	while (j < ((int)row_length))
	{
		if (game->map[0][j] != '1')
			error_message("The map is not closed properly on the first row");
		j++;
	}
	while (game->map[i])
	{
		if ((ft_strlen(game->map[i]) - 1) != row_length)
			error_message("The map is not rectangular");
		if (game->map[i][0] != '1' || game->map[i][row_length] != '1')
		{
			ft_printf("\n[%d] [%s]\n", i, game->map[i]);
			error_message("The map is not closed properly on the sides");
		}
		i++;
	}
	j = 0;
	while (j < (int)row_length)
	{
		if (game->map[i - 1][j] != '1')
			error_message("The map is not closed properly on the last row");
		j++;
	}
}

void	validation_messages(int player_count, int collect_count, int exit_count)
{
	if (collect_count < 1)
		error_message("There must be at least one collectible on the map\n");
	if (exit_count != 1)
		error_message("There must be exactly one exit on the map\n");
	if (player_count != 1)
		error_message("There must be exactly one player on the map\n");
}

void	error_message(char *message)
{
	ft_putendl_fd("Error", 1);
	ft_putendl_fd(message, 1);
	exit(EXIT_FAILURE);
}
