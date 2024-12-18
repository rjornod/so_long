/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojornod <rojornod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 15:04:42 by rojornod          #+#    #+#             */
/*   Updated: 2024/12/18 16:55:33 by rojornod         ###   ########.fr       */
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
static mlx_image_t	*a_img;
static mlx_image_t	*c_img;
static mlx_image_t	*b_img;
static mlx_image_t *cat_img;

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
	//checks if g_img is not null before accessing it
	if (g_img)
    {
        for (int x = 0; x < g_img->width; x++)
            for (int y = 0; y < g_img->height; y++)
                mlx_put_pixel(g_img, x, y, 0xFF0000FF);
    }
	for (int x = 0; x < a_img->width; x++)
		for(int y= 0; y < a_img->height; y++)
			mlx_put_pixel(a_img, x, y, 0x000080ff);
	for (int x = 0; x < b_img->width; x++)
		for(int y= 0; y < b_img->height; y++)
			mlx_put_pixel(b_img, x, y, 0xff00ff80);
	for (int x = 0; x < c_img->width; x++)
		for(int y= 0; y < c_img->height; y++)
			mlx_put_pixel(c_img, x, y, 0xff000080);
			
	//checks if g_img is not null before modifying its instances
	// if (g_img)
    // {	
	// 	if (mlx_is_key_down(param, MLX_KEY_UP))
	// 		g_img->instances[0].y -= 15;
	// 	if (mlx_is_key_down(param, MLX_KEY_DOWN))
	// 		g_img->instances[0].y += 15;
	// 	if (mlx_is_key_down(param, MLX_KEY_LEFT))
	// 		g_img->instances[0].x -= 15;
	// 	if (mlx_is_key_down(param, MLX_KEY_RIGHT))
	// 		g_img->instances[0].x += 15;
	// }
	if (mlx_is_key_down(mlx, MLX_KEY_W))
        cat_img->instances[0].y -= 15;
    if (mlx_is_key_down(mlx, MLX_KEY_S))
        cat_img->instances[0].y += 15;
    if (mlx_is_key_down(mlx, MLX_KEY_A))
        cat_img->instances[0].x -= 15;
    if (mlx_is_key_down(mlx, MLX_KEY_D))
        cat_img->instances[0].x += 15;
		
	mlx_put_string(mlx, "Hello, World!", 0, 0);

}

void	movement(void *param)
{
	mlx_t	*mlx;

	mlx = param;
	
}


int32_t	main(void)
{
	mlx_t	*mlx;

	if (!(mlx = mlx_init(WIDTH, HEIGHT, "MLX42 TESTING", false)))
	{
		puts(mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}


	mlx_key_hook(mlx, &key_handler, mlx);
	mlx_scroll_hook(mlx, &my_scrollhook, NULL);
	a_img = mlx_new_image(mlx, 400, 300);
	b_img = mlx_new_image(mlx, 400, 300);
	c_img = mlx_new_image(mlx, 400, 300);
	g_img = mlx_new_image(mlx, 400, 300);

	printf("g_img: %p\n", g_img);
    printf("a_img: %p\n", a_img);
    printf("b_img: %p\n", b_img);
    printf("c_img: %p\n", c_img);
	
	mlx_image_to_window(mlx, a_img, 400, 0);
	mlx_image_to_window(mlx, b_img, 0, 300);
	mlx_image_to_window(mlx, c_img, 400, 300);
	mlx_image_to_window(mlx, g_img, 0, 0);
	
	//loads texture
	mlx_texture_t* texture = mlx_load_png("assets/cat.png");
	cat_img = mlx_texture_to_image(mlx, texture);
	if (!cat_img)
	perror("error");
	mlx_image_to_window(mlx, cat_img, 40,40);

		
	mlx_loop_hook(mlx, &hook, mlx);
	mlx_loop(mlx);

	mlx_delete_image(mlx, cat_img);
	mlx_delete_texture(texture);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
