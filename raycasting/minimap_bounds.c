/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bounds.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 08:13:30 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/10/22 08:13:42 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	calculate_world_bounds(t_data *data, t_minimap_bounds *bounds)
{
	double	world_radius;

	bounds->player_x = data->player->pos->x;
	bounds->player_y = data->player->pos->y;
	bounds->center_x = (double)(MINIMAP_OFFSET_X + MINIMAP_SIZE / 2);
	bounds->center_y = (double)(MINIMAP_OFFSET_Y + MINIMAP_SIZE / 2);
	world_radius = (MINIMAP_SIZE / 2.0) * MINIMAP_SCALE;
	bounds->world_start_x = bounds->player_x - world_radius;
	bounds->world_start_y = bounds->player_y - world_radius;
	bounds->world_end_x = bounds->player_x + world_radius;
	bounds->world_end_y = bounds->player_y + world_radius;
}

void	calculate_tile_bounds(t_minimap_bounds *bounds, t_tile_bounds *tiles)
{
	tiles->start_x = (int)floor(bounds->world_start_x / TILE_SIZE);
	tiles->start_y = (int)floor(bounds->world_start_y / TILE_SIZE);
	tiles->end_x = (int)floor(bounds->world_end_x / TILE_SIZE);
	tiles->end_y = (int)floor(bounds->world_end_y / TILE_SIZE);
	if (tiles->start_x < -1)
		tiles->start_x = -1;
	if (tiles->start_y < -1)
		tiles->start_y = -1;
}

int	calculate_tile_pixel_size(void)
{
	double	tile_pixel_size_f;
	int		tile_pixel_size_i;

	tile_pixel_size_f = (double)TILE_SIZE / MINIMAP_SCALE;
	tile_pixel_size_i = (int)ceil(tile_pixel_size_f);
	if (tile_pixel_size_i < 1)
		tile_pixel_size_i = 1;
	return (tile_pixel_size_i);
}
