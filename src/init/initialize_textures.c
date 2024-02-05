/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_textures.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 10:45:53 by rmarquar          #+#    #+#             */
/*   Updated: 2024/01/22 11:50:10 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

char	*ft_check_dir_2(int i, t_data *data, char *str, int *count)
{
	char	*tmp;

	*count += 1;
	tmp = get_value(data->mapinfo.file[i], str);
	ft_printf("\t%c\n", str[0]);
	if (open(tmp, O_RDONLY) == -1 && (str[0] != 'F' && str[0] != 'C'))
		ft_error(OPEN, data);
	free(tmp);
	return (get_value(data->mapinfo.file[i], str));
}

int	ft_check_dir(int i, t_data *data)
{
	int	count;

	count = 0;
	while (data->mapinfo.file[i] != NULL)
	{
		if (count == 6)
			break ;
		if (ft_strcmp_cub3d(data->mapinfo.file[i], "NO") == 0)
			data->texinfo.north = ft_check_dir_2(i, data, "NO", &count);
		else if (ft_strcmp_cub3d(data->mapinfo.file[i], "SO") == 0)
			data->texinfo.south = ft_check_dir_2(i, data, "SO", &count);
		else if (ft_strcmp_cub3d(data->mapinfo.file[i], "WE") == 0)
			data->texinfo.west = ft_check_dir_2(i, data, "WE", &count);
		else if (ft_strcmp_cub3d(data->mapinfo.file[i], "EA") == 0)
			data->texinfo.east = ft_check_dir_2(i, data, "EA", &count);
		else if (ft_strcmp_cub3d(data->mapinfo.file[i], "F") == 0)
			data->texinfo.floor = ft_check_dir_2(i, data, "F", &count);
		else if (ft_strcmp_cub3d(data->mapinfo.file[i], "C") == 0)
			data->texinfo.ceiling = ft_check_dir_2(i, data, "C", &count);
		i++;
	}
	ft_parse_map(data, i);
	return (count);
}

void	init_textures(t_data *data)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	count = ft_check_dir(i, data);
	ft_load_textures(data);
	ft_load_colors(data);
}
