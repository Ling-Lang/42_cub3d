/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_dda.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:14:30 by jkulka            #+#    #+#             */
/*   Updated: 2024/01/15 15:12:50 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"


void do_dda(t_ray *ray, t_data *data)
{
    int hit;
    hit = 0;
    while(hit == 0)
    {
        if(ray->sidedist_x < ray->sidedist_y)
        {
            ray->sidedist_x += ray->deltadist_x;
            ray->map_x += ray->step_x;
            ray->side = 0;
        }
        else
        {
            // ft_printf("\t%d;%d\n", ray->map_x, ray->map_y);
            ray->sidedist_y += ray->deltadist_y;
            ray->map_y += ray->step_y;
            ray->side = 1;
        }
        if(data->mapinfo.map[ray->map_y][ray->map_x] == '1')
        {
            ft_printf("WAND!\n");
            hit = 1;
        }
    }
}

    //   //perform DDA
    //   while (hit == 0)
    //   {
    //     //jump to next map square, either in x-direction, or in y-direction
    //     if (sideDistX < sideDistY)
    //     {
    //       sideDistX += deltaDistX;
    //       mapX += stepX;
    //       side = 0;
    //     }
    //     else
    //     {
    //       sideDistY += deltaDistY;
    //       mapY += stepY;
    //       side = 1;
    //     }
    //     //Check if ray has hit a wall
    //     if (worldMap[mapX][mapY] > 0) hit = 1;
    //   } 

void set_dda(t_ray *ray, t_data *data)
{
    if(ray->dir_x < 0)
    {
        ray->step_x = -1;
        ray->sidedist_x = ((data->player.pos_x / 64) - ray->map_x) * ray->deltadist_x;
    }
    else
    {
        ray->step_x = 1;
        ray->sidedist_x = (ray->map_x + 1.0 - (data->player.pos_x / 64)) * ray->deltadist_x;
    }
    if(ray->dir_y < 0)
    {
        ray->step_y = -1;
        ray->sidedist_y = ((data->player.pos_x / 64) - ray->map_x) * ray->deltadist_y;
    }
    else
    {
        ray->step_y = 1;
        ray->sidedist_y = (ray->map_y + 1.0 - (data->player.pos_y / 64)) * ray->deltadist_y;
    }
    // printf("\tsidedist_x: %f\n\tsidedist_y: %f\n", ray->sidedist_x, ray->sidedist_y);
}
