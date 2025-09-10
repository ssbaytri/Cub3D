/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 18:24:28 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/09/05 18:25:58 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

static int	handle_no_texture(t_config *cfg, char **tmp)
{
	if (cfg->taken.got_no)
	{
		free2d(tmp);
		return (0);
	}
	cfg->no_path = ft_strdup(tmp[1]);
	cfg->taken.got_no = 1;
	free2d(tmp);
	return (1);
}

static int	handle_so_texture(t_config *cfg, char **tmp)
{
	if (cfg->taken.got_so)
	{
		free2d(tmp);
		return (0);
	}
	cfg->so_path = ft_strdup(tmp[1]);
	cfg->taken.got_so = 1;
	free2d(tmp);
	return (1);
}

static int	handle_we_texture(t_config *cfg, char **tmp)
{
	if (cfg->taken.got_we)
	{
		free2d(tmp);
		return (0);
	}
	cfg->we_path = ft_strdup(tmp[1]);
	cfg->taken.got_we = 1;
	free2d(tmp);
	return (1);
}

static int	handle_ea_texture(t_config *cfg, char **tmp)
{
	if (cfg->taken.got_ea)
	{
		free2d(tmp);
		return (0);
	}
	cfg->ea_path = ft_strdup(tmp[1]);
	cfg->taken.got_ea = 1;
	free2d(tmp);
	return (1);
}

int	handle_texture_config(t_config *cfg, char **tmp)
{
	if (arr_len(tmp) != 2)
	{
		free2d(tmp);
		return (0);
	}
	if (!strcmp(tmp[0], "NO"))
		return (handle_no_texture(cfg, tmp));
	else if (!strcmp(tmp[0], "SO"))
		return (handle_so_texture(cfg, tmp));
	else if (!strcmp(tmp[0], "WE"))
		return (handle_we_texture(cfg, tmp));
	else if (!strcmp(tmp[0], "EA"))
		return (handle_ea_texture(cfg, tmp));
	return (0);
}
