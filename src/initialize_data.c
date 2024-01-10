/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 09:34:24 by rmarquar          #+#    #+#             */
/*   Updated: 2024/01/10 15:41:51 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	texinfo_initialize(t_texinfo *textures)
{
	textures->size = TEX_SIZE;
	textures->north = NULL;
	textures->south = NULL;
	textures->west = NULL;
	textures->east = NULL;
	textures->floor_color = 0;
	textures->ceiling_color = 0;
	textures->floor = 0;
	textures->ceiling = 0;
	textures->x = 0;
	textures->y = 0;
	textures->step = 0.0;
	textures->pos = 0.0;
}

static void	mapinfo_initialize(t_mapinfo *mapinfo)
{
	mapinfo->fd = 0;
	mapinfo->line_count = 0;
	mapinfo->path = NULL;
	mapinfo->file = NULL;
	mapinfo->height = 0;
	mapinfo->width = 0;
	mapinfo->index_end_of_map = 0;
}

static void	player_initialize(t_player *player)
{
	player->dir = '\0';
	player->dir_x = 0.0;
	player->dir_y = 0.0;
	player->pos_x = 0.0;
	player->pos_y = 0.0;
	player->move_x = 0;
	player->move_y = 0;
	player->plane_x = 0.0;
	player->plane_y = 0.0;
	player->has_moved = 0;
	player->rotate = 0;
}

void	data_initialize(t_data *data)
{
	data->mlx = NULL;
	// data->win = NULL;
	data->win_height = WIN_HEIGHT;
	data->win_width = WIN_WIDTH;
	data->texture_pixels = NULL;
	data->textures = NULL;
	player_initialize(&data->player);
	mapinfo_initialize(&data->mapinfo);
	texinfo_initialize(&data->texinfo);
}
