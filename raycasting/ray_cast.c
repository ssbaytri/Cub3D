/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naessgui <naessgui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 17:17:52 by naessgui          #+#    #+#             */
/*   Updated: 2025/10/09 20:16:18 by naessgui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void cast_single_ray(t_data *data, __unused double ray_angle , int stripid)
{
    horizontal_intersections(data, data->player , stripid);
	vertical_intersections(data , data->player , stripid);
	if (data->ray[stripid].vert_hitdistance > data->ray[stripid].horz_hitdistance )
    {
        data->ray[stripid].wall_hit_x =   data->ray[stripid].horz_wallhit_x;
        data->ray[stripid].wall_hit_y =  data->ray[stripid].horz_wallhit_y; 
    }
    else
    {
        data->ray[stripid].wall_hit_x =  data->ray[stripid].vert_wallhit_x;
        data->ray[stripid].wall_hit_y =  data->ray[stripid].vert_wallhit_y;
    }
    draw_player_line(data , data->player->pos->x , data->player->pos->y ,data->ray[stripid].wall_hit_x , data->ray[stripid].wall_hit_y);
}
void cast_rays(void *param)
{
    t_data *data = (t_data *)param ;
    update(param);
    
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
