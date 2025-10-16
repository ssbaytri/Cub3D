/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 13:27:20 by naessgui          #+#    #+#             */
/*   Updated: 2025/10/16 21:03:59 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

static float	find_player_angle(t_data *data)
{
	if (data->map.player_dir == 'N')
		data->player->player_angle = (3 * M_PI) / 2;
	else if (data->map.player_dir == 'S')
		data->player->player_angle = M_PI / 2;
	else if (data->map.player_dir == 'W')
		data->player->player_angle = M_PI;
	else if (data->map.player_dir == 'E')
		data->player->player_angle = 0;
	return (data->player->player_angle);
}

void	init_player(t_data *data)
{
	data->player = ft_calloc(1, sizeof(t_player));
	data->player->pos = ft_calloc(1, sizeof(t_pos));
	data->player->pos->x = (data->map.player_pos.x + 0.5) * TILE_SIZE;
	data->player->pos->y = (data->map.player_pos.y + 0.5) * TILE_SIZE;
	data->player->walk_dir = 0;
	data->player->turn_dir = 0;
	data->player->move_speed = 3.0;
	data->player->rot_speed = 3 * (M_PI / 180);
	data->player->color = 0xFF0000FF;
	data->player->radius = 4;
	data->player->rot_direction = 0;
	data->player->player_angle = find_player_angle(data);
}
