/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 13:21:57 by naessgui          #+#    #+#             */
/*   Updated: 2025/10/23 03:20:46 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	window_size(t_data *data)
{
	data->mlx.win_h = WINDOW_HEIGHT;
	data->mlx.win_w = WINDOW_WIDTH;
}

int	has_wall_at(t_data *data, float x, float y)
{
	int	map_x;
	int	map_y;
	int	count;

	map_x = (int)(x / TILE_SIZE);
	map_y = (int)(y / TILE_SIZE);
	if (map_x < 0 || map_x >= data->map.width || map_y < 0
		|| map_y >= data->map.height)
		return (1);
	if (data->map.grid[map_y][map_x] == '1')
		return (1);
	if (data->map.grid[map_y][map_x] == 'D')
	{
		count = 0;
		while (count < data->door_list.count)
		{
			if (data->door_list.doors[count].x == map_x
				&& data->door_list.doors[count].y == map_y)
				return (!data->door_list.doors[count].is_open);
			count++;
		}
		return (1);
	}
	return (0);
}

void	wall_collision(t_data *data, double new_x, double new_y)
{
	if (!has_wall_at(data, data->player->pos->x + new_x, data->player->pos->y))
		data->player->pos->x += new_x;
	if (!has_wall_at(data, data->player->pos->x, data->player->pos->y + new_y))
		data->player->pos->y += new_y;
	return ;
}
