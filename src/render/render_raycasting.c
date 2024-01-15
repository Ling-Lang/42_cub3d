/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_raycasting.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:14:15 by jkulka            #+#    #+#             */
/*   Updated: 2024/01/15 15:56:03 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void init_raycast(int x, t_ray *ray, t_data *data)
{
    ray_init(ray);
    ray->camera_x = 2 * x / (double)WIN_WIDTH - 1;
    ray->dir_x = data->player.dir_x + data->player.plane_x * ray->camera_x;
    ray->dir_y = data->player.dir_y + data->player.plane_y * ray->camera_x;
    ray->map_x = (int)data->player.pos_x / 64;
    ray->map_y = (int)data->player.pos_y / 64;
    ray->deltadist_x = fabs(1 / ray->dir_x);   
    ray->deltadist_y = fabs(1 / ray->dir_y);
    // printf("\tcamera_x: %f\n\tdir_x: %f\n\tdir_y%f\n\tmap_x (int): %d\n\tmap_y (int): %d\n\tdeltadist_x: %f\n\tdeltadist_y: %f\n\n",
    // ray->camera_x, ray->dir_x, ray->dir_x, ray->map_x, ray->map_y, ray->deltadist_x, ray->deltadist_y);
}

void drawThickLine(t_data *data, int x1, int y1, int x2, int y2, int thickness, int color, bool dashed)
{
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;
    int dash_length = 10;
    int space_length = 10;
    int counter = 0;
    bool draw = true;

    while (1)
    {
        if (dashed)
        {
            if (counter % (dash_length + space_length) < dash_length)
                draw = true;
            else
                draw = false;
        }

        if (draw)
        {
            for (int i = -thickness; i <= thickness; i++)
            {
                for (int j = -thickness; j <= thickness; j++)
                {
                    if (i * i + j * j <= thickness * thickness)
                    {
                        if((x1 + i > 0 && x1 + i < WIN_WIDTH) && (y1 + j > 0 && y1 + j < WIN_HEIGHT))
                            mlx_put_pixel(data->img, x1 + i, y1 + j, color);
                    }
                }
            }
        }

        if (x1 == x2 && y1 == y2)
            break;

        int e2 = 2 * err;
        if (e2 > -dy)
        {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx)
        {
            err += dx;
            y1 += sy;
        }

        counter++;
    }
}

void raycast(t_data *data)
{
    int x;
    t_ray ray;
    
    ray = data->ray;
    x = -1;

    while(++x < WIN_WIDTH)
    {
        init_raycast(x, &ray, data);
        set_dda(&ray, data);
        do_dda(&ray, data);
        calc_height(&ray, data);
        // texture
        if(x + 1< WIN_WIDTH && ray.draw_start >= 0 && ray.draw_end < WIN_HEIGHT)
        {
            int color;
            if(ray.side == 0)
                color = get_rgba(255, 0, 0, 255);
            else
                color = get_rgba(0, 0, 255, 255);
            drawThickLine(data, x + 1, ray.draw_start, x + 1, ray.draw_end, 1, color, false);
            // mlx_put_pixel(data->img, x + 1, ray.draw_start, get_rgba(255, 0, 0, 255));
            // mlx_put_pixel(data->img, x + 1, ray.draw_end, get_rgba(255, 0, 0, 255));
            
        }
        mlx_image_to_window(data->mlx, data->img, 0, 0);
        // data->img->pixels[0];
    }
    return ;
    
}