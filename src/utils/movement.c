/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 13:10:39 by jkulka            #+#    #+#             */
/*   Updated: 2024/01/19 13:27:25 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	ft_move_forward(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->player.pos_x + data->player.dir_x * data->player.speed;
	new_y = data->player.pos_y + data->player.dir_y * data->player.speed;
	if (data->mapinfo.map[(int)round((new_y + 32) / 64)][(int)round((new_x + 32)
			/ 64)] != '1')
	{
		data->player.pos_y += data->player.dir_y * data->player.speed;
		data->player.pos_x += data->player.dir_x * data->player.speed;
		data->player.has_moved = true;
	}
}

void	ft_move_backwards(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->player.pos_x - data->player.dir_x * data->player.speed;
	new_y = data->player.pos_y - data->player.dir_y * data->player.speed;
	if (data->mapinfo.map[(int)round((new_y - 32) / 64)][(int)round((new_x - 32)
			/ 64)] != '1')
	{
		data->player.pos_y -= data->player.dir_y * data->player.speed;
		data->player.pos_x -= data->player.dir_x * data->player.speed;
		data->player.has_moved = true;
	}
}

void	ft_move_left(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->player.pos_x - data->player.dir_x * data->player.speed;
	new_y = data->player.pos_y + data->player.dir_y * data->player.speed;
	if (data->mapinfo.map[(int)round((new_y + 32) / 64)][(int)round((new_x + 32)
			/ 64)] != '1')
	{
		data->player.pos_x -= data->player.dir_y * data->player.speed;
		data->player.pos_y += data->player.dir_x * data->player.speed;
		data->player.has_moved = true;
	}
}

void	ft_move_right(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->player.pos_x + data->player.dir_x * data->player.speed;
	new_y = data->player.pos_y - data->player.dir_y * data->player.speed;
	if (data->mapinfo.map[(int)round((new_y + 32) / 64)][(int)round((new_x + 32)
			/ 64)] != '1')
	{
		data->player.pos_x += data->player.dir_y * data->player.speed;
		data->player.pos_y -= data->player.dir_x * data->player.speed;
		data->player.has_moved = true;
	}
}

void	ft_rotate(t_data *data, double rotspeed)
{
	double	tmp_x;

	tmp_x = data->player.dir_x;
	data->player.dir_x = data->player.dir_x * cos(rotspeed) - data->player.dir_y
		* sin(rotspeed);
	data->player.dir_y = tmp_x * sin(rotspeed) + data->player.dir_y
		* cos(rotspeed);
	tmp_x = data->player.plane_x;
	data->player.plane_x = data->player.plane_x * cos(rotspeed)
		- data->player.plane_y * sin(rotspeed);
	data->player.plane_y = tmp_x * sin(rotspeed) + data->player.plane_y
		* cos(rotspeed);
	data->player.has_moved = true;
}
