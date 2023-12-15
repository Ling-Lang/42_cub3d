/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 13:06:22 by jkulka            #+#    #+#             */
/*   Updated: 2023/12/15 13:01:15 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"


int get_rgba(int r, int g, int b, int a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

void	ft_putline(t_data *data, t_point *p1, t_point* p2, int color)
{
	int tmp_x = p1->x;
	int tmp_y = p1->y;
	while (tmp_x != p2->x)
	{
		mlx_put_pixel(data->img, tmp_x, tmp_y, color);
		if(p1->y < p2->y)
			tmp_y += 1;
		if(p1->y > p2->y)
			tmp_y -= 1;
		if(p1->x < p2->x)
			tmp_x += 1;
		if(p1->x > p2->x)
			tmp_x -= 1;		
	}
}

void ft_putline_alt(t_data *data, int x0, int y0, int x1, int y1, int color) 
{
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = x0 < x1 ? 1 : -1;
    int sy = y0 < y1 ? 1 : -1;
    int err = (dx > dy ? dx : -dy) / 2;
    int e2;
	// ft_printf("x1: %d\ty1: %d\tx2: %d\ty2: %d\n", x0, y0, x1, y1);
    while (x0 != x1 || y0 != y1) {
        mlx_put_pixel(data->img, x0, y0, color);
        e2 = err;
        if (e2 > -dx) {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dy) {
            err += dx;
            y0 += sy;
        }
    }
}

void ft_clear(t_data *data)
{
	int i = 0;
	int j = 0;
	while(i < data->height)
	{
		while(j < data->width)
		{
			mlx_put_pixel(data->img, j, i, get_rgba(255, 255, 255, 255));
			j++;
		}
		j = 0;
		i++;
	}
}