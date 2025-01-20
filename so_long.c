/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roberto <roberto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 15:04:42 by rojornod          #+#    #+#             */
/*   Updated: 2025/01/17 17:16:21 by roberto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//include the right library
#include "so_long.h"

void	initialize_game(t_game *game) {
	game->mlx = NULL;
	game->player = NULL;
	game->move_count = 0;
	game->collectible_count = 0;
	game->map = NULL;
	game->player_position_x = 0;
	game->player_position_y = 0;
	game->exit_position_x = 0;
	game->exit_position_y = 0;
	game->window_height = 0;
	game->window_width = 0;
	game->textures = NULL;
}

//keeps track of the inputs of the player, when player presses a movement key the movement counter gets
//updated and a new instance of the player image is created
void key_handler(mlx_key_data_t keydata, void *param)
{
    t_game *game = (t_game *)param;

    if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
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

//prints text on the top left of the window
void	text(mlx_t *mlx)
{
	mlx_put_string(mlx, "Oh no! Your elves are trying to steal your presents!", 20, 10);
	mlx_put_string(mlx, "Collect all your presents and get to your sleigh!", 20, 35);
	
}
 
void check_map_file(int argc, char **argv)
{
    size_t file_name_length;
    
    file_name_length = ft_strlen(argv[1]);
	if (file_name_length < 4 || ft_strncmp(&argv[1][file_name_length - 4], ".ber", 4))
		error_message("File extension invalid, please use a .ber file for the map");
    if (argc != 2)
        error_message("You must use exactly one file with a map. Example: ./so_long <map_file>");
    if (argv[1] == NULL)
        ft_printf("test");   
}
int32_t main(int argc, char **argv)
{
    t_game game;
	
	initialize_game(&game);
	// Read map from the provided file path
    game.map = read_map(argv[1]);
    if (!game.map)
    {
        mlx_terminate(game.mlx);
        return (EXIT_FAILURE);
    }
    // Validate map elements
	check_player_position(&game);
    validate_map_elements(game.map);
    check_map_file(argc, argv);
    game.move_count = 0;
	//get_window_size(&game);
	start_mlx_window(&game);
    // Initialize player image
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
    // Place images on the map
    place_map(game.mlx, game.map);
    mlx_image_to_window(game.mlx, game.player, 0, 0);
    place_collectibles(game.mlx, game.map);
    place_exit(game.mlx, game.map);
    place_player(&game);

    // MLX hooks and loops
    mlx_key_hook(game.mlx, &key_handler, &game);
    text(game.mlx);
    mlx_loop(game.mlx);

    // Clean up
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
 