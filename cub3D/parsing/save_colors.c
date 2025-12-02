/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_colors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 18:31:09 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/09/05 18:50:15 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

static int	handle_floor_color(t_config *cfg, char **tmp, char **rgb)
{
	int	result;

	if (cfg->taken.got_f)
	{
		free2d(tmp);
		free2d(rgb);
		return (0);
	}
	result = validate_and_store_rgb(rgb, cfg->floor_rgb);
	if (result)
		cfg->taken.got_f = 1;
	return (result);
}

static int	handle_ceil_color(t_config *cfg, char **tmp, char **rgb)
{
	int	result;

	if (cfg->taken.got_c)
	{
		free2d(tmp);
		free2d(rgb);
		return (0);
	}
	result = validate_and_store_rgb(rgb, cfg->ceil_rgb);
	if (result)
		cfg->taken.got_c = 1;
	return (result);
}

int	handle_color_config(t_config *cfg, char **tmp, char *trimmed_line)
{
	char	*rgb_string;
	char	**rgb;
	int		result;

	rgb_string = extract_rgb_string(trimmed_line, tmp[0]);
	if (!rgb_string)
		return (free2d(tmp), 0);
	if (count_commas(rgb_string) != 2)
	{
		free2d(tmp);
		free(rgb_string);
		return (0);
	}
	rgb = ft_split(rgb_string, ',');
	free(rgb_string);
	if (!rgb)
		return (0);
	if (!strcmp(tmp[0], "F"))
		result = handle_floor_color(cfg, tmp, rgb);
	else
		result = handle_ceil_color(cfg, tmp, rgb);
	free2d(rgb);
	free2d(tmp);
	return (result);
}
