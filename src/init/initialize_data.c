/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 09:34:24 by rmarquar          #+#    #+#             */
/*   Updated: 2024/01/15 20:06:42 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void ray_init(t_ray *ray)
{
	ray->camera_x = 0;
	ray->dir_x = 0;
	ray->dir_y = 0;
	ray->map_x = 0;
	ray->map_y = 0;
	ray->step_x = 0;
	ray->step_y = 0;
	ray->sidedist_x = 0;
	ray->sidedist_y = 0;
	ray->deltadist_x = 0;
	ray->deltadist_y = 0;
	ray->wall_dist = 0;
	ray->wall_x = 0;
	ray->line_height = 0;	
	ray->draw_start = 0;
	ray->draw_end = 0;
}
static void	texinfo_initialize(t_texinfo *textures)
{
	textures->size = TEX_SIZE;
	textures->north = NULL;
	textures->south = NULL;
	textures->west = NULL;
	textures->east = NULL;
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
	mapinfo->map = NULL;
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
	player->rotate = 0.01;
	player->speed = 1;
}

void	data_initialize(t_data *data)
{
	data->mlx = NULL;
	data->win_height = WIN_HEIGHT;
	data->win_width = WIN_WIDTH;
	data->texture_pixels = NULL;
	data->colors = NULL;
	player_initialize(&data->player);
	mapinfo_initialize(&data->mapinfo);
	texinfo_initialize(&data->texinfo);
	ray_init(&data->ray);
	
}
