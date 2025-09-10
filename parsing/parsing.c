/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 09:54:36 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/09/06 20:22:37 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int	handle_empty_line(char *line, int map_started)
{
	if (check_empty_line(line))
	{
		if (map_started)
		{
			free(line);
			return (-1);
		}
		free(line);
		return (1);
	}
	return (0);
}

int	process_map_line(char *line, t_map_list **map_lines)
{
	char		*trimmed_line;
	t_map_list	*curr;

	trimmed_line = ft_strtrim(line, "\n");
	free(line);
	if (!is_map_line_valid(trimmed_line))
	{
		free(trimmed_line);
		return (0);
	}
	curr = create_map_node(trimmed_line);
	if (!curr)
	{
		free(trimmed_line);
		return (0);
	}
	add_map_line(map_lines, curr);
	free(trimmed_line);
	return (1);
}

int	parse_map(int fd, t_map_list **map_lines)
{
	char	*line;
	int		map_started;
	int		empty_result;

	map_started = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		empty_result = handle_empty_line(line, map_started);
		if (empty_result == -1)
			return (0);
		if (empty_result == 1)
			continue ;
		if (!process_map_line(line, map_lines))
			return (0);
		map_started = 1;
	}
	return (1);
}

int	parse_file(char *file, t_game *cub)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (ft_putstr_fd("Error: Cannot open file!\n", 2), 0);
	if (!parse_config(fd, &cub->cfg))
	{
		close(fd);
		return (ft_putstr_fd("Error: Something wrong with configs!\n", 2), 0);
	}
	if (!parse_map(fd, &cub->map.list) || !validate_map(&cub->map))
	{
		close(fd);
		free_map_list(cub->map.list);
		return (ft_putstr_fd("Error: Invalid map!\n", 2), close(fd), 0);
	}
	close(fd);
	return (1);
}
