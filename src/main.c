/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 12:45:20 by jkulka            #+#    #+#             */
/*   Updated: 2024/01/18 13:56:53 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	print_controls(void)
{
	ft_printf("Controls:\nW, A, S, D for movement.\n->/Q,"
		"<-/E for rotation.\n ESC for exiting\n");
}

void	ft_close(t_data *data)
{
	mlx_close_window(data->mlx);
	free(data->colors);
	system("leaks cub3d");
	exit(EXIT_SUCCESS);
}

void	hook(void *v_data)
{
	t_data	*data;

	data = v_data;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		ft_close(data);
	if (data->player.has_moved == true)
		ft_render(data, 0);
}

void	k_hook(mlx_key_data_t key, void *v_data)
{
	t_data	*data;
	double	new_x;
	double	new_y;
	double	rotspeed;
	double	tmp_x;

	data = v_data;
	if (key.key == MLX_KEY_W)
	{
		new_x = data->player.pos_x + data->player.dir_x * data->player.speed;
		new_y = data->player.pos_y + data->player.dir_y * data->player.speed;
		if (data->mapinfo.map[(int)round((new_y + 32) / 64)][(int)round((new_x
					+ 32) / 64)] != '1')
		{
			data->player.pos_y += data->player.dir_y * data->player.speed;
			data->player.pos_x += data->player.dir_x * data->player.speed;
			data->player.has_moved = true;
		}
	}
	if (key.key == MLX_KEY_S)
	{
		new_x = data->player.pos_x - data->player.dir_x * data->player.speed;
		new_y = data->player.pos_y - data->player.dir_y * data->player.speed;
		if (data->mapinfo.map[(int)round((new_y - 32) / 64)][(int)round((new_x
					- 32) / 64)] != '1')
		{
			data->player.pos_y -= data->player.dir_y * data->player.speed;
			data->player.pos_x -= data->player.dir_x * data->player.speed;
			data->player.has_moved = true;
		}
	}
	if (key.key == MLX_KEY_A)
	{
		if (data->player.dir == 'E' || data->player.dir == 'W')
		{
			new_x = data->player.pos_x - data->player.dir_x
				* data->player.speed;
			new_y = data->player.pos_y + data->player.dir_y
				* data->player.speed;
			if (data->mapinfo.map[(int)round((new_y + 32)
						/ 64)][(int)round((new_x + 32) / 64)] != '1')
			{
				data->player.pos_x -= data->player.dir_y * data->player.speed;
				data->player.pos_y += data->player.dir_x * data->player.speed;
				data->player.has_moved = true;
			}
		}
		else
		{
			new_x = data->player.pos_x + data->player.dir_x
				* data->player.speed;
			new_y = data->player.pos_y - data->player.dir_y
				* data->player.speed;
			if (data->mapinfo.map[(int)round((new_y + 32)
						/ 64)][(int)round((new_x + 32) / 64)] != '1')
			{
				data->player.pos_x += data->player.dir_y * data->player.speed;
				data->player.pos_y -= data->player.dir_x * data->player.speed;
				data->player.has_moved = true;
			}
		}
	}
	if (key.key == MLX_KEY_D)
	{
		if (data->player.dir == 'E' || data->player.dir == 'W')
		{
			new_x = data->player.pos_x + data->player.dir_x
				* data->player.speed;
			new_y = data->player.pos_y - data->player.dir_y
				* data->player.speed;
			if (data->mapinfo.map[(int)round((new_y + 32)
						/ 64)][(int)round((new_x + 32) / 64)] != '1')
			{
				data->player.pos_x += data->player.dir_y * data->player.speed;
				data->player.pos_y -= data->player.dir_x * data->player.speed;
				data->player.has_moved = true;
			}
		}
		else
		{
			new_x = data->player.pos_x - data->player.dir_x
				* data->player.speed;
			new_y = data->player.pos_y + data->player.dir_y
				* data->player.speed;
			if (data->mapinfo.map[(int)round((new_y + 32)
						/ 64)][(int)round((new_x + 32) / 64)] != '1')
			{
				data->player.pos_x -= data->player.dir_y * data->player.speed;
				data->player.pos_y += data->player.dir_x * data->player.speed;
				data->player.has_moved = true;
			}
		}
	}
	if (key.key == MLX_KEY_LEFT || key.key == MLX_KEY_Q)
	{
		tmp_x = data->player.dir_x;
		rotspeed = data->player.rotate * -1;
		if (data->player.dir == 'E' || data->player.dir == 'W')
			rotspeed = data->player.rotate * 1;
		data->player.dir_x = data->player.dir_x * cos(rotspeed)
			- data->player.dir_y * sin(rotspeed);
		data->player.dir_y = tmp_x * sin(rotspeed) + data->player.dir_y
			* cos(rotspeed);
		tmp_x = data->player.plane_x;
		data->player.plane_x = data->player.plane_x * cos(rotspeed)
			- data->player.plane_y * sin(rotspeed);
		data->player.plane_y = tmp_x * sin(rotspeed) + data->player.plane_y
			* cos(rotspeed);
		data->player.has_moved = true;
	}
	if (key.key == MLX_KEY_RIGHT || key.key == MLX_KEY_E)
	{
		tmp_x = data->player.dir_x;
		rotspeed = data->player.rotate * 1;
		if (data->player.dir == 'E' || data->player.dir == 'W')
			rotspeed = data->player.rotate * -1;
		data->player.dir_x = data->player.dir_x * cos(rotspeed)
			- data->player.dir_y * sin(rotspeed);
		data->player.dir_y = tmp_x * sin(rotspeed) + data->player.dir_y
			* cos(rotspeed);
		tmp_x = data->player.plane_x;
		data->player.plane_x = data->player.plane_x * cos(rotspeed)
			- data->player.plane_y * sin(rotspeed);
		data->player.plane_y = tmp_x * sin(rotspeed) + data->player.plane_y
			* cos(rotspeed);
		data->player.has_moved = true;
	}
}

int	main(int argc, char **argv)
{
	t_data	data;

	data_initialize(&data);
	parse_arguments(argv[1], &data);
	init_mlx(&data);
	init_textures(&data);
	init_player(&data);
	print_controls();
	ft_render(&data, 1);
	mlx_key_hook(data.mlx, k_hook, &data);
	mlx_loop_hook(data.mlx, hook, &data);
	mlx_loop(data.mlx);
	return (0);
}
