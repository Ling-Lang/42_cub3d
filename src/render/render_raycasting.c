/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_raycasting.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:14:15 by jkulka            #+#    #+#             */
/*   Updated: 2024/01/15 12:57:20 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void init_raycast(int x, t_ray *ray, t_data *data)
{
    ray_init(ray);
    ray->camera_x = 2 * x / (double)WIN_WIDTH - 1;
    ray->dir_x = data->player.dir_x + data->player.plane_x * ray->camera_x;
    ray->dir_y = data->player.dir_y + data->player.plane_y * ray->camera_x;
    ray->map_x = (int)data->player.pos_x;
    ray->map_y = (int)data->player.pos_y;
    ray->deltadist_x = fabs(1 / ray->dir_x);   
    ray->deltadist_y = fabs(1 / ray->dir_y);
    printf("\tcamera_x: %f\n\tdir_x: %f\n\tdir_y%f\n\tmap_x (int): %d\n\tmap_y (int): %d\n\tdeltadist_x: %f\n\tdeltadist_y: %f\n\n",
    ray->camera_x, ray->dir_x, ray->dir_x, ray->map_x, ray->map_y, ray->deltadist_x, ray->deltadist_y);
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
        //set_dda
        // do dda
        // line height?
        // textures
    }
    return ;
    
}