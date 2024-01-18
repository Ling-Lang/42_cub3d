/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 10:38:51 by jkulka            #+#    #+#             */
/*   Updated: 2024/01/18 11:26:29 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	is_line_empty(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0' && line[i] != '\n')
	{
		if (ft_isprint(line[i]))
		{
			if (line[i] == ' ')
				;
			else
				return (0);
		}
		i++;
	}
	return (1);
}

int	get_value_len(char *line, int i)
{
	int	len;

	len = 0;
	while (line[i] != '\0' && line[i] != '\n')
	{
		if (ft_isprint(line[i]))
		{
			if (line[i] != ' ')
				len++;
		}
		i++;
	}
	return (len);
}

char	*get_value(char *line, char *name)
{
	int		i;
	int		len;
	int		j;
	char	*res;

	i = ft_strlen(name);
	len = get_value_len(line, i);
	j = ft_strlen(line) - len - 1;
	res = ft_calloc(len + 1, sizeof(char));
	if (!res)
		ft_error(MALLOC);
	res = ft_strncpy(&line[j], res, len);
	return (res);
}

//TODO Fehler mit nachfolgenden tabs oder spaces fixen (trim?)
int ft_get_color(char *raw_value)
{
	char **tmp_split;

	tmp_split = ft_split(raw_value, ',');
	int res;
	// ft_printf("r: %s g:%s b:%s\n", tmp_split[0], tmp_split[1], tmp_split[2]);
	res = get_rgba(ft_atoi(tmp_split[0]), ft_atoi(tmp_split[1]), ft_atoi(tmp_split[2]), 255);
	int i = 0;
	while(tmp_split[i])
	{
		free(tmp_split[i]);
		i++;
	}
	free(tmp_split);
	return res;
}
