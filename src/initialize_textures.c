/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_textures.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 10:45:53 by rmarquar          #+#    #+#             */
/*   Updated: 2024/01/10 15:54:55 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"


int is_line_empty(char *line)
{
	int i = 0;
	while(line[i] != '\0' && line[i] != '\n')
	{
		if(ft_isprint(line[i]))
		{
			if(line[i] == ' ')
				;
			else
				return 0;
		}
		i++;
	}
	return 1;
}

int get_value_len(char *line, int i)
{
	int len = 0;
	while(line[i] != '\0' && line[i] != '\n')
	{
		if(ft_isprint(line[i]))
		{
			if(line[i] != ' ')
				len++;
		}
			i++;
	}
	return len;
}
char *get_value(char *line, char *name)
{
	int i = ft_strlen(name);
	int len = get_value_len(line, i);
	int j = ft_strlen(line) - len -1;
	char *res = ft_calloc(len + 1, sizeof(char));
	if(!res)
		ft_error(MALLOC);
	res = ft_strncpy(&line[j], res, len);

	return (res);
}

char *ft_check_dir_2(int i, t_data *data, char *str, int *count)
{
	*count += 1;
	return (get_value(data->mapinfo.file[i], str));
}

int ft_check_dir(int i, t_data *data)
{
	int count;

	count = 0;
	while(data->mapinfo.file[i++] != NULL && is_line_empty(data->mapinfo.file[i]) == 0)
	{
		if(ft_strncmp(data->mapinfo.file[i], "NO", 2) == 0)
			data->texinfo.north = ft_check_dir_2(i, data, "NO", &count);
		else if(ft_strncmp(data->mapinfo.file[i], "SO", 2) == 0)
			data->texinfo.south = ft_check_dir_2(i, data, "SO", &count);
		else if(ft_strncmp(data->mapinfo.file[i], "WE", 2) == 0)
			data->texinfo.west = ft_check_dir_2(i, data, "WE", &count);
		else if(ft_strncmp(data->mapinfo.file[i], "EA", 2) == 0)
			data->texinfo.east = ft_check_dir_2(i, data, "EA", &count);
	} 
	return (count);
}
void	init_textures(t_data *data)
{
	int i = 0;
	int count = 0;
	char *tmp = NULL;
	
	count = ft_check_dir(i - 1, data);
	ft_printf("\t%d\n", count);
	if(count != 4)
		ft_strerror("MAP");
	data->textures = ft_calloc(5, sizeof * data->textures);
	data->textures[NORTH] = mlx_texture_to_image(data->mlx, mlx_load_png(data->texinfo.north));
	data->textures[SOUTH] = mlx_texture_to_image(data->mlx, mlx_load_png(data->texinfo.south));
	data->textures[WEST] = mlx_texture_to_image(data->mlx, mlx_load_png(data->texinfo.west));
	data->textures[EAST] = mlx_texture_to_image(data->mlx, mlx_load_png(data->texinfo.east));
}
