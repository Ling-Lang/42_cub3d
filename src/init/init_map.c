/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:35:14 by jkulka            #+#    #+#             */
/*   Updated: 2024/01/15 19:53:22 by jkulka           ###   ########.fr       */
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

static bool ft_check_around(t_data *data, int col, int rows)
{
    if(ft_isalnum(data->mapinfo.file[col + 1][rows]) == 1)
    {
        if(ft_isalnum(data->mapinfo.file[col - 1][rows]) == 1)
        {
            if(ft_isalnum(data->mapinfo.file[col][rows + 1]) == 1)
            {
                if(ft_isalnum(data->mapinfo.file[col][rows - 1]) == 1)
                    return true;
                else    
                    return false;
            }
            else
                return false;
        }
        else
            return false;

    }
    else
        return false;
}

int ft_count_map_lines(t_data *data, int i)
{
    int len = 0;

    while(data->mapinfo.file[i])
    {
        len++;
        i++;
    }
    return len;
}
static int	ft_validate_map(t_data *data, int i)
{
	int		rows;
	int		col;
	bool	player;
    bool    is_valid;
    int     len;

	rows = 0;
	col = i;
    len = 0;
    is_valid = true;
    player = false;
    data->mapinfo.map = ft_calloc(ft_count_map_lines(data, i) + 1, sizeof(char *));
	while (data->mapinfo.file[col] != NULL && is_valid == true)
	{
		while (data->mapinfo.file[col][rows] != '\0')
		{
			if (data->mapinfo.file[col][rows] == '1')
				rows++;
			else if (data->mapinfo.file[col][rows] == '0'
				|| ft_isplayer(data->mapinfo.file[col][rows]) == 1)
            {
				    if(ft_check_around(data, col, rows) == true)
                    {
                        if(ft_isplayer(data->mapinfo.file[col][rows]) == true)
                        {
                            if(player == true)
                                return false;
                            else
                            {
                                player = true;
                                data->player.pos_y = len * 64;
                                data->player.pos_x = rows * 64;
                                data->player.dir = data->mapinfo.file[col][rows];
                            }
                        }
                        rows++;
                    }
                    else
                        return false;
            }
            else if (data->mapinfo.file[col][rows] == ' ' || data->mapinfo.file[col][rows] == '\n')
                rows++;
            else
                return false;
		}
        data->mapinfo.map[len++] = (char*)ft_calloc(rows, sizeof(char));
		rows = 0;
		col++;
	}
    if(player == false)
        return false;
    return is_valid;
}

bool ft_fill_map(t_data *data, int i)
{
    int col;
    int rows;
    int k;
    int j;

    k = 0;
    j = 0;
    rows = 0;
    col = i;
    while (data->mapinfo.file[col] != NULL)
	{
		while (data->mapinfo.file[col][rows] != '\0')
		{
            if(data->mapinfo.file[col][rows] == ' ')
                data->mapinfo.map[k][j] = '-';
            else
            {
                data->mapinfo.map[k][j] = data->mapinfo.file[col][rows];
            }
            j++;
            rows++;  
		}
        j = 0;
        k++;
        col++;
		rows = 0;
	}
    data->mapinfo.map[k] = NULL;
    return true;
}

void	ft_parse_map(t_data *data, int i)
{
	while (is_line_empty(data->mapinfo.file[i]) == 0)
		i++;
	// Weiteres i++ um die leerzeile zwischen map und rest zu skippen.
	i++;
    if(ft_validate_map(data, i) == true)
    {
        ft_printf("Yaay\n");
        ft_fill_map(data, i);
        int j =0;
        int k = 0;
        while(data->mapinfo.map[j])
        {
            while(data->mapinfo.map[j][k] != '\0')
            {
                ft_printf("%c", data->mapinfo.map[j][k]);
                k++;
            }
            k = 0;
            j++;
        }
        ft_printf("\n");
    }
}
