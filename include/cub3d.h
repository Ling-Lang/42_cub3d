/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 12:48:10 by jkulka            #+#    #+#             */
/*   Updated: 2023/12/06 15:33:56 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../lib/MLX42/include/MLX42/MLX42.h"
# include "../lib/Libft/src/libft.h"
# include "structs.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <math.h>

/* Utils */
int get_rgba(int r, int g, int b, int a);
void	ft_putline(t_data *data, t_point *p1, t_point* p2, int color);
void ft_putline_alt(t_data *data, int x0, int y0, int x1, int y1, int color);
double degreeToRadian(double degree);
void ft_clear(t_data *data);
#endif // CUB3D_H