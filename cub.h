/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 15:48:46 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/10/12 10:00:52 by ssbaytri         ###   ########.fr       */
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

#define WHITE 0xFFFFFFFF
#define BLACK 0xFF000000
#define RED 0xFF0000FF
#define GRAY 0x808080FF
#define LIGHT_GRAY 0xD3D3D3FF
#define tile_size 50
#define FOV_ANGLE 60
#define  WALL_STRIP_WIDTH 1
#define WALL_COLOR ((int[]){ 255, 255, 255 })

#define WINDOW_WIDTH 1980
#define WINDOW_HEIGHT 1080

#define MLX_KEY_RIGHT   262
#define MLX_KEY_LEFT    263
#define MLX_KEY_DOWN    264
#define MLX_KEY_UP      265

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
	double				x;
	double				y;
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
	// int 				tile_size;
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
}	
					t_game;
typedef struct s_mlx
{
    mlx_t *mlx;
    mlx_image_t *img;
    int win_w;
    int win_h;
}	t_mlx;

typedef struct s_player
{
	t_pos 	*pos;
    int  turn_dir;
    int walk_dir;
	int rot_direction;
    // mlx_image_t *img_p;
    float move_speed;
    float rot_speed;
    float player_angle;
	// float ray_angle;
	
	// double y_horizontal;
	// double x_horizontal;
	// double y_vertical;
	// double x_vertical;
	
    int color;
    int radius;
}   t_player;

typedef struct s_ray
{
	double ray_angle;
	double wall_hit_x;
	double wall_hit_y;
	double vert_wallhit_x;
	double vert_wallhit_y;
	double horz_wallhit_x;
	double horz_wallhit_y;
	double distance;
	double y_horizontal;
	double x_horizontal;
	double y_vertical;
	double x_vertical;
	double vert_hitdistance;
	double horz_hitdistance;
	int found_horz_wall_hit;
	int found_vert_wall_hit;
	
}t_ray;

typedef struct s_data
{
    t_mlx Mlx;
    t_map map;
	t_config cfg;
    t_player *player;
	t_dir dir;
	t_ray *ray;
}t_data;




void draw_rectangle(mlx_image_t *img, int j, int i, int color);
void draw_player(mlx_image_t *img, t_data *data);
// void init_map(t_data *data);
// void cast_rays(t_data *data);
void window_size(t_data *data);
void init_player(t_data *data);
void    draw_player_line(t_data *data, int x1, int y1, int x2, int y2);
// void draw_player_line(t_data *data , );
void draw_map(t_data *data);
void key_hook(mlx_key_data_t keydata, void *param);
void reset_var(mlx_key_data_t keydata , t_data *data);
int has_wall_at(t_data *data, float x, float y);
void update(void *param);
// void cast_rays(t_data *data);
void horizontal_intersections(t_data *data , t_player *p , int i);
void vertical_intersections(t_data *data, t_player *p , int i);
double normalize_angle(double angle);
 void init_ray(t_ray *ray);
void cast_single_ray(t_data *data,__unused double ray_angle , int stripid);

void cast_rays(void *param);

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
