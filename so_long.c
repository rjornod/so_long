/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojornod <rojornod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 15:04:42 by rojornod          #+#    #+#             */
/*   Updated: 2024/12/19 15:22:56 by rojornod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//include the right library
#include "mlx42/include/MLX42/MLX42.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>

//specify window size
#define WIDTH 800
#define HEIGHT 600

static mlx_image_t	*g_img;
static mlx_image_t	*a_img;
static mlx_image_t	*c_img;
static mlx_image_t	*b_img;
static mlx_image_t *cat_img;
static mlx_image_t *floor_img;

void	key_handler(mlx_key_data_t keydata, void *param)
{
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(param);
	if (keydata.key == MLX_KEY_1 && keydata.action == MLX_PRESS)
		puts("Hello");
	if (keydata.key == MLX_KEY_2 && keydata.action == MLX_RELEASE)
		puts("World");
	if (keydata.key == MLX_KEY_3 && keydata.action == MLX_REPEAT)
		puts("!!!");
}

typedef struct s_game
{
	void *mlx;
	void *window;
} t_game;

// Function to read lines from a file and store them in a 2D array
void fill_map(t_game *game, int lines, char *map) {
    int file;
    int i;

    // Open the file for reading and writing
    file = open(map, O_RDWR);

    // Allocate memory for the map (lines + 1 for the NULL terminator)
    game->map = malloc(sizeof(char *) * (lines + 1));

    // Fill the first element of the array with the first line from the file
    game->map[0] = get_next_line(file);

    // Fill the rest of the array line by line
    i = 0;
    while (i < lines) {
        i++;
        game->map[i] = get_next_line(file);
    }

    // Close the file after reading
    close(file);
}

void my_scrollhook(double xdelta, double ydelta, void *param)
{
	// Simple up or down detection.
	if (ydelta > 0)
		puts("Up!");
	else if (ydelta < 0)
		puts("Down!");
}
void	hook(void* param)
{
	mlx_t* mlx;

	mlx = param;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_P))
    {
        printf("Deleting g_img: %p\n", g_img);
        mlx_delete_image(mlx, g_img);
		//set g_img to null after deleting it
		g_img = NULL;
        printf("g_img deleted\n");
    }
	//checks if cat_img is not null before modifying its instances
	if (cat_img)
	{
		if (mlx_is_key_down(mlx, MLX_KEY_W))
			cat_img->instances[0].y -= 15;
		if (mlx_is_key_down(mlx, MLX_KEY_S))
			cat_img->instances[0].y += 15;
		if (mlx_is_key_down(mlx, MLX_KEY_A))
			cat_img->instances[0].x -= 15;
		if (mlx_is_key_down(mlx, MLX_KEY_D))
			cat_img->instances[0].x += 15;
	}	
	
}

void	text(void *param)
{
	mlx_t* mlx;

	mlx = param;
	mlx_put_string(mlx, "Collect all the coins!", 20, 10);
	mlx_put_string(mlx, "Get to the exit", 20, 35);
	
}
void	read_map()
{
	
}
int32_t	main(void)
{
	mlx_t	*mlx;

	if (!(mlx = mlx_init(WIDTH, HEIGHT, "MLX42 TESTING", true)))
	{
		puts(mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}

	mlx_key_hook(mlx, &key_handler, mlx);
	mlx_scroll_hook(mlx, &my_scrollhook, NULL);
	
	//loads texture
	mlx_texture_t* floor = mlx_load_png("assets/floor.png");
	floor_img = mlx_texture_to_image(mlx, floor);
	if (!floor_img)
		perror("error");
	mlx_image_to_window(mlx, floor_img, 300, 400);
	mlx_texture_t* character = mlx_load_png("assets/cat.png");
	cat_img = mlx_texture_to_image(mlx, character);
	if (!cat_img)
		perror("error");
	mlx_image_to_window(mlx, cat_img, 140,140);

	text(mlx);
	mlx_loop_hook(mlx, &hook, mlx);
	mlx_loop(mlx);

	mlx_delete_image(mlx, cat_img);
	mlx_delete_texture(character);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
