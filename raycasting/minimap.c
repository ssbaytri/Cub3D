/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 08:14:51 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/10/23 01:52:31 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

static int	is_tile_visible(int screen_x, int screen_y, int tile_size)
{
	if (screen_x + tile_size < MINIMAP_OFFSET_X)
		return (0);
	if (screen_x > MINIMAP_OFFSET_X + MINIMAP_SIZE - 1)
		return (0);
	if (screen_y + tile_size < MINIMAP_OFFSET_Y)
		return (0);
	if (screen_y > MINIMAP_OFFSET_Y + MINIMAP_SIZE - 1)
		return (0);
	return (1);
}

static uint32_t	get_tile_color(t_data *data, double tile_x, double tile_y)
{
	double	check_x;
	double	check_y;

	check_x = tile_x + 0.5 * TILE_SIZE;
	check_y = tile_y + 0.5 * TILE_SIZE;
	if (check_x >= 0 && check_y >= 0 && has_wall_at(data, (float)check_x,
			(float)check_y))
		return (0x808080FF);
	return (0xD3D3D3FF);
}

static void	draw_tile(t_data *data, t_tile_draw *d)
{
	double		tile_world_x;
	double		tile_world_y;
	double		screen_x_f;
	double		screen_y_f;
	uint32_t	color;

	tile_world_x = (double)d->tx * (double)TILE_SIZE;
	tile_world_y = (double)d->ty * (double)TILE_SIZE;
	screen_x_f = d->bounds.center_x + (tile_world_x - d->bounds.player_x)
		/ MINIMAP_SCALE;
	screen_y_f = d->bounds.center_y + (tile_world_y - d->bounds.player_y)
		/ MINIMAP_SCALE;
	d->screen_x = (int)round(screen_x_f);
	d->screen_y = (int)round(screen_y_f);
	if (!is_tile_visible(d->screen_x, d->screen_y, d->tile_size))
		return ;
	color = get_tile_color(data, tile_world_x, tile_world_y);
	draw_rect(data->mlx.img, (t_point){d->screen_x, d->screen_y},
		(t_point){d->tile_size, d->tile_size}, color);
}

static void	draw_all_tiles(t_data *data, t_minimap_bounds *b, t_tile_bounds *t,
		int tile_size)
{
	t_tile_draw	d;

	d.bounds = *b;
	d.tile_size = tile_size;
	d.ty = t->start_y;
	while (d.ty <= t->end_y)
	{
		d.tx = t->start_x;
		while (d.tx <= t->end_x)
		{
			draw_tile(data, &d);
			d.tx++;
		}
		d.ty++;
	}
}

void	render_minimap(t_data *data)
{
	t_minimap_bounds	b;
	t_tile_bounds		t;
	int					tile_px;

	draw_rect(data->mlx.img, (t_point){MINIMAP_OFFSET_X, MINIMAP_OFFSET_Y},
		(t_point){MINIMAP_SIZE + 28, MINIMAP_SIZE + 28}, BLACK);
	calculate_world_bounds(data, &b);
	calculate_tile_bounds(&b, &t);
	tile_px = calculate_tile_pixel_size();
	draw_all_tiles(data, &b, &t, tile_px);
	render_minimap_player(data);
	draw_minimap_frame(data);
}
