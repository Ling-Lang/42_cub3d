/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_textures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:14:41 by jkulka            #+#    #+#             */
/*   Updated: 2024/01/18 10:53:51 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void calc_height(t_ray *ray, t_data *data)
{
    if(ray->side == 0)
        ray->wall_dist = (ray->sidedist_x - ray->deltadist_x);
    else
        ray->wall_dist = (ray->sidedist_y - ray->deltadist_y);
    ray->line_height = (int)(WIN_HEIGHT / ray->wall_dist);
    ray->draw_start = -(ray->line_height) / 2 + WIN_HEIGHT / 2;
    if(ray->draw_start < 0)
        ray->draw_start = 0;
    ray->draw_end = ray->line_height / 2 + WIN_HEIGHT / 2;
    if(ray->draw_end >= WIN_HEIGHT)
        ray->draw_end = WIN_HEIGHT - 1;
    if(ray->side == 0)
        ray->wall_x = (data->player.pos_y / 64) + ray->wall_dist * ray->dir_y;
    else
        ray->wall_x = (data->player.pos_x / 64) + ray->wall_dist * ray->dir_x;
    ray->wall_x -= floor(ray->wall_x); 
    // printf("\twall_dist: %f\n\tline_height: %d\n\tdraw_start: %d\n\tdraw_end: %d\n\twall_x: %f\n\n",
    // ray->wall_dist, ray->line_height, ray->draw_start, ray->draw_end, ray->wall_x);
}

// void ft_get_side(t_data *data, t_ray *ray)
// {
//     if(ray->side == 1)
//     {
//         if(ray->dir_x > 0)
//             data->texinfo.side = EAST;
//         else
//             data->texinfo.side = WEST;
//     }
//     else
//     {
//         if(ray->dir_y > 0)
//             data->texinfo.side = NORTH;
//         else
//             data->texinfo.side = SOUTH;
//     }
// }

void ft_get_side(t_data *data, t_ray *ray)
{
    if(ray->side == 0) // The ray hit the east or west side of a wall
    {
        if(ray->dir_x > 0)
            data->texinfo.side = EAST;
        else
            data->texinfo.side = WEST;
    }
    else // The ray hit the north or south side of a wall
    {
        if(ray->dir_y > 0)
            data->texinfo.side = NORTH;
        else
            data->texinfo.side = SOUTH;
    }
}