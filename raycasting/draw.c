/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 12:49:21 by naessgui          #+#    #+#             */
/*   Updated: 2025/10/16 22:35:45 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

static void	init_render_data(t_data *data, int stripid, t_render *render)
{
	double	projection_plane;

	render->corrected_distance = data->ray[stripid].distance
		* cos(data->ray[stripid].ray_angle - data->player->player_angle);
	projection_plane = (data->mlx.win_w / 2) / tan((FOV_ANGLE * M_PI / 180)
			/ 2);
	render->wall_h = (TILE_SIZE / render->corrected_distance)
		* projection_plane;
	render->wall_top_unclamped = (data->mlx.win_h / 2) - (render->wall_h / 2);
	render->wall_bottom_unclamped = (data->mlx.win_h / 2) + (render->wall_h
			/ 2);
	render->texture = get_wall_texture(data, stripid);
	render->tex_offset = get_texture_offset(data, stripid);
	render->tex_x = (int)(render->tex_offset * render->texture->width2);
	render->x = stripid * WALL_STRIP_WIDTH;
}

static void	clamp_wall_heights(t_data *data, t_render *render)
{
	render->wall_top = render->wall_top_unclamped;
	render->wall_bottom = render->wall_bottom_unclamped;
	if (render->wall_top < 0)
		render->wall_top = 0;
	if (render->wall_bottom >= data->mlx.win_h)
		render->wall_bottom = data->mlx.win_h - 1;
}

static void	render_textured_wall(t_data *data, t_render *render)
{
	int	y;
	int	distance_from_top;
	int	tex_y;
	int	x;

	x = render->x;
	y = render->wall_top;
	while (y <= render->wall_bottom)
	{
		if (y >= 0 && y < data->mlx.win_h)
		{
			distance_from_top = y - render->wall_top_unclamped;
			tex_y = (int)((double)distance_from_top / render->wall_h
					* render->texture->height2);
			mlx_put_pixel(data->mlx.img, x, y,
				get_texture_color(render->texture, render->tex_x, tex_y));
		}
		y++;
	}
}

static void	draw_ceiling_and_floor(t_data *data, int stripid, t_render *render)
{
	int	y;
	int	x;

	x = stripid * WALL_STRIP_WIDTH;
	y = 0;
	while (y < render->wall_top)
	{
		mlx_put_pixel(data->mlx.img, x, y, create_trgb(data->cfg.ceil_rgb));
		y++;
	}
	y = render->wall_bottom + 1;
	while (y < data->mlx.win_h)
	{
		mlx_put_pixel(data->mlx.img, x, y, create_trgb(data->cfg.floor_rgb));
		y++;
	}
}

void	render_wall_strip(t_data *data, int stripid)
{
	t_render	render;

	init_render_data(data, stripid, &render);
	clamp_wall_heights(data, &render);
	render_textured_wall(data, &render);
	draw_ceiling_and_floor(data, stripid, &render);
}
