/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 13:18:03 by jkulka            #+#    #+#             */
/*   Updated: 2024/01/19 13:26:33 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	main_hook(void *v_data)
{
	t_data	*data;

	data = v_data;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		ft_close(data);
	if (data->player.has_moved == true)
		ft_render(data, 0);
}

void	move_hook(void *v_data)
{
	t_data	*data;

	data = v_data;
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
		ft_move_forward(data);
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
		ft_move_backwards(data);
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
	{
		if (data->player.dir == 'E' || data->player.dir == 'W')
			ft_move_left(data);
		else
			ft_move_right(data);
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
	{
		if (data->player.dir == 'E' || data->player.dir == 'W')
			ft_move_right(data);
		else
			ft_move_left(data);
	}
}

void	rotate_hook(void *v_data)
{
	t_data	*data;
	double	rotspeed;

	data = v_data;
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT) || mlx_is_key_down(data->mlx,
			MLX_KEY_Q))
	{
		if (data->player.dir == 'E' || data->player.dir == 'W')
			rotspeed = data->player.rotate * 1;
		else
			rotspeed = data->player.rotate * -1;
		ft_rotate(data, rotspeed);
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT) || mlx_is_key_down(data->mlx,
			MLX_KEY_E))
	{
		if (data->player.dir == 'E' || data->player.dir == 'W')
			rotspeed = data->player.rotate * -1;
		else
			rotspeed = data->player.rotate * 1;
		ft_rotate(data, rotspeed);
	}
}
