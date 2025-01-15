/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojornod <rojornod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 14:00:17 by rojornod          #+#    #+#             */
/*   Updated: 2025/01/15 12:15:19 by rojornod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void validate_map_elements(char **map)
{
    int player_count = 0;
    int collect_count = 0;
    int exit_count = 0;
    int i = 0;
    int j;

    // Count map elements
    while (map[i])
    {
        j = 0;
        while (map[i][j] != '\0')
        {
            if (map[i][j] == 'P')
                player_count++;
            else if (map[i][j] == 'C')
                collect_count++;
            else if (map[i][j] == 'E')
                exit_count++;
            j++;
        }
        i++;
    }
    ft_printf("Player count: %d\n", player_count);
    ft_printf("Collectible count: %d\n", collect_count);
    ft_printf("Exit count: %d\n", exit_count);
    validate_map_closure(map);
    validation_messages(player_count, collect_count, exit_count);
}

void validate_map_closure(char **map)
{
    int i = 0;
    size_t row_length;


    row_length = ft_strlen(map[0]) - 1;
    int j = 0;
    while (j < ((int)row_length))
    {
        if (map[0][j] != '1')
            error_message("The map is not closed properly on the first row");
        j++;
    }
    while (map[i])
    {
        if ((ft_strlen(map[i]) -1) != row_length)
            ft_printf("All rows in the map must have the same length");
        if (map[i][0] != '1' || map[i][row_length - 1] != '1')
            error_message("The map is not closed properly on the sides");
        i++;
    }
    j = 0;
    while (j < (int)row_length)
    {
        if (map[i - 1][j] != '1')
            error_message("The map is not closed properly on the last row");
        j++;
    }
}

void validation_messages(int player_count, int collect_count, int exit_count)
{
    if (collect_count < 1)
        error_message("There must be at least one collectible on the map\n");
    if (exit_count != 1)
        error_message("There must be exactly one exit on the map\n");
    if (player_count != 1)
        error_message("There must be exactly one player on the map\n");
}

void error_message(char *message)
{
    ft_putendl_fd("Error", 1);
    ft_putendl_fd(message, 1);
    exit(EXIT_FAILURE);
}
