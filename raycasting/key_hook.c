/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 12:15:59 by naessgui          #+#    #+#             */
/*   Updated: 2025/10/16 21:09:47 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

static void	handle_key_press(mlx_key_data_t keydata, t_player *player,
		t_data *data)
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
	else if (keydata.key == MLX_KEY_ESCAPE)
	{
		mlx_close_window(data->mlx.mlx);
		mlx_terminate(data->mlx.mlx);
		exit(0);
	}
}

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_data		*data;
	t_player	*player;

	data = (t_data *)param;
	player = data->player;
	if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
		handle_key_press(keydata, player, data);
	else if (keydata.action == MLX_RELEASE)
		reset_var(keydata, data);
}

void	reset_var(mlx_key_data_t keydata, t_data *data)
{
	t_player	*player;

	player = data->player;
	if (keydata.key == MLX_KEY_W || keydata.key == MLX_KEY_S)
		player->walk_dir = 0;
	if (keydata.key == MLX_KEY_A || keydata.key == MLX_KEY_D)
		player->turn_dir = 0;
	if (keydata.key == MLX_KEY_RIGHT || keydata.key == MLX_KEY_LEFT)
		player->rot_direction = 0;
}

void	update(void *param)
{
	t_data	*data;
	double	new_x;
	double	new_y;

	data = (t_data *)param;
	new_x = 0;
	new_y = 0;
	data->player->player_angle += data->player->rot_direction
		* data->player->rot_speed;
	data->player->player_angle = fmod(data->player->player_angle, 2 * M_PI);
	new_x += cos(data->player->player_angle) * data->player->walk_dir
		* data->player->move_speed;
	new_y += sin(data->player->player_angle) * data->player->walk_dir
		* data->player->move_speed;
	new_x += cos(data->player->player_angle + M_PI / 2) * data->player->turn_dir
		* data->player->move_speed;
	new_y += sin(data->player->player_angle + M_PI / 2) * data->player->turn_dir
		* data->player->move_speed;
	if (has_wall_at(data, data->player->pos->x + new_x, data->player->pos->y
			+ new_y))
		return ;
	wall_collision(data, new_x, new_y);
}
