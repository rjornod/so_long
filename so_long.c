/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojornod <rojornod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 15:04:42 by rojornod          #+#    #+#             */
/*   Updated: 2025/01/08 16:43:17 by rojornod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//include the right library
#include "so_long.h"
//#include "map_rules.c"

//specify window size
#define WIDTH 800
#define HEIGHT 600

static mlx_image_t *player;
int move_count = 0;

//keeps track of the inputs of the player, when player presses a movement key the movement counter gets
//updated and a new instance of the player image is created
void	key_handler(mlx_key_data_t keydata, void *param)
{
	mlx_t* mlx;

	mlx = param;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (keydata.action == MLX_PRESS)
	{
		if (keydata.key == MLX_KEY_W)
		{
			player->instances[0].y -= 64;
			puts("UP!");
			move_count++;
			printf("Movements made: %d\n\n", move_count);
		}
		if (keydata.key == MLX_KEY_S)
			{
				player->instances[0].y += 64;
				puts("DOWN!");
				move_count++;
				printf("Movements made: %d\n\n", move_count);
			}
		if (keydata.key == MLX_KEY_A)
			{
				player->instances[0].x -= 64;
				puts("LEFT!");
				move_count++;
				printf("Movements made: %d\n\n", move_count);
			}
		if (keydata.key == MLX_KEY_D)
			{
				player->instances[0].x += 64;
				puts("RIGHT!");
				move_count++;
				printf("Movements made: %d\n\n", move_count);
			}
		
	}
}
// void mlx_set_window_size(mlx_t* mlx, int32_t new_width, int32_t new_height)
// {
// 	(void)mlx;
// 	char **map;
// 	map = read_map("map/map.ber");
// 	int i;
// 	i= 0;
// 	new_height = ft_strlen(map[i]);
// 	printf("%d", new_height);
// 	new_width = 100;
// }

//prints text on the top left of the window
void	text(void *param)
{
	mlx_t* mlx;

	mlx = param;
	mlx_put_string(mlx, "Collect all the presents!", 20, 10);
	mlx_put_string(mlx, "Get to your sleigh!", 20, 35);
	
}
int32_t	main(void)
{
	mlx_t	*mlx;
	if (!(mlx = mlx_init(WIDTH, HEIGHT, "MLX42 TESTING", true)))
	{
		puts(mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
	char **map;
	map = read_map("map/map.ber");
	mlx_key_hook(mlx, &key_handler, mlx);
	place_map(mlx, map);
	place_player(mlx, map);
	mlx_texture_t* character = mlx_load_png("assets/santa.png");
	player = mlx_texture_to_image(mlx, character);

	mlx_image_to_window(mlx, player, 320,320);
	text(mlx);
	mlx_loop(mlx);
	mlx_delete_image(mlx, player);
	mlx_delete_texture(character);
	mlx_terminate(mlx);
	 int i = 0;
    while (map[i] != NULL)
    {
        free(map[i]);
        i++;
    }
    free(map);
	return (EXIT_SUCCESS);
}
 