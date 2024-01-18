/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 13:06:59 by jkulka            #+#    #+#             */
/*   Updated: 2024/01/18 13:58:09 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

// typedef struct s_img
// {
// 	void	*img;
// 	int		*addr;
// 	int		pixel_bits;
// 	int		size_line;
// 	int		endian;
// }	t_img;

typedef struct s_texinfo
{
	char		*north;
	char		*south;
	char		*west;
	char		*east;
	char		*floor;
	char		*ceiling;
	int			size;
	int			side;
	double		step;
	double		pos;
	int			x;
	int			y;
}				t_texinfo;

typedef struct s_mapinfo
{
	int			fd;
	int			line_count;
	char		*path;
	char		**file;
	int			height;
	int			width;
	int			index_end_of_map;
	char		**map;
}				t_mapinfo;

typedef struct s_ray
{
	double		camera_x;
	double		dir_x;
	double		dir_y;
	int			map_x;
	int			map_y;
	int			step_x;
	int			step_y;
	double		sidedist_x;
	double		sidedist_y;
	double		deltadist_x;
	double		deltadist_y;
	double		wall_dist;
	double		wall_x;
	int			side;
	int			line_height;
	int			draw_start;
	int			draw_end;
}				t_ray;

typedef struct s_player
{
	char		dir;
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	int			has_moved;
	int			move_x;
	int			move_y;
	double		rotate;
	double		speed;
}				t_player;

typedef struct s_data
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	int			win_height;
	int			win_width;
	t_mapinfo	mapinfo;
	t_player	player;
	t_ray		ray;
	int			**texture_pixels;
	mlx_image_t	*textures[4];
	int			*colors;
	int			color;
	t_texinfo	texinfo;
}				t_data;

typedef enum e_etype
{
	MLX = 0,
	MALLOC
}				t_etype;

typedef enum e_dir
{
	NORTH = 0,
	SOUTH,
	EAST,
	WEST
}				t_dir;

typedef enum e_color
{
	FLOOR = 0,
	CEILING
}				t_color;

#endif
