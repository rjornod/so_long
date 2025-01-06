/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_rules.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojornod <rojornod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 10:46:24 by rojornod          #+#    #+#             */
/*   Updated: 2025/01/06 16:13:33 by rojornod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line/get_next_line.h"
#include "ft_printf/ft_printf.h"
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

	
char **read_map(const char *filename)
{
	char *line;
	int i;
	int	fd;
	
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("Error reading file");
		return (NULL);
	}

	char **map = malloc(100 * sizeof (char *));
	if (!map)
	{
		perror("memory allocation failed");
		close(fd);
		return (NULL);
	}

	i = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		map[i] = line;
		i++;
	}
	i = 0;
	while(map[i] != NULL)
	{
		int j = 0;
		while (map[i][j] != '\0')
		{
			if (map[i][j] == )
			printf("%c", map[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
	map[i] = NULL;
	close(fd);
	return (map);
	
}

int main()
{
	int i;
	i = 0;
	char **map = read_map("map/map.ber");
	if(!map)
	{
		return 1;
	}
	while(map[i] != NULL)
	{
		printf("%s", map[i]);
		i++;
	}
}