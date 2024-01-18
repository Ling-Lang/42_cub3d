/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_raycasting.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:14:15 by jkulka            #+#    #+#             */
/*   Updated: 2024/01/18 13:54:18 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void		ft_get_side(t_data *data, t_ray *ray);

static void	init_raycast(int x, t_ray *ray, t_data *data)
{
	ray_init(ray);
	ray->camera_x = 2 * x / (double)WIN_WIDTH - 1;
	ray->dir_x = data->player.dir_x + data->player.plane_x * ray->camera_x;
	ray->dir_y = data->player.dir_y + data->player.plane_y * ray->camera_x;
	ray->map_x = (int)data->player.pos_x / 64;
	ray->map_y = (int)data->player.pos_y / 64;
	ray->deltadist_x = fabs(1 / ray->dir_x);
	ray->deltadist_y = fabs(1 / ray->dir_y);
}

int	calc_for_y(float big, float small)
{
	int	y;

	y = 0;
	y = fabs((small / big) * 64);
	return (y);
}

int	get_color2(int x, int y, mlx_image_t *img)
{
	int	i;

	i = (y * img->width + x) * 4;
	return (get_rgba(img->pixels[i], img->pixels[i + 1], img->pixels[i + 2],
			img->pixels[i + 3]));
}

void	ft_putpixel_color(t_data *data, t_ray *ray, int x)
{
	int	y;
	int	color;
	int	tex_y;
	int	tex_x;

	ft_get_side(data, ray);
	data->texinfo.x = (int)(ray->wall_x * (double)(data->texinfo.size));
	if ((ray->side == 0 && ray->dir_x > 0) || (ray->side == 1
			&& ray->dir_y < 0))
		data->texinfo.x = data->texinfo.size - data->texinfo.x - 1;
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		tex_y = ((y - ray->draw_start)
				* data->textures[data->texinfo.side]->height)
			/ ray->line_height;
		tex_x = data->texinfo.x % data->textures[data->texinfo.side]->width;
		color = get_color2(tex_x, tex_y, data->textures[data->texinfo.side]);
		mlx_put_pixel(data->img, x, y, color);
		y++;
	}
}

void	raycast(t_data *data)
{
	int		x;
	t_ray	ray;

	ray = data->ray;
	x = -1;
	while (++x < WIN_WIDTH)
	{
		init_raycast(x, &ray, data);
		set_dda(&ray, data);
		do_dda(&ray, data);
		calc_height(&ray, data);
		if (x + 1 < WIN_WIDTH && ray.draw_start >= 0
			&& ray.draw_end < WIN_HEIGHT)
			ft_putpixel_color(data, &ray, x + 1);
	}
}
