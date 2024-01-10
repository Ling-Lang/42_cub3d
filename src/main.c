/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarquar <rmarquar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 12:45:20 by jkulka            #+#    #+#             */
/*   Updated: 2024/01/10 11:01:19 by rmarquar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/cub3d.h"

static void	print_controls(void)
{
	printf("Glueckwunsch. Ihr habt es jetzt bis hierher geschafft :-)");

	printf("\n");
}

int	main(int argc, char **argv)
{
	t_data	data;

	data_initialize(&data);						//Initialisiere die Datenstruktur
	parse_arguments(argv[1], &data);			//Parse die Argumente
	init_mlx(&data);							//Initialisiere die MLX-Bibliothek @Jens: bin heute bis hierher gekommen. Lass uns aber das "parse_arguments" nochmal gemeinsam anschauen. Bin mir das noch nicht so ganz sicher. Bis Morgen. Gruss Robin :-)
	init_textures(&data);						//Lade Texturen
	print_controls();							//Gib Informationen zu den Steuerelementen aus
	render_images(&data);						//Rendere die Bilder
	listen_for_input(&data);					//Höre auf Benutzereingaben
	// mlx_loop_hook(data.mlx, render, &data);	//Höre auf Benutzereingaben
	mlx_loop(data.mlx);							//Starte die MLX-Loop
	return (0);
}
