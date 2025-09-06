/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 14:55:25 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/09/06 18:22:50 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int	is_map_line_valid(char *line)
{
	int	i;

	if (!line)
		return (0);
	i = 0;
	while (line[i])
	{
		if (line[i] != '0' && line[i] != '1' && line[i] != 'N' && line[i] != 'S'
			&& line[i] != 'E' && line[i] != 'W' && line[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

int	player_exists(t_map *map)
{
	int	i;
	int	j;
	int	total_occ;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (map->grid[i][j] == 'N')
				map->dir_count.n++;
			if (map->grid[i][j] == 'S')
				map->dir_count.s++;
			if (map->grid[i][j] == 'W')
				map->dir_count.w++;
			if (map->grid[i][j] == 'E')
				map->dir_count.e++;
			j++;
		}
		i++;
	}
	total_occ = map->dir_count.n + map->dir_count.s + map->dir_count.w
		+ map->dir_count.e;
	return (total_occ == 1);
}

int	extract_player_info(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (map->grid[i][j] == 'N' || map->grid[i][j] == 'S'
				|| map->grid[i][j] == 'W' || map->grid[i][j] == 'E')
			{
				map->player_pos.y = i;
				map->player_pos.x = j;
				map->player_dir = map->grid[i][j];
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	validate_map(t_map *map)
{
	map->grid = list_to_2d(map->list, &map->height, &map->width);
	if (!map->grid)
		return (0);
	if (!player_exists(map))
		return (free2d(map->grid), 0);
	if (!extract_player_info(map))
		return (free2d(map->grid), 0);
	if (!validate_closed_map(map))
		return (free2d(map->grid), 0);
	free2d(map->grid);
	free_map_list(map->list);
	return (1);
}
