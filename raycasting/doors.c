/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 03:10:40 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/10/23 05:01:47 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int	count_doors(t_data *data)
{
	int	count;
	int	i;
	int	j;

	count = 0;
	i = 0;
	while (i < data->map.height)
	{
		j = 0;
		while (j < data->map.width)
		{
			if (data->map.grid[i][j] == 'D')
				count++;
			j++;
		}
		i++;
	}
	return (count);
}

void	find_all_doors(t_data *data)
{
	int	count;
	int	i;
	int	j;

	count = count_doors(data);
	data->door_list.count = count;
	data->door_list.doors = ft_calloc(count, sizeof(t_door));
	count = 0;
	i = 0;
	while (i < data->map.height)
	{
		j = 0;
		while (j < data->map.width)
		{
			if (data->map.grid[i][j] == 'D')
			{
				data->door_list.doors[count].x = j;
				data->door_list.doors[count].y = i;
				data->door_list.doors[count].is_open = 0;
				count++;
			}
			j++;
		}
		i++;
	}
}

static t_point	calculate_check_position(t_data *data)
{
	double	check_dist;
	t_pos	check_pos;
	t_point	map_pos;

	check_dist = TILE_SIZE * 1.5;
	check_pos.x = data->player->pos->x + cos(data->player->player_angle)
		* check_dist;
	check_pos.y = data->player->pos->y + sin(data->player->player_angle)
		* check_dist;
	map_pos.x = (int)(check_pos.x / TILE_SIZE);
	map_pos.y = (int)(check_pos.y / TILE_SIZE);
	return (map_pos);
}

t_door	*find_nearest_door(t_data *data)
{
	t_point	map_pos;
	int		i;

	i = 0;
	map_pos = calculate_check_position(data);
	if (map_pos.y >= 0 && map_pos.y < data->map.height && map_pos.x >= 0
		&& map_pos.x < data->map.width
		&& data->map.grid[map_pos.y][map_pos.x] == 'D')
	{
		i = 0;
		while (i < data->door_list.count)
		{
			if (data->door_list.doors[i].x == map_pos.x
				&& data->door_list.doors[i].y == map_pos.y)
				return (&data->door_list.doors[i]);
			i++;
		}
	}
	return (NULL);
}
