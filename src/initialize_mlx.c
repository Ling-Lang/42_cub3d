/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_mlx.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarquar <rmarquar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 10:56:50 by rmarquar          #+#    #+#             */
/*   Updated: 2024/01/09 11:08:59 by rmarquar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/cub3d.h"

void	init_mlx(t_data *data)
{
	data->mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "This is cub3d from Jens and Robin", true);
	data->win = mlx_new_window(data->mlx, WIN_WIDTH, WIN_HEIGHT, "This is cub3d from Jens and Robin");
	return ;
}
