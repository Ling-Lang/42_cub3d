/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 13:06:22 by jkulka            #+#    #+#             */
/*   Updated: 2024/01/10 15:32:46 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"


int get_rgba(int r, int g, int b, int a)
{
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
