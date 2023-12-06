/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 12:45:20 by jkulka            #+#    #+#             */
/*   Updated: 2023/12/06 17:17:44 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

#define WIDTH 640
#define HEIGHT 480

// Exit the program as failure.
static void ft_error(void)
{
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

// Print the window width and height.

void cast(t_data *data)
{
    double rayAngle = data->angle - data->halfFov;
    for(int rayCount = 0; rayCount < data->width; rayCount++)
    {   
        t_float_point ray;
        ray.x = data->x;
        ray.y = data->y;       
        double rayCos = cos(degreeToRadian(rayAngle)) / data->detail;
        double raySin = sin(degreeToRadian(rayAngle)) / data->detail;
        // printf("%f\n", rayCos);
        int wall = 0;
        while(wall == 0)
        {
            ray.x += rayCos;
            ray.y += raySin;
            wall = data->map[(int)floor(ray.y)][(int)floor(ray.x)];
        }
        double distance = sqrt(pow(data->x - ray.x, 2) + pow(data->y - ray.y, 2));
        // printf("%lf\n", distance * cos(degreeToRadian(rayAngle - data->angle)));
        // printf("%lf\n", ray.x);
        double wallHeight = floor(data->halfH / distance);
        printf("\t%d\n", data->height);
        ft_putline_alt(data,rayCount, 0, rayCount, data->halfH - wallHeight, get_rgba(0, 0, 255, 255));
        ft_putline_alt(data, rayCount, data->halfH - wallHeight, rayCount, data->halfH + wallHeight, get_rgba(255, 0, 0, 255));
        ft_putline_alt(data, rayCount, data->halfH + wallHeight, rayCount, data->height, get_rgba(0, 255, 0, 255));
        rayAngle += data->incrementAngle;
    }
}
void clear_screen(t_data *data)
{
    // mlx_clear_window(data->mlx, data->win); // Clear the window
    // mlx_destroy_image(data->mlx, data->img); // Destroy the previous image
    mlx_delete_image(data->mlx, data->img);
    data->img = mlx_new_image(data->mlx, data->width, data->height); // Create a new image buffer
    mlx_image_to_window(data->mlx, data->img, 0, 0);
}
void	ft_hook(void *param)
{
	// mlx_t	*mlx;
    t_data *data;
    data = param;
    usleep(data->delay * 500);
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
    // data->x += 1;
    ft_clear(data);
    cast(data);
}
void key_hook(mlx_key_data_t keydatam, void *param)
{
    t_data *data;
    data = param;

    if(mlx_is_key_down(data->mlx, MLX_KEY_W))
    {
        double playerCos = cos(degreeToRadian(data->angle)) * data->speed;
        double playerSin = sin(degreeToRadian(data->angle)) * data->speed;
        double newX = data->x + playerCos;
        double newY = data->y + playerSin;
        // printf("newX: %lf\n", playerCos);
        if(data->map[(int)(newY + 0.5)][(int)(newX + 0.5)] == 0){
            data->x = (int)newX;
            data->y = (int)newY;   
        }
        return ;
    }
    else if(mlx_is_key_down(data->mlx, MLX_KEY_S))
    {
        double playerCos = cos(degreeToRadian(data->angle)) * data->speed;
        double playerSin = sin(degreeToRadian(data->angle)) * data->speed;
        double newX = data->x - playerCos;
        double newY = data->y - playerSin;
        // printf("newX: %lf\n", playerCos);
        if(data->map[(int)(newY + 0.5)][(int)(newX + 0.5)] == 0){
            data->x = (int)newX;
            data->y = (int)newY;   
        }
        return ;

    }
    else if(mlx_is_key_down(data->mlx, MLX_KEY_A))
        data->angle -= data->rot;
    else if(mlx_is_key_down(data->mlx, MLX_KEY_D))
        data->angle += data->rot;
}
int	main(void)
{
    t_data data;
    data.height = 480;
    data.width = 640;
    data.halfH = data.height / 2;
    data.halfW = data.width / 2;
    data.fov = 60;
    data.halfFov = data.fov / 2;
    data.detail = 64;
    data.x = 2;
    data.y = 2;
    data.angle = 90;
    data.incrementAngle = data.fov / data.width;
    data.delay = 50;
    data.speed = 1;
    data.rot = 5.0;
    int initial_map[10][10] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 1, 1, 0, 1, 0, 0, 1},
    {1, 0, 0, 1, 0, 0, 1, 0, 0, 1},
    {1, 0, 0, 1, 0, 0, 1, 0, 0, 1},
    {1, 0, 0, 1, 0, 1, 1, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    };
    t_data data_instance;
    ft_memcpy(data.map, initial_map, sizeof(initial_map));
	data.mlx = mlx_init(640, HEIGHT, "cub3d", false);
	if (!data.mlx)
		ft_error();
	data.img = mlx_new_image(data.mlx, data.width, data.height);
	if (!data.img || (mlx_image_to_window(data.mlx, data.img, 0, 0) < 0))
		ft_error();
	mlx_loop_hook(data.mlx, ft_hook, &data);
    mlx_key_hook(data.mlx, key_hook, &data);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	return (EXIT_SUCCESS);
}