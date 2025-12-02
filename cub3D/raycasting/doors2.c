/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 05:12:12 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/10/23 05:12:33 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int	find_door_at(t_data *data, int map_x, int map_y)
{
	int	i;

	i = 0;
	while (i < data->door_list.count)
	{
		if (data->door_list.doors[i].x == map_x
			&& data->door_list.doors[i].y == map_y)
			return (i);
		i++;
	}
	return (-1);
}

uint32_t	get_door_color(t_data *data, int door_index)
{
	if (data->door_list.doors[door_index].is_open)
		return (0x00FF00FF);
	return (0xFF0000FF);
}
