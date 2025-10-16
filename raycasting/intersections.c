/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 18:19:40 by naessgui          #+#    #+#             */
/*   Updated: 2025/10/16 21:52:12 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

static double	distance(double x1, double y1, double x2, double y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

static void	find_horizontal_wall(t_data *data, int i, double x_step,
		double y_step)
{
	while (1)
	{
		if (has_wall_at(data, data->ray[i].x_horizontal,
				data->ray[i].y_horizontal))
		{
			data->ray[i].found_horz_wall_hit = 1;
			data->ray[i].horz_wallhit_x = data->ray[i].x_horizontal;
			data->ray[i].horz_wallhit_y = data->ray[i].y_horizontal;
			break ;
		}
		else
		{
			data->ray[i].y_horizontal += y_step;
			data->ray[i].x_horizontal += x_step;
		}
	}
}

static void	find_vertical_wall(t_data *data, int i, double x_step,
		double y_step)
{
	while (1)
	{
		if (has_wall_at(data, data->ray[i].x_vertical, data->ray[i].y_vertical))
		{
			data->ray[i].found_vert_wall_hit = 1;
			data->ray[i].vert_wallhit_x = data->ray[i].x_vertical;
			data->ray[i].vert_wallhit_y = data->ray[i].y_vertical;
			break ;
		}
		else
		{
			data->ray[i].x_vertical += x_step;
			data->ray[i].y_vertical += y_step;
		}
	}
}

void	horizontal_intersections(t_data *data, t_player *p, int i)
{
	double	y_step;
	double	x_step;

	y_step = TILE_SIZE;
	if (sin(data->ray[i].ray_angle) > 0)
	{
		data->ray[i].y_horizontal = ((int)p->pos->y / TILE_SIZE) * TILE_SIZE
			+ TILE_SIZE;
		y_step *= 1;
	}
	if (sin(data->ray[i].ray_angle) < 0)
	{
		data->ray[i].y_horizontal = ((int)p->pos->y / TILE_SIZE) * TILE_SIZE
			- EPSILON;
		y_step *= -1;
	}
	data->ray[i].x_horizontal = p->pos->x + (data->ray[i].y_horizontal
			- p->pos->y) / tan(data->ray[i].ray_angle);
	x_step = y_step / tan(data->ray[i].ray_angle);
	find_horizontal_wall(data, i, x_step, y_step);
	if (data->ray[i].found_horz_wall_hit)
		data->ray[i].horz_hitdistance = distance(p->pos->x, p->pos->y,
				data->ray[i].horz_wallhit_x, data->ray[i].horz_wallhit_y);
}

void	vertical_intersections(t_data *data, t_player *p, int i)
{
	double	x_step;
	double	y_step;

	x_step = TILE_SIZE;
	if (cos(data->ray[i].ray_angle) > 0)
	{
		data->ray[i].x_vertical = ((int)p->pos->x / TILE_SIZE) * TILE_SIZE
			+ TILE_SIZE;
		x_step *= 1;
	}
	if (cos(data->ray[i].ray_angle) < 0)
	{
		data->ray[i].x_vertical = ((int)p->pos->x / TILE_SIZE) * TILE_SIZE
			- EPSILON;
		x_step *= -1;
	}
	data->ray[i].y_vertical = p->pos->y + (data->ray[i].x_vertical - p->pos->x)
		* tan(data->ray[i].ray_angle);
	y_step = x_step * tan(data->ray[i].ray_angle);
	find_vertical_wall(data, i, x_step, y_step);
	if (data->ray[i].found_vert_wall_hit)
		data->ray[i].vert_hitdistance = distance(p->pos->x, p->pos->y,
				data->ray[i].vert_wallhit_x, data->ray[i].vert_wallhit_y);
}
