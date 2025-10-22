/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 18:23:04 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/10/22 05:45:34 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int	check_empty_line(char *line)
{
	int	i;

	if (!line)
		return (0);
	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

int	count_commas(char *str)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == ',')
			count++;
		i++;
	}
	return (count);
}

int	load_textures(t_data *data)
{
	data->textures.north = mlx_load_png(data->cfg.no_path);
	if (!data->textures.north)
	{
		printf("Error: Failed to load North texture: %s\n", data->cfg.no_path);
		return (0);
	}
	data->textures.south = mlx_load_png(data->cfg.so_path);
	if (!data->textures.south)
	{
		printf("Error: Failed to load South texture: %s\n", data->cfg.so_path);
		return (0);
	}
	data->textures.west = mlx_load_png(data->cfg.we_path);
	if (!data->textures.west)
	{
		printf("Error: Failed to load West texture: %s\n", data->cfg.we_path);
		return (0);
	}
	data->textures.east = mlx_load_png(data->cfg.ea_path);
	if (!data->textures.east)
	{
		printf("Error: Failed to load East texture: %s\n", data->cfg.ea_path);
		return (0);
	}
	return (1);
}
