/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:35:14 by jkulka            #+#    #+#             */
/*   Updated: 2024/01/19 14:29:17 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

bool	ft_check(t_data *data, int col, int *rows, bool *player)
{
	if (data->mapinfo.file[col][*rows] == '1')
		*rows += 1;
	else if (data->mapinfo.file[col][*rows] == '0'
		|| ft_isplayer(data->mapinfo.file[col][*rows]) == 1)
	{
		if (ft_check_around(data, col, *rows) == true)
		{
			if (check_player(data, col, *rows, player) == false)
				return (false);
			*rows += 1;
		}
		else
			return (false);
	}
	else if (data->mapinfo.file[col][*rows] == ' '
		|| data->mapinfo.file[col][*rows] == '\n')
		*rows += 1;
	else
		return (false);
	return (true);
}

static int	ft_validate_map(t_data *data, int i)
{
	int		rows;
	bool	player;
	bool	is_valid;

	rows = 0;
	data->mapinfo.len = 0;
	is_valid = true;
	player = false;
	data->mapinfo.map = ft_calloc(ft_count_map_lines(data, i) + 1,
			sizeof(char *));
	while (data->mapinfo.file[i] != NULL && is_valid == true)
	{
		while (data->mapinfo.file[i][rows] != '\0')
		{
			if (ft_check(data, i, &rows, &player) == false)
				ft_error(MAP, data);
		}
		data->mapinfo.map[data->mapinfo.len++] = (char *)ft_calloc(rows,
				sizeof(char));
		rows = 0;
		i++;
	}
	if (player == false)
		return (false);
	return (is_valid);
}

void	ft_fill_map(t_data *data, int i)
{
	int	col;
	int	rows;
	int	k;
	int	j;

	k = 0;
	j = 0;
	rows = 0;
	col = i - 1;
	while (data->mapinfo.file[++col] != NULL)
	{
		while (data->mapinfo.file[col][rows] != '\0')
		{
			if (data->mapinfo.file[col][rows] == ' ')
				data->mapinfo.map[k][j] = '-';
			else
				data->mapinfo.map[k][j] = data->mapinfo.file[col][rows];
			j++;
			rows++;
		}
		j = 0;
		k++;
		rows = 0;
	}
	data->mapinfo.map[k] = NULL;
}

void	ft_parse_map(t_data *data, int i)
{
	int	j;

	while (is_line_empty(data->mapinfo.file[i]) == 0)
		i++;
	i++;
	j = 0;
	while (data->mapinfo.file[i][j] != '\0')
	{
		if (data->mapinfo.file[i][j] == '0')
			ft_error(MAP, data);
		j++;
	}
	if (ft_validate_map(data, i) == true)
		ft_fill_map(data, i);
}
