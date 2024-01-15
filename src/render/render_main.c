/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:17:09 by jkulka            #+#    #+#             */
/*   Updated: 2024/01/15 15:56:54 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int ft_render(t_data *data, bool direct)
{
    if(direct == true)
    {
        // malloc_textures
        // ray_init(&data->ray);
        raycast(data);
        ft_printf("Hurra!!!\n");
        return 1;
    }
    if(data->player.has_moved == true)
    {
        ft_clear(data);
        raycast(data);
    }
}