/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naessgui <naessgui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 12:49:21 by naessgui          #+#    #+#             */
/*   Updated: 2025/09/22 15:12:42 by naessgui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"
void	draw_rectangle(mlx_image_t *img, int j, int i, int color)
{
	int	x;
	int	y;
	int	ny;
	int	nx;

	x = j * tile_size;
	y = i * tile_size;
	ny = y;
	while (ny < y + tile_size)
	{
		nx = x;
		while (nx < x + tile_size)
		{
			if (nx >= 0 && ny >= 0 && nx < (int)img->width 
			&& ny < (int)img->height)
			{
				if (ny == y || ny == y + tile_size - 1 || nx == x || nx == x
					+ tile_size - 1)
					mlx_put_pixel(img, nx, ny, BLACK);
				else
					mlx_put_pixel(img, nx, ny, color);
			}
			nx++;
		}
		ny++;
	}
}
