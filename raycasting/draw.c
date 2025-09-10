/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naessgui <naessgui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 12:49:21 by naessgui          #+#    #+#             */
/*   Updated: 2025/09/09 11:08:42 by naessgui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void draw_rectangle(mlx_image_t *img, int j , int i , int color)
{
    int x = j * tile_size;
    int y = i * tile_size;
	int ny = y;
	while(ny < y + tile_size)
	{
		int nx = x;
		while ( nx < x + tile_size)
		{
			if (nx >= 0 && ny >= 0 && nx < (int)img->width && ny < (int)img->height)
            {
                if (ny == y || ny == y + tile_size - 1 ||
                    nx == x || nx == x + tile_size - 1)
                    mlx_put_pixel(img, nx, ny, BLACK);
                else
                    mlx_put_pixel(img, nx, ny, color);
            }
			nx++;
			
		}
		ny++;
	}
}