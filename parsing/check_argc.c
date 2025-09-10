/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_argc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 19:28:29 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/09/05 18:56:19 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	error_msg(char *str)
{
	ft_putstr_fd(str, 2);
	exit(1);
}

void	check_args(int ac, char *str)
{
	int		fd;
	char	buf[1];
	int		ret;

	if (ac != 2)
		error_msg("Usage: ./cub3d <map.cub>\n");
	if (ft_strncmp(str + ft_strlen(str) - 4, ".cub", 4))
		error_msg("Error: Invalid file extension\n");
	fd = open(str, O_RDONLY);
	if (fd == -1)
		error_msg("Error: No file exists\n");
	ret = read(fd, buf, 1);
	if (ret <= 0)
		error_msg("Error: Empty file\n");
	close(fd);
}
