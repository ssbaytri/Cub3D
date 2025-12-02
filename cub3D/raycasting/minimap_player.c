/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 08:12:12 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/10/22 08:20:10 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	render_minimap_player(t_data *data)
{
	t_point	center;
	t_point	size;
	t_point	line_end;

	center.x = MINIMAP_OFFSET_X + MINIMAP_SIZE / 2;
	center.y = MINIMAP_OFFSET_Y + MINIMAP_SIZE / 2;
	size.x = 8;
	size.y = 8;
	draw_rect(data->mlx.img, (t_point){center.x - size.x / 2, center.y - size.y
		/ 2}, size, 0xFF0000FF);
	line_end.x = center.x + (int)(cos(data->player->player_angle) * 10);
	line_end.y = center.y + (int)(sin(data->player->player_angle) * 10);
	draw_line(data->mlx.img, center, line_end, 0xFFFF00FF);
}

void	draw_minimap_frame(t_data *data)
{
	t_point		start;
	t_point		end;
	int			thick;
	uint32_t	color;

	thick = 28;
	color = 0x000000FF;
	start.x = MINIMAP_OFFSET_X;
	start.y = MINIMAP_OFFSET_Y;
	end.x = MINIMAP_OFFSET_X + MINIMAP_SIZE + thick;
	end.y = MINIMAP_OFFSET_Y + MINIMAP_SIZE + thick;
	draw_rect(data->mlx.img, start, (t_point){MINIMAP_SIZE, thick}, color);
	draw_rect(data->mlx.img, (t_point){start.x, end.y - thick},
		(t_point){MINIMAP_SIZE + thick, thick}, color);
	draw_rect(data->mlx.img, start, (t_point){thick, MINIMAP_SIZE}, color);
	draw_rect(data->mlx.img, (t_point){end.x - thick, start.y}, (t_point){thick,
		MINIMAP_SIZE}, color);
}
