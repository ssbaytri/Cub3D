/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 21:39:59 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/10/16 22:02:12 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

mlx_texture_t	*get_wall_texture(t_data *data, int stripid)
{
	double	ray_angle;

	ray_angle = data->ray[stripid].ray_angle;
	if (data->ray[stripid].was_vert_hit)
	{
		if (ray_angle > M_PI / 2 && ray_angle < 3 * M_PI / 2)
			return (data->textures.west);
		else
			return (data->textures.east);
	}
	else
	{
		if (ray_angle > 0 && ray_angle < M_PI)
			return (data->textures.south);
		else
			return (data->textures.north);
	}
}

double	get_texture_offset(t_data *data, int stripid)
{
	double	hit_x;
	double	hit_y;
	double	offset;

	hit_x = data->ray[stripid].wall_hit_x;
	hit_y = data->ray[stripid].wall_hit_y;
	if (data->ray[stripid].was_vert_hit)
		offset = fmod(hit_y, TILE_SIZE);
	else
		offset = fmod(hit_x, TILE_SIZE);
	return (offset / TILE_SIZE);
}

uint32_t	get_texture_color(mlx_texture_t *texture, int x, int y)
{
	int		index;
	uint8_t	*pixels;
	uint8_t	rgba[4];

	if (x < 0)
		x = 0;
	if (x >= (int)texture->width2)
		x = texture->width2 - 1;
	if (y < 0)
		y = 0;
	if (y >= (int)texture->height2)
		y = texture->height2 - 1;
	index = (y * texture->width2 + x) * 4;
	pixels = texture->pixels;
	rgba[0] = pixels[index];
	rgba[1] = pixels[index + 1];
	rgba[2] = pixels[index + 2];
	rgba[3] = pixels[index + 3];
	return ((rgba[0] << 24) | (rgba[1] << 16) | (rgba[2] << 8) | rgba[3]);
}

uint32_t	create_trgb(int *rgb)
{
	return ((rgb[0] << 24) | (rgb[1] << 16) | (rgb[2] << 8) | 0xFF);
}
