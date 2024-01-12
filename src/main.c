/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 12:45:20 by jkulka            #+#    #+#             */
/*   Updated: 2024/01/12 16:16:30 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	print_controls()
{
	printf("Glueckwunsch. Ihr habt es jetzt bis hierher geschafft :-)");
	printf("\n");
}
void drawMap(t_data *data)
{
    int i, j, x, y;
    for(i = 0; data->mapinfo.map[i]; i++)
    {
        for(j = 0; data->mapinfo.map[i][j]; j++)
        {
            // Choose a color based on the cell's value
            int color = (data->mapinfo.map[i][j] == '0') ? data->colors[FLOOR] : data->colors[CEILING];
			if(data->mapinfo.map[i][j] == 'S')
				color = get_rgba(12, 12, 12, 255);
			else if(data->mapinfo.map[i][j] == '-')
				color = get_rgba(255, 255, 255, 255);
			else if(data->mapinfo.map[i][j] == '\n')
				color = get_rgba(255, 255, 255, 255);
            for(y = 0; y < 64; y++)
            {
                for(x = 0; x < 64; x++)
                {
					mlx_put_pixel(data->img, j * 64 + x, i * 64 + y, color);
                }
            }
        }
    }
}

void hook(void *v_data)
{
	t_data *data = v_data;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
	ft_clear(data);
	drawMap(data);
	mlx_put_pixel(data->img, 100, 100, data->colors[FLOOR]);
	mlx_image_to_window(data->mlx, data->img, 0, 0);
	//TODO Render function implementieren.
}

int	main(int argc, char **argv)
{
	t_data	data;

	data_initialize(&data);						//Initialisiere die Datenstruktur
	parse_arguments(argv[1], &data);			//Parse die Argumente
	init_mlx(&data);							//Initialisiere die MLX-Bibliothek @Jens: bin heute bis hierher gekommen. Lass uns aber das "parse_arguments" nochmal gemeinsam anschauen. Bin mir das noch nicht so ganz sicher. Bis Morgen. Gruss Robin :-)
	init_textures(&data);						//Lade Texturen
	print_controls();
	// render_images(&data);						//Rendere die Bilder
	// listen_for_input(&data);					//Höre auf Benutzereingaben
	mlx_loop_hook(data.mlx, hook, &data);	//Höre auf Benutzereingaben
	mlx_loop(data.mlx);							//Starte die MLX-Loop
	return (0);
}
