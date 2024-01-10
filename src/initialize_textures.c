/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_textures.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 10:45:53 by rmarquar          #+#    #+#             */
/*   Updated: 2024/01/10 14:45:05 by jkulka           ###   ########.fr       */
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
	while(line[i] != '\0')
	{
		if(ft_isprint(line[i]))
		{
			if(line[i] == ' ')
				i++;
			else
				len++;
		}
		i++;
	}
	return len;
}
char *get_value(char *line, char *name)
{
	int i = ft_strlen(name) - 1;
	int len = get_value_len(line, i);
	int j = 0;
	char *res = ft_calloc(len + 1, sizeof(char));
	if(!res)
		ft_error(MALLOC);
	ft_printf("\t%d\n", i);
	
	// while(line[i] != '\0')
	// {
	// 	if(ft_isprint(line[i]))
	// 	{
	// 		if(line[i] == ' ')
	// 			i++;
	// 		else
	// 		{
	// 			res[j] = line[i];
	// 			j++;
	// 		}
	// 	}
	// 	i++;
	// }

	return (res);
}
void	init_textures(t_data *data)
{
	int i = 0;
	int count = 0;
	while(data->mapinfo.file[i] != NULL && is_line_empty(data->mapinfo.file[i]) == 0)
	{
		if(ft_strncmp(data->mapinfo.file[i], "NO", 2) == 0)
		{
			// ft_printf("Found no\n");
			ft_printf("%s\n",get_value(data->mapinfo.file[i], "NO"));
			count += 1;
		}
		else if(ft_strncmp(data->mapinfo.file[i], "SO", 2) == 0)
		{
			// ft_printf("Found so\n");
			get_value(data->mapinfo.file[i], "SO");
			count += 1;
		}
		else if(ft_strncmp(data->mapinfo.file[i], "WE", 2) == 0)
		{
			// ft_printf("Found we\n");
			get_value(data->mapinfo.file[i], "WE");
			count += 1;
		}
		else if(ft_strncmp(data->mapinfo.file[i], "EA", 2) == 0)
		{
			// ft_printf("Found ea\n");
			get_value(data->mapinfo.file[i], "EA");
			count += 1;
		}
		i++;
	}
	if(count != 4)
		ft_strerror("MAP");
	data->textures = ft_calloc(5, sizeof * data->textures);
	// data->textures[NORTH] = xpm_to_img(data, data->texinfo.north);
	// data->textures[SOUTH] = xpm_to_img(data, data->texinfo.south);
	// data->textures[EAST] = xpm_to_img(data, data->texinfo.east);
	// data->textures[WEST] = xpm_to_img(data, data->texinfo.west);
}
