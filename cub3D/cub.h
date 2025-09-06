/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 15:48:46 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/09/06 20:33:10 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include "libft/libft.h"
# include "mlx/include/MLX42/MLX42.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_marked
{
	int					got_no;
	int					got_so;
	int					got_we;
	int					got_ea;
	int					got_f;
	int					got_c;
}						t_marked;

typedef struct s_dir
{
	int					n;
	int					s;
	int					w;
	int					e;
}						t_dir;

typedef struct s_pos
{
	int					x;
	int					y;
}						t_pos;

typedef struct s_map_list
{
	char				*line;
	struct s_map_list	*next;
}						t_map_list;

typedef struct s_map
{
	t_map_list			*list;
	char				**grid;
	int					height;
	int					width;
	t_pos				player_pos;
	char				player_dir;
	t_dir				dir_count;
}						t_map;

typedef struct s_config
{
	char				*no_path;
	char				*so_path;
	char				*we_path;
	char				*ea_path;
	int					floor_rgb[3];
	int					ceil_rgb[3];
	t_marked			taken;
}						t_config;

typedef struct s_game
{
	void				*mlx;
	void				*win;
	t_config			cfg;
	t_map				map;
}						t_game;

/* ************************************************************************** */
/*                            Argument Checking                               */
/* ************************************************************************** */
void					check_args(int ac, char *str);

/* ************************************************************************** */
/*                            File Parsing                                    */
/* ************************************************************************** */
int						parse_file(char *file, t_game *cub);
int						parse_config(int fd, t_config *cfg);
int						parse_map(int fd, t_map_list **map_lines);

/* ************************************************************************** */
/*                            Config Helpers                                  */
/* ************************************************************************** */
int						handle_texture_config(t_config *cfg, char **tmp);
int						handle_color_config(t_config *cfg, char **tmp,
							char *trimmed_line);
char					*extract_rgb_string(char *line, char *identifier);
int						validate_and_store_rgb(char **rgb, int *rgb_arr);
int						count_commas(char *str);

/* ************************************************************************** */
/*                            String / Array Utils                            */
/* ************************************************************************** */
char					**ft_split2(char *str);
int						arr_len(char **arr);
void					free2d(char **arr);
int						check_empty_line(char *line);

/* ************************************************************************** */
/*                            Map List Utils                                  */
/* ************************************************************************** */
t_map_list				*create_map_node(char *line);
void					add_map_line(t_map_list **list, t_map_list *new_node);
void					free_map_list(t_map_list *list);
int						map_height(t_map_list *head);
int						map_max_width(t_map_list *list);
char					**list_to_2d(t_map_list *head, int *final_height,
							int *final_width);

/* ************************************************************************** */
/*                            Map Validation                                  */
/* ************************************************************************** */
int						is_map_line_valid(char *line);
int						validate_closed_map(t_map *map);
int						validate_map(t_map *map);

#endif
