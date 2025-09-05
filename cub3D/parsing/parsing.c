/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 09:54:36 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/09/05 13:03:40 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int ft_ischar(int c)
{
	return (c == ' ' || c == '\n' || c == '\0' || c == '\t');
}

int word_count(char *str)
{
	int count = 0;
	int i = 0;
	while (str[i])
	{
		while (str[i] &&ft_ischar(str[i]))
			i++;
		if (!ft_ischar(str[i]))
			count++;
		while (!ft_ischar(str[i]))
			i++;
	}
	return count;
}


int ft_strlen2(char *str)
{
	int i = 0;
	while (str[i] && !ft_ischar(str[i]))
		i++;
	return i;
}

char *ft_word(char *str)
{
	char *word;
	int word_len;
	int i;

	i = 0;
	word_len = ft_strlen2(str);
	word = malloc(word_len + 1);
	if (!word)
		return NULL;
	while (i < word_len)
	{
		word[i] = str[i];
		i++;
	}
	word[i] = 0;
	return word;
}


char    **ft_split2(char *str)
{
	char **result;
	int i;

	i = 0;
	result = malloc(sizeof(char *) * word_count(str) + 1);
	if (!result)
		return NULL;
	while (*str)
	{
		while (*str && ft_ischar(*str))
			str++;
		if (*str)
		{
			result[i] = ft_word(str);
			i++;
		}
		while (*str && !ft_ischar(*str))
			str++;
	}
	result[i] = NULL;
	return result;
}

int	check_empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

int arr_len(char **arr)
{
	int i = 0;
	
	if (!arr)
		return (0);
	while(arr[i])
		i++;
	return (i);
}

int is_numeric_string(char *str)
{
    int i = 0;
    while (str[i])
    {
        if (str[i] < '0' || str[i] > '9')
            return 0;
        i++;
    }
    return 1;
}

int validate_and_store_rgb(char **rgb, int *rgb_arr)
{
	int i;
	int value;
	
	i = 0;
	while (rgb[i])
	{
		if (is_numeric_string(rgb[i]))
		{
			value = ft_atoi(rgb[i]);
			if (value < 0 || value > 255)
				return 0;
			rgb_arr[i] = value;
			i++;
		}
		else
			return (0);
	}
	return 1;
}

void free2d(char **arr)
{
	int i;
	
	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

int save_config(t_config *cfg, char **tmp)
{
	if (!strcmp(tmp[0], "NO") || !strcmp(tmp[0], "SO")
		||! strcmp(tmp[0], "EA") ||!strcmp(tmp[0], "WE"))
	{
		if (arr_len(tmp) == 2)
		{
			if (!strcmp(tmp[0], "NO"))
			{
				cfg->no_path = ft_strdup(tmp[1]);
				cfg->taken.got_no = 1;
			}
			else if(!strcmp(tmp[0], "SO"))
			{
				cfg->so_path = ft_strdup(tmp[1]);
				cfg->taken.got_so = 1;
			}
			else if(!strcmp(tmp[0], "WE"))
			{
				cfg->we_path = ft_strdup(tmp[1]);
				cfg->taken.got_we = 1;
			}
			else if(!strcmp(tmp[0], "EA"))
			{
				cfg->ea_path = ft_strdup(tmp[1]);
				cfg->taken.got_ea = 1;
			}
			return (1);
		}
		return (0);
	}
	if (!strcmp(tmp[0], "F") || !strcmp(tmp[0], "C"))
	{
		if (arr_len(tmp) == 2)
		{
			if (!strcmp(tmp[0], "F"))
			{
				char **rgb = ft_split(tmp[1], ',');
				if (arr_len(rgb) == 3 && validate_and_store_rgb(rgb, cfg->floor_rgb))
				{
					cfg->taken.got_f = 1;
					free2d(rgb);
					return (1);
				}
				return (0);
			}
			else if(!strcmp(tmp[0], "C"))
			{
				char **rgb = ft_split(tmp[1], ',');
				if (arr_len(rgb) == 3 && validate_and_store_rgb(rgb, cfg->ceil_rgb))
				{
					cfg->taken.got_c = 1;
					free2d(rgb);
					return (1);
				}
				return (0);
			}
		}
		return (0);
	}
	return (0);
}

void	parse_config(char *file, t_config *cfg)
{
	int fd;
	char *line;
	char **tmp;

	ft_memset(cfg, 0, sizeof(t_config));
	fd = open(file, O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (check_empty_line(line))
		{
			free(line);
			continue ;
		}
		tmp = ft_split2(line);
		save_config(cfg, tmp);
		free2d(tmp);
	}
	printf("%s\n", cfg->no_path);
	printf("%s\n", cfg->so_path);
	printf("%s\n", cfg->we_path);
	printf("%s\n", cfg->ea_path);
	printf("[%d, %d, %d]\n", cfg->floor_rgb[0], cfg->floor_rgb[1], cfg->floor_rgb[2]);
	printf("[%d, %d, %d]\n", cfg->ceil_rgb[0], cfg->ceil_rgb[1], cfg->ceil_rgb[2]);
}