/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 14:22:33 by jkulka            #+#    #+#             */
/*   Updated: 2024/01/10 14:32:30 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
void ft_error(int type)
{
    if(type == MLX)
    {
	    perror(mlx_strerror(mlx_errno));
	    exit(EXIT_FAILURE);
    }
    if(type == MALLOC)
    {
        perror("Malloc");
        exit(EXIT_FAILURE);
    }
}
void ft_strerror(char *str)
{
    write(2, "Error: ", 7);
    perror(str);
    write(2, "\n", 1);
    exit(EXIT_FAILURE);
}
