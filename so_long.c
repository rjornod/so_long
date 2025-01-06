/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojornod <rojornod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 15:04:42 by rojornod          #+#    #+#             */
/*   Updated: 2025/01/06 16:02:51 by rojornod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//include the right library
#include "so_long.h"
//#include "map_rules.c"

//specify window size
#define WIDTH 800
#define HEIGHT 600

static mlx_image_t *player;
static mlx_image_t *floor_img;
int move_count = 0;

void	key_handler(mlx_key_data_t keydata, void *param)
{
	mlx_t* mlx;

	mlx = param;
	// if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	// 	mlx_close_window(param);
	// if (keydata.key == MLX_KEY_1 && keydata.action == MLX_PRESS)
	// 	puts("Hello");
	// if (keydata.key == MLX_KEY_2 && keydata.action == MLX_RELEASE)
	// 	puts("World");
	// if (keydata.key == MLX_KEY_3 && keydata.action == MLX_REPEAT)
	// 	puts("!!!");
		
	if (keydata.action == MLX_PRESS)
	{
		
		if (keydata.key == MLX_KEY_W)
		{
			player->instances[0].y -= 100;
			puts("UP!");
			move_count++;
			printf("Movements made: %d\n\n", move_count);
		}
		if (keydata.key == MLX_KEY_S)
			{
				player->instances[0].y += 100;
				puts("DOWN!");
				move_count++;
				printf("Movements made: %d\n\n", move_count);
			}
		if (keydata.key == MLX_KEY_A)
			{
				player->instances[0].x -= 100;
				puts("LEFT!");
				move_count++;
				printf("Movements made: %d\n\n", move_count);
			}
		if (keydata.key == MLX_KEY_D)
			{
				player->instances[0].x += 100;
				puts("RIGHT!");
				move_count++;
				printf("Movements made: %d\n\n", move_count);
			}
		
	}
}

// typedef struct s_game
// {
// 	void *mlx;
// 	void *window;
// } t_game;

// // Function to read lines from a file and store them in a 2D array
// void fill_map(t_game *game, int lines, char *map) {
//     int file;
//     int i;

//     // Open the file for reading and writing
//     file = open(map, O_RDWR);

//     // Allocate memory for the map (lines + 1 for the NULL terminator)
//     mlx->map = malloc(sizeof(char *) * (lines + 1));

//     // Fill the first element of the array with the first line from the file
//     game->map[0] = get_next_line(file);

//     // Fill the rest of the array line by line
//     i = 0;
//     while (i < lines) {
//         i++;
//         game->map[i] = get_next_line(file);
//     }

//     // Close the file after reading
//     close(file);
// }

// void my_scrollhook(double xdelta, double ydelta, void *param)
// {
// 	// Simple up or down detection.
// 	if (ydelta > 0)
// 		puts("Up!");
// 	else if (ydelta < 0)
// 		puts("Down!");
// }
// void	hook(void* param)
// {
// 	mlx_t* mlx;

// mlx = param;
// 	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
// 		mlx_close_window(mlx);
// 	// if (mlx_is_key_down(mlx, MLX_KEY_P))
//     // {
//     //     printf("Deleting g_img: %p\n", g_img);
//     //     mlx_delete_image(mlx, g_img);
// 	// 	//set g_img to null after deleting it
// 	// 	g_img = NULL;
//     //     printf("g_img deleted\n");
//     // }
// 	//checks if the player img is not null before modifying its instances
// if (keydata.action)
// {
// 		if (mlx_is_key_down(mlx, MLX_KEY_W))
// 			main_c_img->instances[0].y -= 1;
// 		if (mlx_is_key_down(mlx, MLX_KEY_S))
// 			main_c_img->instances[0].y += 1;
// 		if (mlx_is_key_down(mlx, MLX_KEY_A))
// 			main_c_img->instances[0].x -= 1;
// 		if (mlx_is_key_down(mlx, MLX_KEY_D))
// 			main_c_img->instances[0].x += 1;
// 	}	
	
//  }


void	text(void *param)
{
	mlx_t* mlx;

	mlx = param;
	mlx_put_string(mlx, "Collect all the souls!", 20, 10);
	mlx_put_string(mlx, "Get to the exit", 20, 35);
	
}
int32_t	main(void)
{
	// int i;
	// i = 0;
	// char **map = read_map("map/map.ber");
	// if(!map)
	// {
	// 	return 1;
	// }
	// while(map[i] != NULL)
	// {
	// 	printf("%s", map[i]);
	// 	i++;
	// }
	mlx_t	*mlx;


	if (!(mlx = mlx_init(WIDTH, HEIGHT, "MLX42 TESTING", true)))
	{
		puts(mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}

	mlx_key_hook(mlx, &key_handler, mlx);
	//mlx_scroll_hook(mlx, &my_scrollhook, NULL);
	
	//loads texture
	mlx_texture_t* floor = mlx_load_png("assets/floor.png");
	floor_img = mlx_texture_to_image(mlx, floor);
	if (!floor_img)
		perror("error");
	mlx_image_to_window(mlx, floor_img, 300, 400);
	mlx_texture_t* character = mlx_load_png("assets/mainchar100.png");
	player = mlx_texture_to_image(mlx, character);
	if (!player)
		perror("error");
	mlx_image_to_window(mlx, player, 140,140);

	text(mlx);
	//mlx_loop_hook(mlx, &hook, mlx);
	mlx_loop(mlx);

	mlx_delete_image(mlx, player);
	mlx_delete_texture(character);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
 