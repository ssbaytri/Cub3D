/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 17:17:52 by naessgui          #+#    #+#             */
/*   Updated: 2025/10/18 02:19:46 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

static void	clear_image(t_data *data)
{
	int	y;
	int	x;

	y = 0;
	while (y < data->mlx.win_h)
	{
		x = 0;
		while (x < data->mlx.win_w)
		{
			mlx_put_pixel(data->mlx.img, x, y, BLACK);
			x++;
		}
		y++;
	}
}

static void	init_ray(t_ray *ray)
{
	ray->horz_wallhit_x = 0;
	ray->vert_wallhit_x = 0;
	ray->vert_wallhit_y = 0;
	ray->horz_wallhit_y = 0;
	ray->found_horz_wall_hit = 0;
	ray->found_vert_wall_hit = 0;
}

void	cast_single_ray(t_data *data, int stripid)
{
	horizontal_intersections(data, data->player, stripid);
	vertical_intersections(data, data->player, stripid);
	if (data->ray[stripid].vert_hitdistance
		> data->ray[stripid].horz_hitdistance)
	{
		data->ray[stripid].wall_hit_x = data->ray[stripid].horz_wallhit_x;
		data->ray[stripid].wall_hit_y = data->ray[stripid].horz_wallhit_y;
		data->ray[stripid].distance = data->ray[stripid].horz_hitdistance;
		data->ray[stripid].was_vert_hit = 0;
	}
	else
	{
		data->ray[stripid].wall_hit_x = data->ray[stripid].vert_wallhit_x;
		data->ray[stripid].wall_hit_y = data->ray[stripid].vert_wallhit_y;
		data->ray[stripid].distance = data->ray[stripid].vert_hitdistance;
		data->ray[stripid].was_vert_hit = 1;
	}
	render_wall_strip(data, stripid);
}

double	normalize_angle(double angle)
{
	angle = fmod(angle, 2 * M_PI);
	if (angle < 0)
		angle += 2 * M_PI;
	return (angle);
}

void	cast_rays(void *param)
{
	t_data	*data;
	int		num_rays;
	int		i;
	double	ray_angle;

	data = (t_data *)param;
	mouse_move(param);
	update(param);
	clear_image(data);
	num_rays = data->mlx.win_w / WALL_STRIP_WIDTH;
	data->ray = ft_calloc(num_rays, sizeof(t_ray));
	ray_angle = data->player->player_angle - ((FOV_ANGLE * M_PI / 180) / 2);
	i = 0;
	while (i < num_rays)
	{
		init_ray(&data->ray[i]);
		data->ray[i].ray_angle = normalize_angle(ray_angle);
		cast_single_ray(data, i);
		ray_angle += (FOV_ANGLE * M_PI / 180) / num_rays;
		i++;
	}
	render_minimap(data);
	draw_minimap_frame(data);
	free(data->ray);
}
