/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_mlx.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 10:56:50 by rmarquar          #+#    #+#             */
/*   Updated: 2024/01/12 16:02:15 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"


void	init_mlx(t_data *data)
{
	data->mlx = mlx_init(1920, 1080, "Test", false);
	if(!data->mlx)
		ft_error(MLX);
    data->img = mlx_new_image(data->mlx, 1920, 1080);
	return ;
}
