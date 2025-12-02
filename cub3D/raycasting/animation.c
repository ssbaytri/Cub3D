/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 02:58:38 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/10/22 06:10:33 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

static uint32_t	get_pixel_color(uint8_t *pixels, int index)
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
	uint8_t	a;

	r = pixels[index];
	g = pixels[index + 1];
	b = pixels[index + 2];
	a = pixels[index + 3];
	return ((r << 24) | (g << 16) | (b << 8) | a);
}

static void	draw_weapon_pixel(t_data *data, mlx_texture_t *text,
		t_weapon_draw *info, t_pixel_coord *screen)
{
	t_pixel_coord	tex;
	int				pixel_index;
	uint32_t		color;
	int				final_x;
	int				final_y;

	tex.x = (int)(screen->x / info->scale);
	tex.y = (int)(screen->y / info->scale);
	pixel_index = (tex.y * text->width2 + tex.x) * 4;
	if (text->pixels[pixel_index + 3] < 128)
		return ;
	color = get_pixel_color(text->pixels, pixel_index);
	final_x = info->weapon_x + screen->x;
	final_y = info->weapon_y + screen->y;
	if (final_x >= 0 && final_x < data->mlx.win_w && final_y >= 0
		&& final_y < data->mlx.win_h)
		mlx_put_pixel(data->mlx.img, final_x, final_y, color);
}

static void	draw_weapon_pixels(t_data *data, mlx_texture_t *text,
		t_weapon_draw *info)
{
	t_pixel_coord	screen;

	screen.y = 0;
	while (screen.y < info->final_height)
	{
		screen.x = 0;
		while (screen.x < info->final_width)
		{
			draw_weapon_pixel(data, text, info, &screen);
			screen.x++;
		}
		screen.y++;
	}
}

void	draw_weapon(t_data *data)
{
	mlx_texture_t	*curr_text;
	t_weapon_draw	info;

	curr_text = data->weapon.frames[data->weapon.current_frame];
	if (!curr_text)
		return ;
	info.scale = 0.5;
	info.final_width = (int)(curr_text->width2 * info.scale);
	info.final_height = (int)(curr_text->height2 * info.scale);
	info.weapon_x = (data->mlx.win_w / 2) - (info.final_width / 2);
	info.weapon_y = data->mlx.win_h - info.final_height;
	draw_weapon_pixels(data, curr_text, &info);
}
