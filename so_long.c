/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojornod <rojornod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 15:04:42 by rojornod          #+#    #+#             */
/*   Updated: 2025/01/22 16:39:55 by rojornod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//include the right library
#include "so_long.h"
void	key_handler(mlx_key_data_t keydata, void *param)
{
	t_game *game = (t_game *)param;
	game->player_pos_x = game->player->instances[0].x;
	game->player_pos_y = game->player->instances[0].y;   
	 
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		ft_putendl_fd("Goodbye 🎅", 1);
		mlx_close_window(game->mlx);
	}
	if (game->game_over)
        return;
	if (keydata.action == MLX_PRESS)
	{
		if (keydata.key == MLX_KEY_W)
			game->player_pos_y -= T_SIZE;
		if (keydata.key == MLX_KEY_S)
			game->player_pos_y += T_SIZE;
		if (keydata.key == MLX_KEY_A)
			game->player_pos_x -= T_SIZE;
		if (keydata.key == MLX_KEY_D)
			game->player_pos_x += T_SIZE;
		val_payer_pos(game, keydata);
		check_end_game(game);
    }
}
void	val_payer_pos(t_game *game, mlx_key_data_t keydata)
{
	game->map_x = game->player_pos_x / T_SIZE;
		game->map_y = game->player_pos_y / T_SIZE;

		// Check if the new position is a wall
		if (game->map[game->map_y][game->map_x] != '1')
		{
			game->player->instances[0].x = game->player_pos_x;
			game->player->instances[0].y = game->player_pos_y;
			if (keydata.key == MLX_KEY_W || keydata.key == MLX_KEY_S || keydata.key == MLX_KEY_A || keydata.key == MLX_KEY_D)
			{
				game->move_count++;
				ft_printf("Movements made: %d\n", game->move_count);
			}
		}
}
void	check_end_game(t_game *game)
{
	if (game->map[game->map_y][game->map_x] == 'C')
	{
		game->map[game->map_y][game->map_x] = '0';
		if (game->collect_images[game->map_y][game->map_x])
		{
			mlx_delete_image(game->mlx, game->collect_images[game->map_y][game->map_x]);
			game->collect_images[game->map_y][game->map_x] = NULL;
		}
		game->collectible_count++;
		ft_printf("You found a collectible! You now have [%d]\n",  game->collectible_count);
	}
	if (game->map[game->map_y][game->map_x] == 'E')
	{
		if (game->collectible_count == game->collectible_total)
			winning_screen(game);
		else
		{
			ft_printf("You must collect all the presents before you can leave!\n");
			ft_printf("You need [%d] collectibles. You have [%d]", game->collectible_total, game->collectible_count);
		}
	}
}

mlx_image_t	*load_texture(mlx_t *mlx, const char *path)
{
	mlx_texture_t	*tex;
	mlx_image_t		*img;

	tex = mlx_load_png(path);
	if (!tex)
		error_message("Failed to load texture");
	img = mlx_texture_to_image(mlx, tex);
	if (!img)
	{
		mlx_delete_texture(tex);
		error_message("Failed to convert texture to image");
	}
	mlx_delete_texture(tex);
	return (img);
}
void load_textures(t_game *game)
{
    game->floor = load_texture(game->mlx, "assets/snow.png");
    if (!game->floor)
		error_message("Failed to load floor texture");
    game->wall = load_texture(game->mlx, "assets/ice.png");
    if (!game->wall)
        error_message("Failed to load wall texture");
    game->exit = load_texture(game->mlx, "assets/exit64.png");
    if (!game->exit)
        error_message("Failed to load exit texture");
    game->collect = load_texture(game->mlx, "assets/collect64.png");
    if (!game->collect)
        error_message("Failed to load collect texture");
    game->player = load_texture(game->mlx, "assets/santa.png");
    if (!game->player)
        error_message("Failed to load player texture");
}

void	winning_screen(t_game *game)
{
	mlx_image_t		*img;
	mlx_texture_t	*end_texture;
	int				center_x;
	int				center_y;
	
	game->game_over = true;
	center_x = (game->w_width - 252) / 2;
	center_y = (game->w_height - 126) / 2;
	end_texture = mlx_load_png("assets/win_screen252x126.png");
	if (!end_texture)
		error_message("Failed to load winning texture\n");
	img = mlx_texture_to_image(game->mlx, end_texture);
	if (!img)
	{
		mlx_delete_texture(end_texture);
		error_message("Failed to convert texture to image\n");
	}
	mlx_image_to_window(game->mlx, img, center_x, center_y);
	// Do not delete the image immediately
	//mlx_delete_image(game->mlx, img);
	mlx_delete_texture(end_texture);
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
void	game_struct_init(t_game *game)
{
	game->mlx = NULL;
	game->move_count = 0;
	game->collectible_count = 0;
	game->collectible_total = 0;
	game->map = NULL;
	game->player_count = 0;
	game->player_pos_x  = 0;
	game->player_pos_y = 0;
	game->exit_count = 0;
	game->exit_position_x = 0;
	game->exit_position_y = 0;
	game->w_height = 0;
	game->w_width = 0;
	game->game_over = false;
	game->image = NULL;
	game->map_x = 0;
	game->map_y = 0;
	// Initialize collect_images array
	for (int i = 0; i < MAX_MAP_HEIGHT; i++)
		for (int j = 0; j < MAX_MAP_WIDTH; j++)
			game->collect_images[i][j] = NULL;
}

int	free_map(t_game *game)
{
	int i = 0;
	while (game->map[i] != NULL)
	{
		free(game->map[i]);
		i++;
	}
	free(game->map);
	return (EXIT_SUCCESS);
}

void	clean_images(t_game *game)
{
	if (game->floor)
		mlx_delete_image(game->mlx, game->floor);
	if (game->wall)
		mlx_delete_image(game->mlx, game->wall);
	if (game->exit)
		mlx_delete_image(game->mlx, game->exit);
	if (game->collect)
		mlx_delete_image(game->mlx, game->collect);
	if (game->player)
		mlx_delete_image(game->mlx, game->player);
	if (game->image)
		mlx_delete_image(game->mlx, game->image);
}

int32_t main(int argc, char **argv)
{
	t_game game;
	
	ft_printf("initializing game struct..\n");
	game_struct_init(&game);
	ft_printf("initialized game struct!\n");
	
	ft_printf("Validating map file...\n");
	check_map_file(argc, argv);
	ft_printf("Map validated!\n");
	
	ft_printf("Reading game map..\n");
	game.map = read_map(argv[1]);
	if (!game.map)
		error_message("The map is null\n");
	ft_printf("Map read!\n");
	
	ft_printf("validating game elements..\n");
	validate_map_elements(&game);
	ft_printf("game elements validated!\n");
	
	ft_printf("Getting window height..\n");
	game.w_height = get_w_height(game.map);
	ft_printf("window height!\n");
	
	ft_printf("Getting window width..\n");
	game.w_width = get_w_width(game.map);
	ft_printf("Window height!\n");
	
	ft_printf("Initializing MLX42..\n");
	start_mlx_window(&game);
	ft_printf("MLX42 initialized!\n");

	ft_printf("Loading textures..\n");
    load_textures(&game);
    ft_printf("Textures loaded!\n");

	ft_printf("Placing map..\n");
	place_map(&game);
	ft_printf("Map placed!\n");
	
	ft_printf("Placing collectibles..\n");
	place_collectibles(&game);
	ft_printf("collectibles placed!\n");
	
	ft_printf("Placing exit..\n");
	place_exit(&game);
	ft_printf("Exit placed!\n");
	
	ft_printf("Placing player..\n");
	place_player(&game);
	ft_printf("Player placed!\n");
	
	ft_printf("Running key hook..\n");
	mlx_key_hook(game.mlx, &key_handler, &game);
	ft_printf("Key hook!\n");
	
	ft_printf("Placing text on screen\n");
	text(game.mlx);
	ft_printf("Text placed!\n");
	
	ft_printf("Running mlx loop\n");
	mlx_loop(game.mlx);
	ft_printf("Loop worked!\n");
	
	clean_images(&game);
	
	ft_printf("Terminating MLX..\n");
	mlx_terminate(game.mlx);
	ft_printf("MLX terminated!\n");
	
	ft_printf("Freeing map..\n");
	free_map(&game);
	ft_printf("Map freed!\n");
}
