/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naessgui <naessgui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 18:19:40 by naessgui          #+#    #+#             */
/*   Updated: 2025/10/09 20:16:58 by naessgui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"
double distance(double x1, double y1, double x2, double y2)
{
    return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

 void init_ray(t_ray *ray)
 {
    ray = malloc(sizeof(t_ray));
    ray->horz_wallhit_x = 0;
    ray->vert_wallhit_x = 0;
	ray->vert_wallhit_y = 0;
	ray->horz_wallhit_y = 0;
	ray->vert_wallhit_y = 0;
    ray->found_horz_wall_hit = 0;
    ray->found_vert_wall_hit = 0;
 }

void horizontal_intersections(t_data *data , t_player *p , int i)
{
    double y_step = tile_size;
    if (sin(data->ray[i].ray_angle) > 0) {
       data->ray[i].y_horizontal = ((int)p->pos->y / tile_size) * tile_size + tile_size;
        y_step *= 1;
    }

    if (sin(data->ray[i].ray_angle) < 0) {
       data->ray[i].y_horizontal = ((int)p->pos->y / tile_size) * tile_size - 1;
        y_step *= -1;
    }

    data->ray[i].x_horizontal = p->pos->x + (data->ray[i].y_horizontal - p->pos->y) / tan(data->ray[i].ray_angle);

    double x_step = y_step / tan(data->ray[i].ray_angle);
    while (1)
    {
        if (has_wall_at(data , data->ray[i].x_horizontal , data->ray[i].y_horizontal))
        {
            data->ray[i].found_horz_wall_hit = 1;
            data->ray[i].horz_wallhit_x = data->ray[i].x_horizontal;
            data->ray[i].horz_wallhit_y = data->ray[i].y_horizontal;
            break;
        }
        else
        {
            data->ray[i].y_horizontal += y_step;
            data->ray[i].x_horizontal += x_step;
            
        }
    }
    // double horz_hitdistance;
    if (data->ray[i].found_horz_wall_hit)
        data->ray[i].horz_hitdistance = distance(p->pos->x ,p->pos->y , data->ray[i].horz_wallhit_x, data->ray[i].horz_wallhit_y);
}


void vertical_intersections(t_data *data , t_player *p , int i)
{
    double x_step = tile_size;

    if (cos(data->ray[i].ray_angle) > 0) {
        data->ray[i].x_vertical = ((int)p->pos->x / tile_size) * tile_size + tile_size;
        x_step *= 1;
    }

    if (cos(data->ray[i].ray_angle) < 0) {
        data->ray[i].x_vertical = ((int)p->pos->x / tile_size) * tile_size - 1;
        x_step *= -1;
    }

    data->ray[i].y_vertical = p->pos->y + (data->ray[i].x_vertical - p->pos->x) * tan(data->ray[i].ray_angle);

    double y_step = x_step * tan(data->ray[i].ray_angle);

    while (1)
    {
        if (has_wall_at(data , data->ray[i].x_vertical , data->ray[i].y_vertical))
        {
            data->ray[i].found_vert_wall_hit = 1;
            data->ray[i].vert_wallhit_x = data->ray[i].x_vertical;
            data->ray[i].vert_wallhit_y = data->ray[i].y_vertical;
            break;
        }
        else
        {
            data->ray[i].x_vertical += x_step;
            data->ray[i].y_vertical += y_step;
        }
    }
    if (data->ray[i].found_vert_wall_hit)
        data->ray[i].vert_hitdistance = distance(p->pos->x ,p->pos->y , data->ray[i].vert_wallhit_x, data->ray[i].vert_wallhit_y);
}
