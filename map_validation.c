/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojornod <rojornod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 14:00:17 by rojornod          #+#    #+#             */
/*   Updated: 2025/01/10 16:48:00 by rojornod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
void	validate_map_elements(char *map)
{
	int	player_count = 0;
	int	collect_count = 0;
	int exit_count = 0;
	int i = 0;

	while (map[i] != '\0')
	{
		if (map[i] == 'P')
			player_count++;
		if (map[i] == 'E')
			exit_count++;
		if (map[i] == 'C')
			collect_count++;
		i++;
	}

	if (collect_count < 1)
		ft_printf("At least 1 collectible must be on the map\n");
	if (exit_count != 1)
		ft_printf("There must be exactly one exit on the map\n");
	if (player_count != 1)
		ft_printf("There must be exactly one player on the map\n");
}

void	error_message(char *message)
{
	ft_putendl_fd("Error: ", 1);
	ft_putendl_fd(message, 1);
	exit(EXIT_FAILURE);
}