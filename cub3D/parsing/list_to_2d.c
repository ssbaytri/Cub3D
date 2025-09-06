/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_to_2d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 13:16:52 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/09/06 14:54:10 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

char	**allocate_grid(int height, int width)
{
	char	**grid;
	int		i;

	if (height <= 0 || width <= 0)
		return (NULL);
	grid = malloc(sizeof(char *) * (height + 1));
	if (!grid)
		return (NULL);
	i = 0;
	while (i < height)
	{
		grid[i] = malloc(width + 1);
		if (!grid[i])
		{
			while (--i >= 0)
				free(grid[i]);
			free(grid);
			return (NULL);
		}
		i++;
	}
	grid[height] = NULL;
	return (grid);
}

void	fill_grid(char *grid_row, char *line, int width)
{
	int	j;
	int	line_len;

	line_len = ft_strlen(line);
	j = 0;
	while (j < line_len && j < width)
	{
		grid_row[j] = line[j];
		j++;
	}
	while (j < width)
	{
		grid_row[j] = ' ';
		j++;
	}
	grid_row[width] = '\0';
}

char	**convert_list_to_2d(t_map_list *head, int height, int width)
{
	char		**grid;
	t_map_list	*curr;
	int			i;

	grid = allocate_grid(height, width);
	if (!grid)
		return (NULL);
	curr = head;
	i = 0;
	while (curr && i < height)
	{
		fill_grid(grid[i], curr->line, width);
		curr = curr->next;
		i++;
	}
	return (grid);
}

char	**list_to_2d(t_map_list *head, int *final_height, int *final_width)
{
	int		height;
	int		width;
	char	**map;

	if (!head)
		return (NULL);
	height = map_height(head);
	width = map_max_width(head);
	if (height == 0 || width == 0)
		return (NULL);
	map = convert_list_to_2d(head, height, width);
	if (map && final_height && final_width)
	{
		*final_height = height;
		*final_width = width;
	}
	return (map);
}
