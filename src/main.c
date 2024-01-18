/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 12:45:20 by jkulka            #+#    #+#             */
/*   Updated: 2024/01/18 11:21:57 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	print_controls()
{
	printf("Glueckwunsch. Ihr habt es jetzt bis hierher geschafft :-)");
	printf("\n");
}

void ft_close(t_data *data)
{
	mlx_close_window(data->mlx);
	free(data->colors);
	system("leaks cub3d");

	exit(EXIT_SUCCESS);
}
void hook(void *v_data)
{
	t_data *data = v_data;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
	{
		ft_close(data);
	}
	if(data->player.has_moved == true)
		ft_render(data, 0);
}

void k_hook(mlx_key_data_t key, void *v_data)
{
	t_data *data = v_data;
	if(key.key == MLX_KEY_W)
	{
		double new_x = data->player.pos_x + data->player.dir_x * data->player.speed; 
		double new_y = data->player.pos_y + data->player.dir_y * data->player.speed;
		if(data->mapinfo.map[(int)round((new_y + 32) / 64)][(int)round((new_x + 32) / 64)] != '1')
		{
			data->player.pos_y += data->player.dir_y * data->player.speed;
			data->player.pos_x += data->player.dir_x * data->player.speed;
			data->player.has_moved = true;
			
		}
	}
	else if(key.key == MLX_KEY_S)
	{
		double new_x = data->player.pos_x - data->player.dir_x * data->player.speed; 
		double new_y = data->player.pos_y - data->player.dir_y * data->player.speed;
		if(data->mapinfo.map[(int)round((new_y - 32) / 64)][(int)round((new_x - 32) / 64)] != '1')
		{
			data->player.pos_y -= data->player.dir_y * data->player.speed;
			data->player.pos_x -= data->player.dir_x * data->player.speed;
			data->player.has_moved = true;	
		}
	}
	else if(key.key == MLX_KEY_A)
	{
		double new_x = data->player.pos_x + data->player.dir_x * data->player.speed; 
		double new_y = data->player.pos_y - data->player.dir_y * data->player.speed;
		if(data->mapinfo.map[(int)round((new_y + 32) / 64)][(int)round((new_x + 32) / 64)] != '1')
		{
			data->player.pos_x += data->player.dir_y * data->player.speed;
			data->player.pos_y -= data->player.dir_x * data->player.speed;
			data->player.has_moved = true;
		}
	}
	else if(key.key == MLX_KEY_D)
	{
		double new_x = data->player.pos_x - data->player.dir_x * data->player.speed; 
		double new_y = data->player.pos_y + data->player.dir_y * data->player.speed;
		if(data->mapinfo.map[(int)round((new_y + 32) / 64)][(int)round((new_x + 32) / 64)] != '1')
		{
			data->player.pos_x -= data->player.dir_y * data->player.speed;
			data->player.pos_y += data->player.dir_x * data->player.speed;
			data->player.has_moved = true;
		}
	}
	else if(key.key == MLX_KEY_Q)
	{
		double rotspeed;
		double tmp_x = data->player.dir_x;
		rotspeed = data->player.rotate * -1;
		data->player.dir_x = data->player.dir_x * cos(rotspeed) - data->player.dir_y * sin(rotspeed);
		data->player.dir_y = tmp_x * sin(rotspeed) + data->player.dir_y * cos(rotspeed);
		tmp_x = data->player.plane_x;
		data->player.plane_x = data->player.plane_x * cos(rotspeed) - data->player.plane_y * sin(rotspeed);
		data->player.plane_y = tmp_x * sin(rotspeed) + data->player.plane_y * cos(rotspeed);
		data->player.has_moved = true;
	}
	else if(key.key == MLX_KEY_E)
	{
		double rotspeed;
		double tmp_x = data->player.dir_x;
		rotspeed = data->player.rotate * 1;
		data->player.dir_x = data->player.dir_x * cos(rotspeed) - data->player.dir_y * sin(rotspeed);
		data->player.dir_y = tmp_x * sin(rotspeed) + data->player.dir_y * cos(rotspeed);
		tmp_x = data->player.plane_x;
		data->player.plane_x = data->player.plane_x * cos(rotspeed) - data->player.plane_y * sin(rotspeed);
		data->player.plane_y = tmp_x * sin(rotspeed) + data->player.plane_y * cos(rotspeed);
		data->player.has_moved = true;
	}
}
 
int	main(int argc, char **argv)
{
	t_data	data;

	data_initialize(&data);						//Initialisiere die Datenstruktur
	parse_arguments(argv[1], &data);			//Parse die Argumente
	init_mlx(&data);							//Initialisiere die MLX-Bibliothek @Jens: bin heute bis hierher gekommen. Lass uns aber das "parse_arguments" nochmal gemeinsam anschauen. Bin mir das noch nicht so ganz sicher. Bis Morgen. Gruss Robin :-)
	init_textures(&data);						//Lade Texturen
	init_player(&data);
	print_controls();							//Gib Informationen zu den Steuerelementen aus
	ft_render(&data, 1);	//Rendere die Bilder
	mlx_key_hook(data.mlx, k_hook, &data);
	mlx_loop_hook(data.mlx, hook, &data);	//Höre auf Benutzereingaben
	mlx_loop(data.mlx);							//Starte die MLX-Loop
	return (0);
}