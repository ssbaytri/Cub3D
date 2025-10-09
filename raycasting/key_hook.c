/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naessgui <naessgui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 12:15:59 by naessgui          #+#    #+#             */
/*   Updated: 2025/10/09 20:00:48 by naessgui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void key_hook(mlx_key_data_t keydata, void *param)
{
	t_data *data = (t_data *)param;
	t_player *player = data->player;
    
	if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
	{
		if (keydata.key == MLX_KEY_W)
			player->walk_dir = 1;
		else if (keydata.key == MLX_KEY_S)
			player->walk_dir = -1;
		else if (keydata.key == MLX_KEY_A)
			player->turn_dir = -1;
		else if (keydata.key == MLX_KEY_D)
			player->turn_dir = 1;
		else if (keydata.key == MLX_KEY_LEFT)
			player->rot_direction = -1;
		else if (keydata.key == MLX_KEY_RIGHT)
			player->rot_direction = 1;
		else if( keydata.key == MLX_KEY_ESCAPE)
			exit(0);
	}
	else if (keydata.action == MLX_RELEASE)
        reset_var(keydata , data);
	
}
void reset_var(mlx_key_data_t keydata , t_data *data)
{
    t_player *player = data->player;
    if (keydata.key == MLX_KEY_W || keydata.key == MLX_KEY_S)
		player->walk_dir = 0;
	else if (keydata.key == MLX_KEY_A || keydata.key == MLX_KEY_D)
		player->turn_dir = 0;
	else if (keydata.key == MLX_KEY_RIGHT || keydata.key == MLX_KEY_LEFT)
		player->rot_direction = 0;
}

int has_wall_at(t_data *data, float x, float y)
{
    int map_x = (int)(x / tile_size);
    int map_y = (int)(y / tile_size);

    if (map_x < 0 || map_x >= data->map.width ||
        map_y < 0 || map_y >= data->map.height) 
        return 1;
	
    if (data->map.grid[map_y][map_x] == '1')
        return 1;
    return 0;
}

void wall_collision(t_data *data ,  double  new_x ,double new_y)
{
	
	if (!has_wall_at(data , data->player->pos->x  + new_x  , data->player->pos->y))
		data->player->pos->x += new_x;	
	if (!has_wall_at(data ,data->player->pos->x , data->player->pos->y +  new_y))
		data->player->pos->y +=  new_y;	
	return ;
}
void update(void *param)
{
    t_data *data = (t_data *)param;
	double	new_x;
	double	new_y;
	
	
	new_x = 0;
	new_y = 0;
    data->player->player_angle += data->player->rot_direction * data->player->rot_speed;
	data->player->player_angle= fmod(data->player->player_angle, 2 * M_PI);

    new_x += cos(data->player->player_angle) * data->player->walk_dir * data->player->move_speed;
    new_y += sin(data->player->player_angle) * data->player->walk_dir * data->player->move_speed;
    new_x += cos(data->player->player_angle + M_PI / 2) * data->player->turn_dir * data->player->move_speed;
    new_y += sin(data->player->player_angle + M_PI / 2) * data->player->turn_dir * data->player->move_speed;	
	if (has_wall_at(data ,data->player->pos->x + new_x, data->player->pos->y + new_y ))
		return;
	wall_collision(data ,new_x ,new_y);
	draw_map(data);
    draw_player(data->Mlx.img, data);
}
