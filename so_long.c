/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojornod <rojornod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 15:04:42 by rojornod          #+#    #+#             */
/*   Updated: 2024/12/17 16:14:01 by rojornod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//include the right library
#include "mlx42/include/MLX42/MLX42.h"
#include <stdlib.h>
#include <stdio.h>

//specify window size
#define WIDTH 800
#define HEIGHT 600

static mlx_image_t	*g_img;

void	key_handler(mlx_key_data_t keydata, void *param)
{
	if ((keydata.key == MLX_KEY_ESCAPE
			|| keydata.key == MLX_KEY_ENTER) && keydata.action == MLX_PRESS)
		mlx_close_window(param);
	if (keydata.key == MLX_KEY_1 && keydata.action == MLX_PRESS)
		puts("Hello");
	if (keydata.key == MLX_KEY_2 && keydata.action == MLX_RELEASE)
		puts("World");
	if (keydata.key == MLX_KEY_3 && keydata.action == MLX_REPEAT)
		puts("!!!");
}

void my_scrollhook(double xdelta, double ydelta, void* param)
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
		mlx_delete_image(mlx, g_img);
	for (int x = 0; x < g_img->width; x++)
		for(int y= 0; y < g_img->height; y++)
			mlx_put_pixel(g_img, x, y, rand() % RAND_MAX);
}


int32_t	main(void)
{
	mlx_t	*mlx;

	if (!(mlx = mlx_init(WIDTH, HEIGHT, "MLX42 Example", true)))
	{
		puts(mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
	mlx_key_hook(mlx, &key_handler, mlx);
	mlx_scroll_hook(mlx, &my_scrollhook, NULL);
	g_img = mlx_new_image(mlx, 128, 128);
	mlx_image_to_window(mlx, g_img, 0, 0);
	mlx_loop_hook(mlx, &hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
