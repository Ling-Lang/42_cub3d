/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_arguments.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 11:21:04 by rmarquar          #+#    #+#             */
/*   Updated: 2024/01/18 13:25:32 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	how_many_lines(char *path)
{
	int		fd;
	char	*line;
	int		counter;

	counter = 0;
	fd = open(path, O_RDONLY);
	if (fd < 0)
		perror("Error Message\n");
	else
	{
		line = get_next_line(fd);
		while (line != 0)
		{
			counter++;
			free(line);
			line = get_next_line(fd);
		}
		close(fd);
	}
	return (counter);
}

static void	build_size_of_map(t_data *data, int row, int col, int i)
{
	char	*line;

	line = get_next_line(data->mapinfo.fd);
	while (line != 0)
	{
		data->mapinfo.file[row] = ft_calloc(ft_strlen(line) + 1, sizeof(char));
		while (line[i] != '\0')
		{
			data->mapinfo.file[row][col] = line[i];
			col++;
			i++;
		}
		data->mapinfo.file[row++][col] = '\0';
		col = 0;
		i = 0;
		free(line);
		line = get_next_line(data->mapinfo.fd);
	}
	data->mapinfo.file[row] = NULL;
}

void	parse_arguments(char *path, t_data *data)
{
	int	i;
	int	row;
	int	col;

	i = 0;
	col = 0;
	row = 0;
	data->mapinfo.line_count = how_many_lines(path);
	data->mapinfo.path = path;
	data->mapinfo.file = ft_calloc(data->mapinfo.line_count + 1,
			sizeof(char *));
	data->mapinfo.fd = open(path, O_RDONLY);
	build_size_of_map(data, row, col, i);
	close(data->mapinfo.fd);
}
