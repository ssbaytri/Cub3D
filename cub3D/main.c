/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 20:26:03 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/09/06 20:26:56 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	ss(void)
{
	system("leaks cub3D");
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
	free2d(cub.map.grid);
	free_cfg(&cub.cfg);
	return (0);
}
