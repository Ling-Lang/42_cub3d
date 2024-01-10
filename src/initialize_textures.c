/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_textures.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarquar <rmarquar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 10:45:53 by rmarquar          #+#    #+#             */
/*   Updated: 2024/01/10 10:54:39 by rmarquar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/cub3d.h"

void	init_textures(t_data *data)
{
	data->textures = ft_calloc(5, sizeof * data->textures);
	data->textures[NORTH] = xpm_to_img(data, data->texinfo.north);
	data->textures[SOUTH] = xpm_to_img(data, data->texinfo.south);
	data->textures[EAST] = xpm_to_img(data, data->texinfo.east);
	data->textures[WEST] = xpm_to_img(data, data->texinfo.west);
}
