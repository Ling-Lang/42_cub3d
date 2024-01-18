/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_raycasting.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:14:15 by jkulka            #+#    #+#             */
/*   Updated: 2024/01/18 10:47:37 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
void ft_get_side(t_data *data, t_ray *ray);
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

int     calc_for_y(float big, float small)
{
    int y = 0;

    y = fabs((small / big) * 64);
    return (y);
}

int get_color2(int x, int y, mlx_image_t *img)
{
    int i = (y * img->width + x) * 4; // Multiply by 4 because each pixel is represented by 4 elements
    int r = img->pixels[i];
    int g = img->pixels[i + 1];
    int b = img->pixels[i + 2];
    int a = img->pixels[i + 3];
    return get_rgba(r, g, b, a);
}

void ft_putpixel_color(t_data *data, t_ray *ray, int x)
{
    int y;
    int color;

    ft_get_side(data, ray);
    data->texinfo.x = (int)(ray->wall_x * (double)(data->texinfo.size));
    if((ray->side == 0 && ray->dir_x > 0)
        || (ray->side == 1 && ray->dir_y < 0))
        data->texinfo.x = data->texinfo.size - data->texinfo.x - 1;
    data->texinfo.step = 1.0 * data->texinfo.size / ray->line_height;
    data->texinfo.pos = (ray->draw_start - WIN_HEIGHT / 2 + ray->line_height / 2) * data->texinfo.step;
    y = ray->draw_start;
    while(y < ray->draw_end)
    {
        // Calculate tex_y based on the current y value
        int tex_y = ((y - ray->draw_start) * data->textures[data->texinfo.side]->height) / ray->line_height;
        int tex_x = data->texinfo.x % data->textures[data->texinfo.side]->width;

        color = get_color2(tex_x, tex_y, data->textures[data->texinfo.side]);
        mlx_put_pixel(data->img, x, y, color);
        y++;
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
            ft_putpixel_color(data, &ray, x + 1);
            // int color;
            // if(ray.side == 0)
            //     color = get_rgba(255, 0, 0, 255);
            // else
            //     color = get_rgba(0, 0, 255, 255);
            // ft_get_side(data, &ray);
            // drawThickLine(data, x + 1, ray.draw_start, ray.draw_end, color);
        }
    }
    return ;
}
