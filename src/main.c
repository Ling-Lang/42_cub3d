/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarquar <rmarquar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 12:45:20 by jkulka            #+#    #+#             */
/*   Updated: 2024/01/08 16:09:03 by rmarquar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	main(int ac, char **av)
{
	t_data	data;

	init_data(&data);                           //Initialisiere die Datenstruktur
	if (parse_args(&data, av) != 0)             //Parse die Argumente
		return (1);
	init_mlx(&data);                            //Initialisiere die MLX-Bibliothek
	init_textures(&data);                       //Lade Texturen
	print_controls();                           //Gib Informationen zu den Steuerelementen aus
	render_images(&data);                       //Rendere die Bilder
	listen_for_input(&data);                    //Höre auf Benutzereingaben
	mlx_loop_hook(data.mlx, render, &data);     //Höre auf Benutzereingaben
	mlx_loop(data.mlx);                         //Starte die MLX-Loop
	return (0);
}
