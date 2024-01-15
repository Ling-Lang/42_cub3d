/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 12:48:10 by jkulka            #+#    #+#             */
/*   Updated: 2024/01/15 14:52:41 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <math.h>

#include "../lib/MLX42/include/MLX42/MLX42.h"
#include "../lib/Libft/src/libft.h"
#include "structs.h"
#include "../lib/get_next_line/get_next_line.h"

# define WIN_WIDTH 640
# define WIN_HEIGHT 480



# define TEX_SIZE 64

void	init_mlx(t_data *data);
void	data_initialize(t_data *data);
void ray_init(t_ray *ray);
void	init_mlx(t_data *data);
// void	init_img_clean(t_img *img);
void	init_textures(t_data *data);
void	parse_arguments(char *path, t_data *data);

/* Draw Utils */
int get_rgba(int r, int g, int b, int a);
void ft_clear(t_data *data);

/* Error Utils */
void ft_strerror(char *str);
void ft_error(int type);

/* Init */
int	is_line_empty(char *line);
int	get_value_len(char *line, int i);
char	*get_value(char *line, char *name);
int ft_load_textures(t_data *data);
int ft_load_colors(t_data *data);
int ft_get_color(char *raw_value);
void ft_parse_map(t_data *data, int i);
void	init_player(t_data *data);

/* Render Zeugs */
int ft_render(t_data *data, bool direct);
void raycast(t_data *data);
void set_dda(t_ray *ray, t_data *data);
void do_dda(t_ray *ray, t_data *data);
void calc_height(t_ray *ray, t_data *data);

#endif
