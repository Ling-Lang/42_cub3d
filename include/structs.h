/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 13:06:59 by jkulka            #+#    #+#             */
/*   Updated: 2023/12/15 13:37:13 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H
#include "cub3d.h"

typedef struct s_point
{
    int x;
    int y;
}   t_point;
typedef struct s_float_point
{
    double x;
    double y;
} t_float_point;

typedef struct s_data
{
    mlx_image_t *img;
    mlx_t *mlx;
    int width;
    int height;
    double halfW;
    double halfH;
    int delay;
    double incrementAngle;
    double detail;
    double fov;
    double halfFov;
    double x;
    double y;
    double angle;
    double speed;
    double rot;
    int map[10][10];
}   t_data;

#endif // STRUCTS_H