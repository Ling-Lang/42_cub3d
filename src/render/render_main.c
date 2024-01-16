/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:17:09 by jkulka            #+#    #+#             */
/*   Updated: 2024/01/16 12:57:53 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void drawThickLine(t_data *data, int y, int x1, int x2, int color)
{
    if((y > 0 && y < WIN_HEIGHT) && (x1 > 0 && x1 < WIN_WIDTH) && (x2 > 0 && x2 < WIN_WIDTH))
    {
        while(x1 < x2)
        {
            mlx_put_pixel(data->img, x1, y, color);
            x1++;
        }
    }
}

void draw_floor(t_data *data)
{
    int y = WIN_HEIGHT / 2;
    int y2 = WIN_HEIGHT / 2;
    int i = 0;
    while(y > 0)
    {
        drawThickLine(data, y, 1, WIN_WIDTH - 1, data->colors[CEILING]);
        y--;
    }
    while(y2 < WIN_HEIGHT)
    {
        drawThickLine(data, y2, 1, WIN_WIDTH - 1, data->colors[FLOOR]);
        y2++;
    }
    
}

int ft_render(t_data *data, bool direct)
{
    if(direct == true)
    {
        draw_floor(data);
        raycast(data);
        ft_printf("Hurra!!!\n");
        return 1;
    }
    if(data->player.has_moved == true)
    {
        ft_clear(data);
        draw_floor(data);
        raycast(data);
        data->player.has_moved = false;
    }
    return 1;
}