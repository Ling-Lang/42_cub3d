/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 12:48:10 by jkulka            #+#    #+#             */
/*   Updated: 2024/01/10 12:38:36 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

#include "../lib/MLX42/include/MLX42/MLX42.h"
#include "../lib/Libft/src/libft.h"
#include "structs.h"
#include "../lib/get_next_line/get_next_line.h"

# define WIN_WIDTH 640
# define WIN_HEIGHT 480

#define NORTH 0
#define SOUTH 1
#define EAST 2
#define WEST 3

# define TEX_SIZE 64

void	init_mlx(t_data *data);
void	data_initialize(t_data *data);
void	init_mlx(t_data *data);
// void	init_img_clean(t_img *img);
void	parse_arguments(char *path, t_data *data);

/* Draw Utils */
int get_rgba(int r, int g, int b, int a);
void ft_clear(t_data *data);
#endif
