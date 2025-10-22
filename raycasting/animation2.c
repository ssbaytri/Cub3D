/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 05:45:50 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/10/22 06:11:38 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

static void	init_weapon_paths(char *paths[6])
{
	paths[0] = "./textures/weapon/0.png";
	paths[1] = "./textures/weapon/1.png";
	paths[2] = "./textures/weapon/2.png";
	paths[3] = "./textures/weapon/3.png";
	paths[4] = "./textures/weapon/4.png";
	paths[5] = "./textures/weapon/5.png";
}

bool	load_weapon_animation(t_data *data)
{
	int		i;
	char	*paths[6];

	init_weapon_paths(paths);
	i = 0;
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
	data->weapon.frame_delay = 4;
	data->weapon.frame_counter = 0;
	data->weapon.total_frames = 6;
	return (true);
}

void	update_weapon_animation(t_data *data)
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
