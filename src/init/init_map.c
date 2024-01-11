/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:35:14 by jkulka            #+#    #+#             */
/*   Updated: 2024/01/11 18:34:47 by jkulka           ###   ########.fr       */
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
    // ft_printf("%s\n", data->mapinfo.file[col][rows]);
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

static int	ft_validate_map(t_data *data, int i)
{
	int		rows;
	int		col;
	bool	player;
    bool    is_valid;
    int     len;

    len = 0;
	rows = 0;
	col = i;
    is_valid = true;
	while (data->mapinfo.file[col] != NULL && is_valid == true)
	{
		while (data->mapinfo.file[col][rows] != '\0')
		{
			if (data->mapinfo.file[col][rows] == '1')
            {
				rows++;
                len++;
            }
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
                                player = true;
                        }
                        rows++;
                        len++;
                    }
                    else
                    {
                        return false;
                    }
            }
            else if (data->mapinfo.file[col][rows] == ' ' || data->mapinfo.file[col][rows] == '\n')
                rows++;
            else
                return false;
		}
		rows = 0;
		col++;
	}
    return is_valid;
}

void	ft_parse_map(t_data *data, int i)
{
	while (is_line_empty(data->mapinfo.file[i]) == 0)
		i++;
	// Weiteres i++ um die leerzeile zwischen map und rest zu skippen.
	i++;
    if(ft_validate_map(data, i) == true)
        ft_printf("Yaay\n");
}
