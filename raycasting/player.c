/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naessgui <naessgui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 13:27:20 by naessgui          #+#    #+#             */
/*   Updated: 2025/10/09 19:59:34 by naessgui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

float	find_player_angle(t_data *data)
{
	if (data->map.player_dir == 'N')
		data->player->player_angle = (3 * M_PI) / 2;
	else if (data->map.player_dir == 'S')
		data->player->player_angle = M_PI / 2 ;
	else if (data->map.player_dir == 'W')
		data->player->player_angle = M_PI;
	else if (data->map.player_dir == 'E')
		data->player->player_angle = 0;
	return (data->player->player_angle);
}

void	init_player(t_data *data)
{
	data->player = malloc(sizeof(t_player));
	data->player->pos = malloc(sizeof(t_pos));
	data->player->pos->x = (data->map.player_pos.x + 0.5) * tile_size;
	data->player->pos->y = (data->map.player_pos.y + 0.5) * tile_size;
	data->player->walk_dir = 0;
	data->player->turn_dir = 0;
	data->player->move_speed = 3.0;
	data->player->rot_speed = 3 * (M_PI / 180);
	data->player->color = 0xFF0000FF;
	data->player->radius = 4;
	data->player->rot_direction = 0;
	data->player->player_angle = find_player_angle(data);
}

void	draw_player(mlx_image_t *img, t_data *data)
{
	int	y;
	int	x;
	int	px;
	int	py;

	y = -data->player->radius;
	while (y <= data->player->radius)
	{
		x = -data->player->radius;
		while (x <= data->player->radius)
		{
			if (x * x + y * y <= data->player->radius * data->player->radius)
			{
				px = data->player->pos->x + x;
				py = data->player->pos->y + y;
				if (px >= 0 && py >= 0 && px < (int)img->width
					&& py < (int)img->height)
					mlx_put_pixel(img, px, py, data->player->color);
			}
			x++;
		}
		y++;
	}
}

// void	draw_player_line(t_data *data)
// {
// 	int	start_x;
// 	int	start_y;
// 	int	x;
// 	int	y;
// 	int	i;

// 	start_x = data->player->pos->x;
// 	start_y = data->player->pos->y;
// 	i = 0;
// 	while (i < 50)
// 	{
// 		x = start_x + cos(data->player->player_angle) * i;
// 		y = start_y + sin(data->player->player_angle) * i;
// 		if (x >= 0 && x < data->Mlx.win_w && y >= 0 && y < (int)data->Mlx.win_h)
// 			mlx_put_pixel(data->Mlx.img, x, y, 0xFF00FFFF);
// 		i++;
// 	}
// }
void    draw_player_line(t_data *data, int x1, int y1, int x2, int y2)
{
    int dx = abs(x2 - x1);
    int sx = x1 < x2 ? 1 : -1;
    int dy = -abs(y2 - y1);
    int sy = y1 < y2 ? 1 : -1;
    int err = dx + dy;
    int e2;

    while (1)
    {
		if (x1 >= 0 && x1 < data->Mlx.win_w && y1 >= 0 && y1 < (int)data->Mlx.win_h)
			mlx_put_pixel(data->Mlx.img, x1, y1, 0xFF00FFFF);
        if (x1 == x2 && y1 == y2)
            break;
        e2 = 2 * err;
        if (e2 >= dy)
        {
            err += dy;
            x1 += sx;
        }
        if (e2 <= dx)
        {
            err += dx;
            y1 += sy;
        }
    }
}
