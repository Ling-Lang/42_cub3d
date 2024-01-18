/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:17:09 by jkulka            #+#    #+#             */
/*   Updated: 2024/01/18 13:52:38 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	draw_thick_line(t_data *data, int y, int x1, int x2)
{
	if ((y > 0 && y < WIN_HEIGHT) && (x1 > 0 && x1 < WIN_WIDTH) && (x2 > 0
			&& x2 < WIN_WIDTH))
	{
		while (x1 < x2)
		{
			mlx_put_pixel(data->img, x1, y, data->color);
			x1++;
		}
	}
}

void	draw_floor(t_data *data)
{
	int	y;
	int	y2;

	y = WIN_HEIGHT / 2;
	y2 = y;
	while (y > 0)
	{
		data->color = data->colors[CEILING];
		draw_thick_line(data, y, 1, WIN_WIDTH - 1);
		y--;
	}
	while (y2 < WIN_HEIGHT)
	{
		data->color = data->colors[FLOOR];
		draw_thick_line(data, y2, 1, WIN_WIDTH - 1);
		y2++;
	}
}

void	ft_render(t_data *data, bool direct)
{
	if (direct == true)
	{
		draw_floor(data);
		raycast(data);
	}
	if (data->player.has_moved == true)
	{
		ft_clear(data);
		draw_floor(data);
		raycast(data);
		data->player.has_moved = false;
	}
}
