/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naessgui <naessgui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 15:20:30 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/09/10 13:54:01 by naessgui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int	arr_len(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return (0);
	while (arr[i])
		i++;
	return (i);
}

void	free2d(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	printf("%s",*arr);
	while (arr[i])
	{
		printf("%s\n",arr[i]);
		free(arr[i]);
		
		i++;
	}
	free(arr);
}

int	is_numeric_string(char *str)
{
	int	i;

	i = 0;
	if (!str || *str == '\0')
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

char	*extract_rgb_string(char *line, char *identifier)
{
	char	*start;
	char	*rgb_str;
	int		id_len;

	id_len = strlen(identifier);
	start = line + id_len;
	while (*start && (*start == ' ' || *start == '\t'))
		start++;
	if (*start == '\0')
		return (NULL);
	rgb_str = ft_strtrim(start, " \t\n\r");
	return (rgb_str);
}

int	validate_and_store_rgb(char **rgb, int *rgb_arr)
{
	int		i;
	int		value;
	char	*trimmed;

	if (!rgb || arr_len(rgb) != 3)
		return (0);
	i = 0;
	while (i < 3)
	{
		trimmed = ft_strtrim(rgb[i], " \t");
		if (!trimmed || !is_numeric_string(trimmed))
		{
			if (trimmed)
				free(trimmed);
			return (0);
		}
		value = ft_atoi(trimmed);
		free(trimmed);
		if (value < 0 || value > 255)
			return (0);
		rgb_arr[i] = value;
		i++;
	}
	return (1);
}
