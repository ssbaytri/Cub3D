/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 22:45:07 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/10/23 04:20:51 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	free_cfg(t_config *cfg)
{
	free(cfg->no_path);
	free(cfg->so_path);
	free(cfg->we_path);
	free(cfg->ea_path);
}

void	clean_textures(t_data *data)
{
	int	i;

	i = 0;
	if (data->textures.north)
		mlx_delete_texture(data->textures.north);
	if (data->textures.south)
		mlx_delete_texture(data->textures.south);
	if (data->textures.east)
		mlx_delete_texture(data->textures.east);
	if (data->textures.west)
		mlx_delete_texture(data->textures.west);
	if (data->textures.door)
		mlx_delete_texture(data->textures.door);
	while (i < 6)
	{
		if (data->weapon.frames[i])
			mlx_delete_texture(data->weapon.frames[i]);
		i++;
	}
}

int	cleanup_error(t_data *data)
{
	free_cfg(&data->cfg);
	free2d(data->map.grid);
	clean_textures(data);
	free(data);
	return (1);
}

void	cleanup_success(t_data *data)
{
	free2d(data->map.grid);
	free_cfg(&data->cfg);
	if (data->player && data->player->pos)
		free(data->player->pos);
	if (data->player)
		free(data->player);
	clean_textures(data);
	free(data);
}
