/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 13:18:03 by jkulka            #+#    #+#             */
/*   Updated: 2024/01/22 13:32:11 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	main_hook(void *v_data)
{
	t_data	*data;

	data = v_data;
	mlx_get_mouse_pos(data->mlx, &(data->player.m_x), &(data->player.m_y));
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		ft_close(data);
	if (data->player.has_moved == true)
		ft_render(data, 0);
	mlx_set_mouse_pos(data->mlx, WIN_WIDTH / 2, WIN_HEIGHT / 2);
	mlx_set_cursor_mode(data->mlx, MLX_MOUSE_HIDDEN);
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
	if (WIN_WIDTH / 2 != data->player.m_x && data->player.spawn == false)
	{
		rotspeed = ((data->player.m_x) - WIN_WIDTH / 2.0) / (WIN_WIDTH / 2.0)
			* (data->player.rotate * 40);
		ft_rotate(data, rotspeed);
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT) || mlx_is_key_down(data->mlx,
			MLX_KEY_Q))
	{
		rotspeed = data->player.rotate * -1;
		ft_rotate(data, rotspeed);
		data->player.spawn = false;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT) || mlx_is_key_down(data->mlx,
			MLX_KEY_E))
	{
		rotspeed = data->player.rotate * 1;
		ft_rotate(data, rotspeed);
		data->player.spawn = false;
	}
}
