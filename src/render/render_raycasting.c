/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_raycasting.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:14:15 by jkulka            #+#    #+#             */
/*   Updated: 2024/01/16 12:43:32 by jkulka           ###   ########.fr       */
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

void drawThickLine(t_data *data, int x, int y1, int y2, int color)
{
    if((x > 0 && x < WIN_WIDTH) && (y1 > 0 && y1 < WIN_HEIGHT) && (y2 > 0 && y2 < WIN_HEIGHT))
    {
        while(y1 < y2)
        {
            mlx_put_pixel(data->img, x, y1, color);
            y1++;
        }
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
        if(x + 1< WIN_WIDTH && ray.draw_start >= 0 && ray.draw_end < WIN_HEIGHT)
        {
            int color;
            if(ray.side == 0)
                color = get_rgba(255, 0, 0, 255);
            else
                color = get_rgba(0, 0, 255, 255);
            drawThickLine(data, x + 1, ray.draw_start, ray.draw_end, color);
        }
    }
    return ;
}
