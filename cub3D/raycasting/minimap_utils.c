/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 08:11:00 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/10/22 08:16:52 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

static int	clip_rect_bounds(mlx_image_t *img, t_point *start, t_point *end)
{
	if (end->x < 0 || end->y < 0 || start->x >= (int)img->width
		|| start->y >= (int)img->height)
		return (0);
	if (start->x < 0)
		start->x = 0;
	if (start->y < 0)
		start->y = 0;
	if (end->x >= (int)img->width)
		end->x = (int)img->width - 1;
	if (end->y >= (int)img->height)
		end->y = (int)img->height - 1;
	return (1);
}

void	draw_rect(mlx_image_t *img, t_point start, t_point size, uint32_t color)
{
	t_point	end;
	int		xx;
	int		yy;

	end.x = start.x + size.x - 1;
	end.y = start.y + size.y - 1;
	if (!clip_rect_bounds(img, &start, &end))
		return ;
	yy = start.y - 1;
	while (++yy <= end.y)
	{
		xx = start.x - 1;
		while (++xx <= end.x)
			mlx_put_pixel(img, xx, yy, color);
	}
}

static void	update_line_error(int *err, t_point *p, t_point step, t_point delta)
{
	int	e2;

	e2 = 2 * (*err);
	if (e2 > -delta.y)
	{
		*err -= delta.y;
		p->x += step.x;
	}
	if (e2 < delta.x)
	{
		*err += delta.x;
		p->y += step.y;
	}
}

void	draw_line(mlx_image_t *img, t_point p0, t_point p1, uint32_t color)
{
	t_point	d;
	t_point	step;
	int		err;

	d.x = abs(p1.x - p0.x);
	d.y = abs(p1.y - p0.y);
	step.x = (p0.x < p1.x) * 2 - 1;
	step.y = (p0.y < p1.y) * 2 - 1;
	err = d.x - d.y;
	while (1)
	{
		if (p0.x >= 0 && p0.x < (int)img->width && p0.y >= 0
			&& p0.y < (int)img->height)
			mlx_put_pixel(img, p0.x, p0.y, color);
		if (p0.x == p1.x && p0.y == p1.y)
			break ;
		update_line_error(&err, &p0, step, d);
	}
}
