/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_load.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 10:42:04 by jkulka            #+#    #+#             */
/*   Updated: 2024/01/11 10:44:34 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int ft_load_textures(t_data *data)
{
    
    data->textures = ft_calloc(5, sizeof * data->textures);
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
