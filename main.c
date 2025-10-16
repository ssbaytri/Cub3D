/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 20:26:03 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/10/16 18:51:27 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void    debug_game(t_data *data)
{
    int i;

    printf("========== CONFIG ==========\n");
    printf("NO: %s\n", data->cfg.no_path);
    printf("SO: %s\n", data->cfg.so_path);
    printf("WE: %s\n", data->cfg.we_path);
    printf("EA: %s\n", data->cfg.ea_path);

    printf("F: [%d, %d, %d]\n",
        data->cfg.floor_rgb[0],
        data->cfg.floor_rgb[1],
        data->cfg.floor_rgb[2]);

    printf("C: [%d, %d, %d]\n",
        data->cfg.ceil_rgb[0],
        data->cfg.ceil_rgb[1],
        data->cfg.ceil_rgb[2]);

    printf("========== MAP ==========\n");
    printf("Map size: %d x %d\n", data->map.height, data->map.width);
    printf("Player at: (%f, %f) facing %c\n",
        data->map.player_pos.x,
        data->map.player_pos.y,
        data->map.player_dir);

    for (i = 0; i < data->map.height; i++)
        printf("[%s]\n", data->map.grid[i]);

    printf("===========================\n");
}

void	free_cfg(t_config *cfg)
{
	free(cfg->no_path);
	free(cfg->so_path);
	free(cfg->we_path);
	free(cfg->ea_path);
}

void clean_textures(t_data *data)
{
    if (data->textures.north)
        mlx_delete_texture(data->textures.north);
    if (data->textures.south)
        mlx_delete_texture(data->textures.south);
    if (data->textures.east)
        mlx_delete_texture(data->textures.east);
    if (data->textures.west)
        mlx_delete_texture(data->textures.west);
}


void	ss(void)
{
	system("leaks cub3D");
}

int	main(int argc, char **argv)
{
    t_data *data;
    
	atexit(ss);
    data = ft_calloc(1, sizeof(t_data));
	check_args(argc, argv[1]);
	if (!parse_file(argv[1], data) || !load_textures(data))
	{
		free_cfg(&data->cfg);
		free2d(data->map.grid);
        free(data);
        clean_textures(data);
		return (1);
	}
    printf("Valid map and textures\n");
	window_size(data);
    data->Mlx.mlx = mlx_init(data->Mlx.win_w, data->Mlx.win_h, "Cub3D", false);
    if (!data->Mlx.mlx)
        return (EXIT_FAILURE);
    data->Mlx.img = mlx_new_image(data->Mlx.mlx, data->Mlx.win_w, data->Mlx.win_h);
	mlx_image_to_window(data->Mlx.mlx, data->Mlx.img, 0, 0);
	init_player(data);
	mlx_key_hook(data->Mlx.mlx , &key_hook ,data);
    mlx_loop_hook(data->Mlx.mlx, cast_rays, data);
    mlx_loop(data->Mlx.mlx);
	free2d(data->map.grid);
	free_cfg(&data->cfg);
    free(data);
    free(data->player);
    free(data->player->pos);
    clean_textures(data);
	return (0);
}
