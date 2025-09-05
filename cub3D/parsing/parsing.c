/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 09:54:36 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/09/05 17:57:13 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

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

int count_commas(char *str)
{
    int count = 0;
    int i = 0;
    
    while (str[i])
    {
        if (str[i] == ',')
            count++;
        i++;
    }
    return (count);
}

int save_config(t_config *cfg, char *trimmed_line)
{
    char **tmp;
    char *rgb_string;
    char **rgb;
    int result;
    
    tmp = ft_split2(trimmed_line);
    if (!tmp || arr_len(tmp) < 1)
    {
        if (tmp)
            free2d(tmp);
        return (0);
    }
    if (!strcmp(tmp[0], "NO") || !strcmp(tmp[0], "SO") ||
        !strcmp(tmp[0], "EA") || !strcmp(tmp[0], "WE"))
    {
        if (arr_len(tmp) != 2)
        {
            free2d(tmp);
            return (0);
        }
        
        if (!strcmp(tmp[0], "NO"))
        {
            if (cfg->taken.got_no)
            {
                free2d(tmp);
                return (0);
            }
            cfg->no_path = ft_strdup(tmp[1]);
            cfg->taken.got_no = 1;
        }
        else if (!strcmp(tmp[0], "SO"))
        {
            if (cfg->taken.got_so)
            {
                free2d(tmp);
                return (0);
            }
            cfg->so_path = ft_strdup(tmp[1]);
            cfg->taken.got_so = 1;
        }
        else if (!strcmp(tmp[0], "WE"))
        {
            if (cfg->taken.got_we)
            {
                free2d(tmp);
                return (0);
            }
            cfg->we_path = ft_strdup(tmp[1]);
            cfg->taken.got_we = 1;
        }
        else if (!strcmp(tmp[0], "EA"))
        {
            if (cfg->taken.got_ea)
            {
                free2d(tmp);
                return (0);
            }
            cfg->ea_path = ft_strdup(tmp[1]);
            cfg->taken.got_ea = 1;
        }
        
        free2d(tmp);
        return (1);
    }
    if (!strcmp(tmp[0], "F") || !strcmp(tmp[0], "C"))
    {
        rgb_string = extract_rgb_string(trimmed_line, tmp[0]);
        if (!rgb_string)
            return (0);
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
        {
            if (cfg->taken.got_f)
            {
				free2d(tmp);
                free2d(rgb);
                return (0);
			}
            result = validate_and_store_rgb(rgb, cfg->floor_rgb);
            if (result)
                cfg->taken.got_f = 1;
        }
        else
        {
            if (cfg->taken.got_c)
            {
				free2d(tmp);
                free2d(rgb);
                return (0);
            }
            
            result = validate_and_store_rgb(rgb, cfg->ceil_rgb);
            if (result)
                cfg->taken.got_c = 1;
        }
        free2d(rgb);
		free2d(tmp);
        return (result);
    }
    free2d(tmp);
    return (0);
}

int	parse_config(char *file, t_config *cfg)
{
	int fd;
	char *line;
	char *trimmed_line;

	ft_memset(cfg, 0, sizeof(t_config));
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (ft_putstr_fd("Error: Cannot open file!\n", 2), 0);
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
		trimmed_line = ft_strtrim(line, " \t\n\r");
		free(line);
		if (!save_config(cfg, trimmed_line))
		{
			free(trimmed_line);
			close(fd);
			return (ft_putstr_fd("Error: Invalid configurations!\n", 2), 0);
		}
		free(trimmed_line);
	}
	close(fd);
	
	if (!cfg->taken.got_no || !cfg->taken.got_so || !cfg->taken.got_we || 
        !cfg->taken.got_ea || !cfg->taken.got_f || !cfg->taken.got_c)
		return (ft_putstr_fd("Error: Missing required configs\n", 2), 0);
	
	printf("NO: %s\n", cfg->no_path);
    printf("SO: %s\n", cfg->so_path);
    printf("WE: %s\n", cfg->we_path);
    printf("EA: %s\n", cfg->ea_path);
    printf("F: [%d, %d, %d]\n", cfg->floor_rgb[0], cfg->floor_rgb[1], cfg->floor_rgb[2]);
    printf("C: [%d, %d, %d]\n", cfg->ceil_rgb[0], cfg->ceil_rgb[1], cfg->ceil_rgb[2]);
	return (1);
}
