/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 13:06:22 by jkulka            #+#    #+#             */
/*   Updated: 2024/01/11 14:01:31 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"


int get_rgba(int r, int g, int b, int a)
{
	// ft_printf("\tr:%d g:%d b:%d a:%d\n", r, g, b, a);
    return (r << 24 | g << 16 | b << 8 | a);
}

void ft_clear(t_data *data)
{
	int i = 0;
	int j = 0;
	while(i < WIN_HEIGHT)
	{
		while(j < WIN_WIDTH)
		{
			mlx_put_pixel(data->img, j, i, get_rgba(255, 255, 255, 255));
			j++;
		}
		j = 0;
		i++;
	}
}

// void	ft_putline(mlx_image_t *img, int x1, int y1,int x2, int y2, int color)
// {
// 	int temp_x = x1;
// 	int temp_y = y1;
// 	while (temp_x != x2 || temp_y != y2)
// 	{
// 		mlx_put_pixel(img, temp_x, temp_y, color);
// 		if(y1 < y2)
// 			temp_y += 1;
// 		if(y1 > y2)
// 			temp_y -= 1;
// 		if(x1 < x2)
// 			temp_x += 1;
// 		if(x1 > x2)
// 			temp_x -= 1;		
// 	}
// }