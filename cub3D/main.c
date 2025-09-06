/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 20:26:03 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/09/06 20:45:12 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	ss(void)
{
	system("leaks cub3D");
}

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
    printf("Player at: (%d, %d) facing %c\n",
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

int	main(int argc, char **argv)
{
	t_game	cub;

	atexit(ss);
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
	free2d(cub.map.grid);
	free_cfg(&cub.cfg);
	return (0);
}
