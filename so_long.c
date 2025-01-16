/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojornod <rojornod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 15:04:42 by rojornod          #+#    #+#             */
/*   Updated: 2025/01/16 15:47:10 by rojornod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//include the right library
#include "so_long.h"

//specify window size
#define WIDTH 1728
#define HEIGHT 800


//keeps track of the inputs of the player, when player presses a movement key the movement counter gets
//updated and a new instance of the player image is created
void key_handler(mlx_key_data_t keydata, void *param)
{
    t_game *game = (t_game *)param;

    if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
    {
        ft_putendl_fd("Goodbye 🎅", 1);
        mlx_close_window(game->mlx);
    }
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
int get_window_height(char **map)
{
    int i;
    i = 0;
    int window_height;
    while (map[i] != NULL)
        i++;
    window_height = i * 64;
    ft_printf("\nwindow height is [%d]\n", window_height);
    return (window_height);
}
int get_window_width(char **map)
{
    int window_width;
    window_width = (ft_strlen(map[0]) * 64);
    ft_printf("window width is [%d]\n", window_width);
    return(window_width);    
}

//prints text on the top left of the window
void	text(mlx_t *mlx)
{
	mlx_put_string(mlx, "Oh no! Your elves are trying to steal your presents!", 20, 10);
	mlx_put_string(mlx, "Collect all your presents and get to your sleigh!", 20, 35);
	
}
 
void check_map_file(int argc, char **argv)
{
    const char *file_extension;
    size_t len_target;
    size_t file_name_length;
    
    file_extension = ".ber";
    file_name_length = ft_strlen(argv[1]);
    len_target = ft_strlen(file_extension);
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
    int window_width;
    int window_height;
    
    // Read map from the provided file path
    game.map = read_map(argv[1]);
    if (!game.map)
    {
        mlx_terminate(game.mlx);
        return (EXIT_FAILURE);
    }
    // Validate map elements
    validate_map_elements(game.map);

    //define window size
    window_height = get_window_height(game.map);
    window_width = get_window_width(game.map);
    check_map_file(argc, argv);
    game.move_count = 0;

    // Initialize MLX42
    if (!(game.mlx = mlx_init(window_width, window_height, "SAVE CHRISTMAS", true)))
    {
        puts(mlx_strerror(mlx_errno));
        return (EXIT_FAILURE);
    }


    // get_window_width(game.map);

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
    place_player(&game);
    place_collectibles(game.mlx, game.map);
    place_exit(game.mlx, game.map);

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
 