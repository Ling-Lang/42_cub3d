/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 11:48:05 by jkulka            #+#    #+#             */
/*   Updated: 2024/01/19 14:29:39 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	ft_isplayer(char c)
{
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
		return (1);
	else
		return (0);
}

bool	ft_check_around(t_data *data, int col, int rows)
{
	if (ft_isalnum(data->mapinfo.file[col + 1][rows]) == 1)
	{
		if (ft_isalnum(data->mapinfo.file[col - 1][rows]) == 1)
		{
			if (ft_isalnum(data->mapinfo.file[col][rows + 1]) == 1)
			{
				if (ft_isalnum(data->mapinfo.file[col][rows - 1]) == 1)
					return (true);
				else
					return (false);
			}
			else
				return (false);
		}
		else
			return (false);
	}
	else
		return (false);
}

int	ft_count_map_lines(t_data *data, int i)
{
	int	len;

	len = 0;
	while (data->mapinfo.file[i])
	{
		len++;
		i++;
	}
	return (len);
}

bool	check_player(t_data *data, int col, int rows, bool *player)
{
	if (ft_isplayer(data->mapinfo.file[col][rows]) == true)
	{
		if (*player == true)
			return (false);
		else
		{
			*player = true;
			data->player.pos_y = data->mapinfo.len * 64;
			data->player.pos_x = rows * 64;
			data->player.dir = data->mapinfo.file[col][rows];
		}
	}
	return (true);
}
