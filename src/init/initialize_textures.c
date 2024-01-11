/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_textures.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 10:45:53 by rmarquar          #+#    #+#             */
/*   Updated: 2024/01/11 11:56:48 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

char	*ft_check_dir_2(int i, t_data *data, char *str, int *count)
{
	*count += 1;
	return (get_value(data->mapinfo.file[i], str));
}

int	ft_check_dir(int i, t_data *data)
{
	int	count;

	count = 0;
	while (data->mapinfo.file[i++] != NULL
		&& is_line_empty(data->mapinfo.file[i]) == 0)
	{
		if (ft_strcmp_cub3d(data->mapinfo.file[i], "NO") == 0)
			data->texinfo.north = ft_check_dir_2(i, data, "NO", &count);
		else if (ft_strcmp_cub3d(data->mapinfo.file[i], "SO") == 0)
			data->texinfo.south = ft_check_dir_2(i, data, "SO", &count);
		else if (ft_strcmp_cub3d(data->mapinfo.file[i], "WE") == 0)
			data->texinfo.west = ft_check_dir_2(i, data, "WE", &count);
		else if (ft_strcmp_cub3d(data->mapinfo.file[i], "EA") == 0)
			data->texinfo.east = ft_check_dir_2(i, data, "EA", &count);
		
	}
	return (count);
}



void	init_textures(t_data *data)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	count = ft_check_dir(i - 1, data);
	if (count != 4)
		ft_strerror("MAP");
	ft_load_textures(data);
}
