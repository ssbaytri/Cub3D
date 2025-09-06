/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 09:54:36 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/09/06 15:37:31 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int	all_cfg_done(t_config *cfg)
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

void	debug(t_config *cfg)
{
	printf("NO: %s\n", cfg->no_path);
	printf("SO: %s\n", cfg->so_path);
	printf("WE: %s\n", cfg->we_path);
	printf("EA: %s\n", cfg->ea_path);
	printf("F: [%d, %d, %d]\n", cfg->floor_rgb[0], cfg->floor_rgb[1],
		cfg->floor_rgb[2]);
	printf("C: [%d, %d, %d]\n", cfg->ceil_rgb[0], cfg->ceil_rgb[1],
		cfg->ceil_rgb[2]);
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

int	parse_map(int fd, t_map_list **map_lines)
{
	char		*line;
	char		*trimmed_line;
	int			map_started;
	t_map_list	*curr;

	map_started = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (check_empty_line(line))
		{
			if (map_started)
				return (free(line), 0);
			free(line);
			continue ;
		}
		trimmed_line = ft_strtrim(line, "'\n");
		free(line);
		if (!is_map_line_valid(trimmed_line))
			return (free(trimmed_line), 0);
		curr = create_map_node(trimmed_line);
		if (!curr)
			return (free(trimmed_line), free_map_list(curr), 0);
		add_map_line(map_lines, curr);
		map_started = 1;
		free(trimmed_line);
	}
	return (1);
}

int	parse_file(char *file, t_config *cfg)
{
	int		fd;
	t_map	map;

	ft_memset(cfg, 0, sizeof(t_config));
	ft_memset(&map, 0, sizeof(t_map));
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (ft_putstr_fd("Error: Cannot open file!\n", 2), 0);
	if (!parse_config(fd, cfg))
	{
		close(fd);
		return (ft_putstr_fd("Error: Something wrong with configs!\n", 2), 0);
	}
	debug(cfg);
	if (!parse_map(fd, &map.list) || !validate_map(&map))
	{
		close(fd);
		free_map_list(map.list);
		return (ft_putstr_fd("Error: Invalid map!\n", 2), close(fd), 0);
	}
	close(fd);
	return (1);
}
