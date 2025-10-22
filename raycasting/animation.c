/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 02:58:38 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/10/22 03:36:26 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

bool load_weapon_animation(t_data *data)
{
	char *paths[6] = {
        "./textures/weapon/0.png",
        "./textures/weapon/1.png",
        "./textures/weapon/2.png",
        "./textures/weapon/3.png",
        "./textures/weapon/4.png",
        "./textures/weapon/5.png"
    };
	int i = 0;
	    while (i < 6)
    {
        data->weapon.frames[i] = mlx_load_png(paths[i]);
        if (!data->weapon.frames[i])
        {
            printf("Error: Failed to load weapon frame %d: %s\n", i, paths[i]);
            return (false);
        }
        i++;
    }
	data->weapon.current_frame = 0;
	data->weapon.is_playing = 0;
	data->weapon.frame_delay = 3;
	data->weapon.frame_counter = 0;
	data->weapon.total_frames = 6;
	return (true);
}

void update_weapon_animation(t_data *data)
{
	if (!data->weapon.is_playing)
		return ;
	data->weapon.frame_counter++;
	if (data->weapon.frame_counter >= data->weapon.frame_delay)
	{
		data->weapon.frame_counter = 0;
		data->weapon.current_frame++;
		if (data->weapon.current_frame >= data->weapon.total_frames)
		{
			data->weapon.current_frame = 0;
			data->weapon.is_playing = 0;
		}
	}
}

void draw_weapon(t_data *data)
{
	mlx_texture_t *curr_text;
	int weapon_x;
	int weapon_y;
	double scale;

	curr_text = data->weapon.frames[data->weapon.current_frame];
	if (!curr_text)
		return ;
	scale = 0.5;
	weapon_x = (data->mlx.win_w / 2) - (curr_text->width2 * scale / 2);
	weapon_y = data->mlx.win_h - (curr_text->height2 * scale);
	for (uint32_t y = 0; y < curr_text->height2; y++)
    {
        for (uint32_t x = 0; x < curr_text->width2; x++)
        {
            int pixel_index = (y * curr_text->width2 + x) * 4;
            uint8_t r = curr_text->pixels[pixel_index];
            uint8_t g = curr_text->pixels[pixel_index + 1];
            uint8_t b = curr_text->pixels[pixel_index + 2];
            uint8_t a = curr_text->pixels[pixel_index + 3];
            
            if (a < 128)
                continue;
            
            uint32_t color = (r << 24) | (g << 16) | (b << 8) | a;

            for (int sy = 0; sy < scale; sy++)
            {
                for (int sx = 0; sx < scale; sx++)
                {
                    int screen_x = weapon_x + x * scale + sx;
                    int screen_y = weapon_y + y * scale + sy;
                    
                    if (screen_x >= 0 && screen_x < data->mlx.win_w &&
                        screen_y >= 0 && screen_y < data->mlx.win_h)
                        mlx_put_pixel(data->mlx.img, screen_x, screen_y, color);
                }
            }
        }
    }
}
