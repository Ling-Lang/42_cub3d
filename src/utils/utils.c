/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 14:22:33 by jkulka            #+#    #+#             */
/*   Updated: 2024/01/19 15:08:33 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	ft_error_2(int type, t_data *data)
{
	if (type == OPEN)
	{
		ft_strerror("Invalid file or filepath\n", data);
		exit(EXIT_FAILURE);
	}
	if (type == M_FILE)
	{
		ft_strerror("Invalid map file make sure it ends in .cub\n", data);
		exit(EXIT_FAILURE);
	}
}

void	ft_error(int type, t_data *data)
{
	if (type == MLX)
	{
		perror(mlx_strerror(mlx_errno));
		ft_close(data);
	}
	else if (type == MALLOC)
	{
		perror("Malloc");
		ft_close(data);
	}
	else if (type == MAP)
	{
		ft_strerror("Map is not valid look into the subject"
			"for more information!\n", data);
		ft_close(data);
	}
	else if (type == ARG)
	{
		ft_strerror("Invalid number of arguements!\n", data);
		exit(EXIT_FAILURE);
	}
	else
		ft_error_2(type, data);
}

void	ft_strerror(char *str, t_data *data)
{
	write(2, "Error:\n", 7);
	ft_putstr_fd(str, 2);
}
