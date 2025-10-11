/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 20:26:03 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/10/11 21:53:25 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void    debug_game(t_game *game)
{
    int i;

    printf("========== CONFIG ==========\n");
    printf("NO: %s\n", game->cfg.no_path);
    printf("SO: %s\n", game->cfg.so_path);
    printf("WE: %s\n", game->cfg.we_path);
    printf("EA: %s\n", game->cfg.ea_path);

    printf("F: [%d, %d, %d]\n",
        game->cfg.floor_rgb[0],
        game->cfg.floor_rgb[1],
        game->cfg.floor_rgb[2]);

    printf("C: [%d, %d, %d]\n",
        game->cfg.ceil_rgb[0],
        game->cfg.ceil_rgb[1],
        game->cfg.ceil_rgb[2]);

    printf("========== MAP ==========\n");
    printf("Map size: %d x %d\n", game->map.height, game->map.width);
    printf("Player at: (%f, %f) facing %c\n",
        game->map.player_pos.x,
        game->map.player_pos.y,
        game->map.player_dir);

    for (i = 0; i < game->map.height; i++)
        printf("[%s]\n", game->map.grid[i]);

    printf("===========================\n");
}

void	free_cfg(t_config *cfg)
{
	free(cfg->no_path);
	free(cfg->so_path);
	free(cfg->we_path);
	free(cfg->ea_path);
}
// void	ss(void)
// {
// 	system("leaks cub3D");
// }
int	main(int argc, char **argv)
{
	t_game	cub;
    t_data *data;
	// atexit(ss);
     
	ft_memset(&cub, 0, sizeof(t_game));
	check_args(argc, argv[1]);
	if (!parse_file(argv[1], &cub))
	{
		free_cfg(&cub.cfg);
		free2d(cub.map.grid);
		return (1);
	}
	printf("Valida Map\n");
	debug_game(&cub);
    data = malloc(sizeof(t_data));
	data->map = cub.map;
	data->cfg  = cub.cfg;
    
	window_size(data);
    data->Mlx.mlx = mlx_init(data->Mlx.win_w, data->Mlx.win_h, "My MLX42 Window", false);
    
    if (!data->Mlx.mlx)
        return (EXIT_FAILURE);
    data->Mlx.img = mlx_new_image(data->Mlx.mlx, data->Mlx.win_w, data->Mlx.win_h);
	
	mlx_image_to_window(data->Mlx.mlx, data->Mlx.img, 0, 0);
	// draw_map(data);
	init_player(data);
	// draw_player(data->Mlx.img, data);
    // draw_player_line(data);
	mlx_key_hook(data->Mlx.mlx , &key_hook ,data);
	// mlx_loop_hook(data->Mlx.mlx, update, data);
    mlx_loop_hook(data->Mlx.mlx, cast_rays, data);
    // cast_rays(data);
    mlx_loop(data->Mlx.mlx); 
	free2d(cub.map.grid);
	free_cfg(&cub.cfg);
	return (0);
}
