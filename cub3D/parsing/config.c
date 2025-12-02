/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 19:37:19 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/09/06 20:23:40 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

static int	all_cfg_done(t_config *cfg)
{
	return (cfg->taken.got_no && cfg->taken.got_so && cfg->taken.got_we
		&& cfg->taken.got_ea && cfg->taken.got_f && cfg->taken.got_c);
}

int	save_config(t_config *cfg, char *trimmed_line)
{
	char	**tmp;

	tmp = ft_split2(trimmed_line);
	if (!tmp || arr_len(tmp) < 1)
	{
		if (tmp)
			free2d(tmp);
		return (0);
	}
	if (!strcmp(tmp[0], "NO") || !strcmp(tmp[0], "SO") || !strcmp(tmp[0], "EA")
		|| !strcmp(tmp[0], "WE"))
		return (handle_texture_config(cfg, tmp));
	if (!strcmp(tmp[0], "F") || !strcmp(tmp[0], "C"))
		return (handle_color_config(cfg, tmp, trimmed_line));
	free2d(tmp);
	return (0);
}

int	parse_config(int fd, t_config *cfg)
{
	char	*line;
	char	*trimmed_line;

	while (!all_cfg_done(cfg))
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (check_empty_line(line))
		{
			free(line);
			continue ;
		}
		trimmed_line = ft_strtrim(line, " \t\n\r");
		free(line);
		if (!save_config(cfg, trimmed_line))
		{
			free(trimmed_line);
			return (0);
		}
		free(trimmed_line);
	}
	if (!all_cfg_done(cfg))
		return (0);
	return (1);
}
