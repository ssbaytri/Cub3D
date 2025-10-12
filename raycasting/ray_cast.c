/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 17:17:52 by naessgui          #+#    #+#             */
/*   Updated: 2025/10/12 18:55:35 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"


mlx_texture_t *get_wall_texture(t_data *data, int stripid)
{
    double ray_angle;

    ray_angle = data->ray[stripid].ray_angle;
    if (data->ray[stripid].was_vert_hit)
    {
        if (ray_angle > M_PI / 2 && ray_angle < 3 * M_PI / 2)
            return data->textures.west;
        else
            return data->textures.east;
    }
    else
    {
        if (ray_angle > 0 && ray_angle < M_PI)
            return data->textures.south;
        else
            return data->textures.north;
    }
}

double get_texture_offset()

uint32_t create_trgb(int *rgb)
{
    return ((rgb[0] << 24) | (rgb[1] << 16) | (rgb[2] << 8) | 0xFF);
}

void render_wall_strip(t_data *data, int stripid)
{
    double corrected_distance = data->ray[stripid].distance * cos(data->ray[stripid].ray_angle - data->player->player_angle);
    double projection_plane = (data->Mlx.win_w / 2) / tan((FOV_ANGLE * M_PI / 180) / 2);
    double wall_h = (tile_size / corrected_distance) * projection_plane;
    
    int wall_top = (data->Mlx.win_h / 2) - (wall_h / 2);
    int wall_bottom = (data->Mlx.win_h / 2) + (wall_h / 2);
    
    if (wall_top < 0) wall_top = 0;
    if (wall_bottom >= data->Mlx.win_h) wall_bottom = data->Mlx.win_h - 1;

    // draw ceiling:
    for (int y = 0; y < wall_top; y++)
        mlx_put_pixel(data->Mlx.img, stripid * WALL_STRIP_WIDTH, y, create_trgb(data->cfg.ceil_rgb));
    
    // draw wall:
    for (int y = wall_top; y < wall_bottom; y++)
        mlx_put_pixel(data->Mlx.img, stripid * WALL_STRIP_WIDTH, y, create_trgb(WALL_COLOR));

    // draw floor:
    for (int y = wall_bottom + 1; y < data->Mlx.win_h; y++)
        mlx_put_pixel(data->Mlx.img, stripid * WALL_STRIP_WIDTH, y, create_trgb(data->cfg.floor_rgb));
}

void clear_image(t_data *data)
{
    for (int y = 0; y < data->Mlx.win_h; y++)
    {
        for (int x = 0; x < data->Mlx.win_w; x++)
        {
            mlx_put_pixel(data->Mlx.img, x, y, BLACK);
        }
    }
}



void cast_single_ray(t_data *data, __unused double ray_angle , int stripid)
{
    horizontal_intersections(data, data->player , stripid);
	vertical_intersections(data , data->player , stripid);
	if (data->ray[stripid].vert_hitdistance > data->ray[stripid].horz_hitdistance)
    {
        data->ray[stripid].wall_hit_x =   data->ray[stripid].horz_wallhit_x;
        data->ray[stripid].wall_hit_y =  data->ray[stripid].horz_wallhit_y;
        data->ray[stripid].distance = data->ray[stripid].horz_hitdistance;
        data->ray[stripid].was_vert_hit = 0;
    }
    else
    {
        data->ray[stripid].wall_hit_x =  data->ray[stripid].vert_wallhit_x;
        data->ray[stripid].wall_hit_y =  data->ray[stripid].vert_wallhit_y;
        data->ray[stripid].distance = data->ray[stripid].vert_hitdistance;
                data->ray[stripid].was_vert_hit = 1;
    }
    // draw_player_line(data , data->player->pos->x , data->player->pos->y ,data->ray[stripid].wall_hit_x , data->ray[stripid].wall_hit_y);
    render_wall_strip(data, stripid);
}
void cast_rays(void *param)
{
    t_data *data = (t_data *)param;
    update(param);
    clear_image(data);
	int num_rays = data->Mlx.win_w / WALL_STRIP_WIDTH;
    data->ray = malloc(sizeof(t_ray) * num_rays);
	double ray_angle = data->player->player_angle - ((FOV_ANGLE  * M_PI /180) / 2);
	int i = 0;
	while ( i < num_rays)
	{
		init_ray(&data->ray[i]);
        data->ray[i].ray_angle = ray_angle;
		cast_single_ray(data, ray_angle , i);
		ray_angle += (FOV_ANGLE * M_PI / 180) / num_rays;
		i++;
	}
}
