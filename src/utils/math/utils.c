/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 13:27:12 by jkulka            #+#    #+#             */
/*   Updated: 2023/12/06 15:33:45 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"
/*
function degreeToRadians(degree) {
    let pi = Math.PI;
    return degree * pi / 180;
}
*/
double degreeToRadian(double degree)
{
    return (degree * M_PI / 180);
}