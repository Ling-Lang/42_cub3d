/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_load.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 10:42:04 by jkulka            #+#    #+#             */
/*   Updated: 2024/01/11 16:26:27 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int ft_load_textures(t_data *data)
{
    // ft_printf("\t%s\n", data->texinfo.north);
    // ft_printf("\t%s\n", data->texinfo.south);
    // ft_printf("\t%s\n", data->texinfo.west);
    // ft_printf("\t%s\n", data->texinfo.east);
	data->textures[NORTH] = mlx_texture_to_image(data->mlx,
			mlx_load_png(data->texinfo.north));
	data->textures[SOUTH] = mlx_texture_to_image(data->mlx,
			mlx_load_png(data->texinfo.south));
	data->textures[WEST] = mlx_texture_to_image(data->mlx,
			mlx_load_png(data->texinfo.west));
	data->textures[EAST] = mlx_texture_to_image(data->mlx,
			mlx_load_png(data->texinfo.east));
    return 1;
}

int ft_load_colors(t_data *data)
{
    data->colors = ft_calloc(2, sizeof(int));
	data->colors[FLOOR] = ft_get_color(data->texinfo.floor);
	data->colors[CEILING] = ft_get_color(data->texinfo.ceiling);
    return 1;
}
