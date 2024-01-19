/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 12:45:20 by jkulka            #+#    #+#             */
/*   Updated: 2024/01/19 14:58:29 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void		ft_rotate(t_data *data, double rotspeed);

static void	print_controls(void)
{
	ft_printf("Controls:\nW, A, S, D for movement.\n->/Q,"
		"<-/E for rotation.\n ESC for exiting\n");
}

void	ft_close(t_data *data)
{
	mlx_close_window(data->mlx);
	free(data->colors);
	exit(EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	t_data	data;

	data_initialize(&data);
	parse_arguments(argv[1], &data, argc);
	init_mlx(&data);
	init_textures(&data);
	init_player(&data);
	print_controls();
	ft_render(&data, 1);
	mlx_loop_hook(data.mlx, move_hook, &data);
	mlx_loop_hook(data.mlx, rotate_hook, &data);
	mlx_loop_hook(data.mlx, main_hook, &data);
	mlx_loop(data.mlx);
	return (0);
}
