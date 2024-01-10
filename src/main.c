/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 12:45:20 by jkulka            #+#    #+#             */
/*   Updated: 2024/01/10 12:36:58 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	print_controls(void)
{
	printf("Glueckwunsch. Ihr habt es jetzt bis hierher geschafft :-)");
	printf("\n");
}

void hook(void *v_data)
{
	t_data *data = v_data;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
	ft_clear(data);
	//TODO Render function implementieren. 
	mlx_put_pixel(data->img, 10, 10, get_rgba(255, 0, 0, 255));
}

int	main(int argc, char **argv)
{
	t_data	data;

	data_initialize(&data);						//Initialisiere die Datenstruktur
	// parse_arguments(argv[1], &data);			//Parse die Argumente
	init_mlx(&data);							//Initialisiere die MLX-Bibliothek @Jens: bin heute bis hierher gekommen. Lass uns aber das "parse_arguments" nochmal gemeinsam anschauen. Bin mir das noch nicht so ganz sicher. Bis Morgen. Gruss Robin :-)
	// init_textures(&data);						//Lade Texturen
	print_controls();							//Gib Informationen zu den Steuerelementen aus
	// render_images(&data);						//Rendere die Bilder
	// listen_for_input(&data);					//Höre auf Benutzereingaben
	mlx_loop_hook(data.mlx, hook, &data);	//Höre auf Benutzereingaben
	mlx_loop(data.mlx);							//Starte die MLX-Loop
	return (0);
}
