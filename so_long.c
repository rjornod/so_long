/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojornod <rojornod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 15:04:42 by rojornod          #+#    #+#             */
/*   Updated: 2025/01/09 15:50:32 by rojornod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//include the right library
#include "so_long.h"

//specify window size
#define WIDTH 800
#define HEIGHT 800


//keeps track of the inputs of the player, when player presses a movement key the movement counter gets
//updated and a new instance of the player image is created
void key_handler(mlx_key_data_t keydata, void *param)
{
    t_game *game = (t_game *)param;

    if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
        mlx_close_window(game->mlx);
    if (keydata.action == MLX_PRESS)
    {
        if (keydata.key == MLX_KEY_W)
        {
            game->player->instances[0].y -= TILE_SIZE;
            puts("UP!");
            game->move_count++;
        }
        if (keydata.key == MLX_KEY_S)
        {
            game->player->instances[0].y += TILE_SIZE;
            puts("DOWN!");
            game->move_count++;
        }
        if (keydata.key == MLX_KEY_A)
        {
            game->player->instances[0].x -= TILE_SIZE;
            puts("LEFT!");
            game->move_count++;
        }
        if (keydata.key == MLX_KEY_D)
        {
            game->player->instances[0].x += TILE_SIZE;
            puts("RIGHT!");
            game->move_count++;
        }
		if (keydata.key == MLX_KEY_D || keydata.key == MLX_KEY_W || keydata.key == MLX_KEY_S || keydata.key == MLX_KEY_A)
        	printf("Movements made: %d\n\n", game->move_count);
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
void	text(mlx_t *mlx)
{
	mlx_put_string(mlx, "Collect all the presents!", 20, 10);
	mlx_put_string(mlx, "Get to your sleigh!", 20, 35);
	
}
int32_t main(void)
{
    t_game game;
    game.move_count = 0;

    if (!(game.mlx = mlx_init(WIDTH, HEIGHT, "MLX42 TESTING", true)))
    {
        puts(mlx_strerror(mlx_errno));
        return (EXIT_FAILURE);
    }

    game.map = read_map("map/map.ber");
    if (!game.map)
    {
        mlx_terminate(game.mlx);
        return (EXIT_FAILURE);
    }

    mlx_texture_t *character = mlx_load_png("assets/santa.png");
    if (!character)
    {
        perror("Failed to load player texture");
        mlx_terminate(game.mlx);
        return (EXIT_FAILURE);
    }

    game.player = mlx_texture_to_image(game.mlx, character);
    if (!game.player)
    {
        perror("Failed to create player image");
        mlx_delete_texture(character);
        mlx_terminate(game.mlx);
        return (EXIT_FAILURE);
    }

    place_map(game.mlx, game.map);
    mlx_image_to_window(game.mlx, game.player, 0, 0);
    place_player(&game);
	place_collectibes(game.mlx, game.map);

    mlx_key_hook(game.mlx, &key_handler, &game);
    text(game.mlx);
    mlx_loop(game.mlx);

    mlx_delete_image(game.mlx, game.player);
    mlx_delete_texture(character);
    mlx_terminate(game.mlx);

    int i = 0;
    while (game.map[i] != NULL)
    {
        free(game.map[i]);
        i++;
    }
    free(game.map);

    return (EXIT_SUCCESS);
}
 