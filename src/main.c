/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 12:45:20 by jkulka            #+#    #+#             */
/*   Updated: 2024/01/13 22:20:47 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	print_controls()
{
	printf("Glueckwunsch. Ihr habt es jetzt bis hierher geschafft :-)");
	printf("\n");
}
void drawCircle(t_data *data, int centerX, int centerY, int radius, int color)
{
int x, y;
    for(y = -radius; y <= radius; y++)
    {
        for(x = -radius; x <= radius; x++)
        {
            if(x*x + y*y <= radius*radius)
            {
                mlx_put_pixel(data->img, centerX + x, centerY + y, color);
            }
        }
    }
}

void drawMap(t_data *data)
{
    int i, j, x, y;
    for(i = 0; data->mapinfo.map[i]; i++)
    {
        for(j = 0; data->mapinfo.map[i][j]; j++)
        {
            // Choose a color based on the cell's value
            int color = (data->mapinfo.map[i][j] == '0') ? data->colors[FLOOR] : data->colors[CEILING];
			if(data->mapinfo.map[i][j] == '-')
				color = get_rgba(255, 255, 255, 255);
			else if(data->mapinfo.map[i][j] == '\n')
				color = get_rgba(255, 255, 255, 255);
            for(y = 0; y < 64; y++)
            {
                for(x = 0; x < 64; x++)
                {
					mlx_put_pixel(data->img, j * 64 + x, i * 64, get_rgba(0, 0, 0, 255)); // Horizontal line
                mlx_put_pixel(data->img, j * 64, i * 64 + x, get_rgba(0, 0, 0, 255)); // Vertical line	
					mlx_put_pixel(data->img, j * 64 + x, i * 64 + y, color);
				}
            }
        }
    }
	// data->player.pos_x = 2;
	// printf("\t%f;%f\n", data->player.pos_x, data->player.pos_y);
}

void k_hook(mlx_key_data_t key, void *v_data)
{
	t_data *data = v_data;
	if(key.key == MLX_KEY_W)
	{
		data->player.pos_y -= 5;
		data->player.has_moved = true;
	}
	else if(key.key == MLX_KEY_S)
	{
		data->player.pos_y += 5;
		data->player.has_moved = true;	
	}
	else if(key.key == MLX_KEY_A)
	{
		data->player.pos_x -= 5;
		data->player.has_moved = true;
	}
	else if(key.key == MLX_KEY_D)
	{
		data->player.pos_x += 5;
		data->player.has_moved = true;
	}
}

void drawThickLine(t_data *data, int x1, int y1, int x2, int y2, int thickness, int color, bool dashed)
{
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;
    int dash_length = 10;
    int space_length = 10;
    int counter = 0;
    bool draw = true;

    while (1)
    {
        if (dashed)
        {
            if (counter % (dash_length + space_length) < dash_length)
                draw = true;
            else
                draw = false;
        }

        if (draw)
        {
            for (int i = -thickness; i <= thickness; i++)
            {
                for (int j = -thickness; j <= thickness; j++)
                {
                    if (i * i + j * j <= thickness * thickness)
                    {
                        mlx_put_pixel(data->img, x1 + i, y1 + j, color);
                    }
                }
            }
        }

        if (x1 == x2 && y1 == y2)
            break;

        int e2 = 2 * err;
        if (e2 > -dy)
        {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx)
        {
            err += dx;
            y1 += sy;
        }

        counter++;
    }
}

void hook(void *v_data)
{
	int32_t old_x, old_y;
	t_data *data = v_data;

	old_x = data->m_x;
	old_y = data->m_y;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
	if(data->player.has_moved == true || data->m_x != old_x || data->m_y != old_x)
	{
		ft_clear(data);
		drawMap(data);
		drawCircle(data, data->player.pos_x + 15, data->player.pos_y + 15, 15, get_rgba(255, 2, 2, 255));
		mlx_image_to_window(data->mlx, data->img, 0, 0);
		data->player.has_moved = false;
		if((!(data->m_x <= 0 || data->m_x >= 1920) && !(data->m_y <= 0 || data->m_y >= 1080)))
		{
			drawCircle(data, data->m_x, data->m_y, 10, get_rgba(0, 120, 255, 255));
			drawThickLine(data, data->player.pos_x + 16, data->player.pos_y + 16, data->m_x, data->m_y, 1, get_rgba(0, 255, 255, 255), true);
			
		}
		old_x = data->m_x;
		old_y = data->m_y;
	}
	// mlx_put_pixel(data->img, 100, 100, data->colors]);
		data->player.has_moved = false;
	mlx_get_mouse_pos(data->mlx, &(data->m_x), &(data->m_y));
	
	
	// ft_printf("\tx: %d\t y: %d\n", x, y);
	//TODO Render function implementieren.
}
void init_render(t_data *data)
{
	ft_clear(data);
	drawMap(data);
	drawCircle(data, data->player.pos_x + 15, data->player.pos_y + 15, 15, get_rgba(255, 2, 2, 255));
	mlx_image_to_window(data->mlx, data->img, 0, 0);
}
int	main(int argc, char **argv)
{
	t_data	data;

	data_initialize(&data);						//Initialisiere die Datenstruktur
	parse_arguments(argv[1], &data);			//Parse die Argumente
	init_mlx(&data);							//Initialisiere die MLX-Bibliothek @Jens: bin heute bis hierher gekommen. Lass uns aber das "parse_arguments" nochmal gemeinsam anschauen. Bin mir das noch nicht so ganz sicher. Bis Morgen. Gruss Robin :-)
	init_textures(&data);						//Lade Texturen
	print_controls();
	init_render(&data);
	// render_images(&data);						//Rendere die Bilder
	// listen_for_input(&data);
	mlx_key_hook(data.mlx, k_hook, &data);

	mlx_loop_hook(data.mlx, hook, &data);	//Höre auf Benutzereingaben
	mlx_loop(data.mlx);							//Starte die MLX-Loop
	return (0);
}
