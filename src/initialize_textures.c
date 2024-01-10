/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_textures.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 10:45:53 by rmarquar          #+#    #+#             */
/*   Updated: 2024/01/10 15:28:47 by jkulka           ###   ########.fr       */
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
void	init_textures(t_data *data)
{
	int i = 0;
	int count = 0;
	char *tmp = NULL;
	while(data->mapinfo.file[i] != NULL && is_line_empty(data->mapinfo.file[i]) == 0)
	{
		if(ft_strncmp(data->mapinfo.file[i], "NO", 2) == 0)
		{
			tmp = get_value(data->mapinfo.file[i], "NO");
			data->texinfo.north = ft_strdup(tmp);
			free(tmp);
			count += 1;
		}
		else if(ft_strncmp(data->mapinfo.file[i], "SO", 2) == 0)
		{
			tmp = get_value(data->mapinfo.file[i], "SO");
			data->texinfo.south = ft_strdup(tmp);
			free(tmp);
			count += 1;
		}
		else if(ft_strncmp(data->mapinfo.file[i], "WE", 2) == 0)
		{
			tmp = get_value(data->mapinfo.file[i], "WE");
			data->texinfo.west = ft_strdup(tmp);
			free(tmp);
			count += 1;
		}
		else if(ft_strncmp(data->mapinfo.file[i], "EA", 2) == 0)
		{
			tmp = get_value(data->mapinfo.file[i], "EA");
			data->texinfo.east = ft_strdup(tmp);
			free(tmp);
			count += 1;
		}
		i++;
	}
	if(count != 4)
		ft_strerror("MAP");
	data->textures = ft_calloc(5, sizeof * data->textures);
	ft_printf("\t%s\n", data->texinfo.north);
	data->textures[NORTH] = mlx_texture_to_image(data->mlx, mlx_load_png(data->texinfo.north));
	data->textures[SOUTH] = mlx_texture_to_image(data->mlx, mlx_load_png(data->texinfo.south));
	data->textures[WEST] = mlx_texture_to_image(data->mlx, mlx_load_png(data->texinfo.west));
	data->textures[EAST] = mlx_texture_to_image(data->mlx, mlx_load_png(data->texinfo.east));
	mlx_image_to_window(data->mlx, data->textures[NORTH], 50, 50);
	mlx_image_to_window(data->mlx, data->textures[SOUTH], 0, 0);
	mlx_image_to_window(data->mlx, data->textures[EAST], 100, 100);
	mlx_image_to_window(data->mlx, data->textures[WEST], 250, 250);
	// data->textures[NORTH] = xpm_to_img(data, data->texinfo.north);
	// data->textures[SOUTH] = xpm_to_img(data, data->texinfo.south);
	// data->textures[EAST] = xpm_to_img(data, data->texinfo.east);
	// data->textures[WEST] = xpm_to_img(data, data->texinfo.west);
}
