/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_argc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 19:28:29 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/09/04 20:48:17 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void error_msg(char *str)
{
	ft_putstr_fd(str, 2);
	exit(1);
}

void check_args(int ac, char *str)
{
	char *line;

	if (ac != 2)
		error_msg("Usage: ./cub3d <map.cub>\n");
	if (ft_strncmp(str + ft_strlen(str) - 4, ".cub", 4))
		error_msg("Error: Invalid file extensions\n");
	if (open(str, O_RDONLY) == -1)
		error_msg("Error: No file exists\n");
	line = get_next_line(open(str, O_RDONLY));
	if (!line)
	{
		error_msg("Error: Empty file");
		return ;
	}
	free(line);
}
