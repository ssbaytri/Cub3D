/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naessgui <naessgui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 13:27:20 by naessgui          #+#    #+#             */
/*   Updated: 2025/09/10 14:25:18 by naessgui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../cub.h"

void init_player(t_data *data)
{
    data->player.pos_x = ( data->map.player_pos.x + 0.5) * tile_size;
    data->player.pos_y = ( data->map.player_pos.y + 0.5) * tile_size;
    data->player.walk_dir = 0;
    data->player.turn_dir = 0;
    data->player.move_speed = 3.0;
    data->player.rot_speed = 3 * (M_PI / 180);
    data->player.color = 0xFF0000FF;
    data->player.radius = 4;
    data->player.rot_angle = 45 * (M_PI/180);
}
void	draw_player(mlx_image_t *img, t_data *data)
{
	int	y;
	int	x;
	int	px; 
	int	py;

	y = -data->player.radius;
	while (y <= data->player.radius)
	{
		x = -data->player.radius;
		while (x <= data->player.radius)
		{
			if (x * x + y * y <= data->player.radius * data->player.radius)
			{
				px = data->player.pos_x + x;
				py = data->player.pos_y + y;
				if (px >= 0 && py >= 0 && px < (int)img->width
					&& py < (int)img->height)
					mlx_put_pixel(img, px, py, data->player.color);
			}
			x++;
		}
		y++;
	}
}
void draw_player_line(t_data *data)
{
    int x;
    int y;
    int length ;
    int i;
    int end_x;
    int end_y;
    
    x = (int)data->player.pos_x;
    y = (int)data->player.pos_y;
    length = 50;
    i = 0;
    while  ( i < length)
    {
        end_x = x + cos(data->player.rot_angle) * i;
        end_y = y + sin(data->player.rot_angle) * i;

        if (end_x >= 0 && end_y >= 0 &&
            end_x < data->Mlx.win_w &&
            end_y < (int)data->Mlx.win_h)
            mlx_put_pixel(data->Mlx.img, end_x, end_y, 0xFF00FFFF);
        i++;
    }
}

