/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 22:54:55 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/10/17 23:20:52 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void draw_rect(mlx_image_t *img, int x, int y, int width, int height, uint32_t color)
{
	int row;
	int col;
	uint32_t px;
	uint32_t py;

	row = 0;
	while (row < height)
	{
		col = 0;
		while (col < width)
		{
			px = x + col;
			py = y + row;
			if (px >= 0 && px < img->width && py >= 0 && py < img->height)
				mlx_put_pixel(img, px, py, color);
			col++;
		}
		row++;
	}
}

void render_minimap(t_data *data)
{
	int row, col;
	char **grid = data->map.grid;
	
	for (row = 0; row < data->map.height; row++)
	{
		for (col = 0; col < data->map.width; col++)
		{
			uint32_t color = BLACK;
			if (grid[row][col] == '1')
				color = GRAY;
			else if (grid[row][col] == '0' || ft_strchr("NSEW", grid[row][col]))
				color = LIGHT_GRAY;
			int x = col * MINIMAP_TILESIZE;
			int y = row * MINIMAP_TILESIZE;
			draw_rect(data->mlx.img, x, y, MINIMAP_TILESIZE, MINIMAP_TILESIZE, color);
		}
	}
}

void    render_minimap_player(t_data *data)
{
    int px = data->player->pos->x * MINIMAP_SCALE;
    int py = data->player->pos->y * MINIMAP_SCALE;

    for (int dy = -MINIMAP_PLAYER_RADIUS; dy <= MINIMAP_PLAYER_RADIUS; dy++)
    {
        for (int dx = -MINIMAP_PLAYER_RADIUS; dx <= MINIMAP_PLAYER_RADIUS; dx++)
        {
            if (dx * dx + dy * dy <= MINIMAP_PLAYER_RADIUS * MINIMAP_PLAYER_RADIUS)
                mlx_put_pixel(data->mlx.img, px + dx, py + dy, RED);
        }
    }
}
