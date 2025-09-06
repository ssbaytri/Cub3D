/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 17:05:06 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/09/06 18:22:59 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int	flood_fill(t_map *map, int y, int x, int **visited)
{
	if (x < 0 || y < 0 || x >= map->width || y >= map->height)
		return (0);
	if (map->grid[y][x] == ' ')
		return (0);
	if (map->grid[y][x] == '1')
		return (1);
	if (visited[y][x])
		return (1);
	visited[y][x] = 1;
	if (!flood_fill(map, y + 1, x, visited))
		return (0);
	if (!flood_fill(map, y - 1, x, visited))
		return (0);
	if (!flood_fill(map, y, x + 1, visited))
		return (0);
	if (!flood_fill(map, y, x - 1, visited))
		return (0);
	return (1);
}

int	validate_closed_map(t_map *map)
{
	int	**visited;
	int	i;
	int	result;

	visited = malloc(sizeof(int *) * map->height);
	if (!visited)
		return (0);
	i = 0;
	while (i < map->height)
	{
		visited[i] = ft_calloc(map->width, sizeof(int));
		if (!visited[i])
			return (0);
		i++;
	}
	result = flood_fill(map, map->player_pos.y, map->player_pos.x, visited);
	i = 0;
	while (i < map->height)
	{
		free(visited[i]);
		i++;
	}
	free(visited);
	return (result);
}
