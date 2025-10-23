/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 20:26:03 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/10/23 05:20:21 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	mouse_move(void *param)
{
	t_data	*data;
	int32_t	xpos;
	int32_t	ypos;
	int		center_x;

	data = (t_data *)param;
	center_x = data->mlx.win_w / 2;
	mlx_get_mouse_pos(data->mlx.mlx, &xpos, &ypos);
	data->player->player_angle += (xpos - center_x) * SENSITIVITY;
	mlx_set_mouse_pos(data->mlx.mlx, data->mlx.win_w / 2, data->mlx.win_h / 2);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	data = ft_calloc(1, sizeof(t_data));
	check_args(argc, argv[1]);
	if (!parse_file(argv[1], data) || !load_textures(data)
		|| !load_weapon_animation(data) || !load_door_texture(data))
		return (cleanup_error(data));
	find_all_doors(data);
	window_size(data);
	data->mlx.mlx = mlx_init(data->mlx.win_w, data->mlx.win_h, "Cub3D", false);
	if (!data->mlx.mlx)
		return (EXIT_FAILURE);
	data->mlx.img = mlx_new_image(data->mlx.mlx, data->mlx.win_w,
			data->mlx.win_h);
	mlx_image_to_window(data->mlx.mlx, data->mlx.img, 0, 0);
	init_player(data);
	mlx_set_cursor_mode(data->mlx.mlx, MLX_MOUSE_DISABLED);
	mlx_key_hook(data->mlx.mlx, &key_hook, data);
	mlx_mouse_hook(data->mlx.mlx, &mouse_click_hook, data);
	mlx_loop_hook(data->mlx.mlx, cast_rays, data);
	mlx_loop(data->mlx.mlx);
	cleanup_success(data);
	return (0);
}
