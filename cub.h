/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 15:48:46 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/10/17 00:25:34 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include "libft/libft.h"
# include "mlx/include/MLX42/MLX42.h"
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define WHITE 0xFFFFFFFF
# define BLACK 0xFF000000
# define RED 0xFF0000FF
# define GRAY 0x808080FF
# define LIGHT_GRAY 0xD3D3D3FF
# define TILE_SIZE 64
# define FOV_ANGLE 60
# define WALL_STRIP_WIDTH 1
# define EPSILON 0.0001
# define SENSITIVITY 0.001

# define WINDOW_WIDTH 1920
# define WINDOW_HEIGHT 1080

# define MLX_KEY_RIGHT 262
# define MLX_KEY_LEFT 263
# define MLX_KEY_DOWN 264
# define MLX_KEY_UP 265

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

typedef struct s_mlx
{
	mlx_t				*mlx;
	mlx_image_t			*img;
	int					win_w;
	int					win_h;
}						t_mlx;

typedef struct s_player
{
	t_pos				*pos;
	int					turn_dir;
	int					walk_dir;
	int					rot_direction;
	float				move_speed;
	float				rot_speed;
	float				player_angle;
	int					color;
	int					radius;
}						t_player;

typedef struct s_ray
{
	double				ray_angle;
	double				wall_hit_x;
	double				wall_hit_y;
	double				vert_wallhit_x;
	double				vert_wallhit_y;
	double				horz_wallhit_x;
	double				horz_wallhit_y;
	double				distance;
	double				y_horizontal;
	double				x_horizontal;
	double				y_vertical;
	double				x_vertical;
	double				vert_hitdistance;
	double				horz_hitdistance;
	int					found_horz_wall_hit;
	int					found_vert_wall_hit;
	int					was_vert_hit;
}						t_ray;

typedef struct s_textures
{
	mlx_texture_t		*north;
	mlx_texture_t		*south;
	mlx_texture_t		*east;
	mlx_texture_t		*west;
}						t_textures;

typedef struct s_render
{
	double				corrected_distance;
	double				wall_h;
	int					wall_top_unclamped;
	int					wall_bottom_unclamped;
	int					wall_top;
	int					wall_bottom;
	mlx_texture_t		*texture;
	double				tex_offset;
	int					tex_x;
	int					x;
}						t_render;

typedef struct s_data
{
	t_mlx				mlx;
	t_map				map;
	t_config			cfg;
	t_player			*player;
	t_dir				dir;
	t_ray				*ray;
	t_textures			textures;
}						t_data;

/* ************************************************************************** */
/*                               INITIALIZATION                               */
/* ************************************************************************** */
void					window_size(t_data *data);
void					init_player(t_data *data);
int						load_textures(t_data *data);

/* ************************************************************************** */
/*                             INPUT & MOVEMENT                               */
/* ************************************************************************** */
void					key_hook(mlx_key_data_t keydata, void *param);
void					reset_var(mlx_key_data_t keydata, t_data *data);
void					update(void *param);
void					wall_collision(t_data *data, double new_x,
							double new_y);
int						has_wall_at(t_data *data, float x, float y);
void					mouse_move(void *param);

/* ************************************************************************** */
/*                                 RAYCASTING                                 */
/* ************************************************************************** */
void					cast_rays(void *param);
void					cast_single_ray(t_data *data, int stripid);
void					horizontal_intersections(t_data *data, t_player *p,
							int i);
void					vertical_intersections(t_data *data, t_player *p,
							int i);

/* ************************************************************************** */
/*                                 RENDERING                                  */
/* ************************************************************************** */
mlx_texture_t			*get_wall_texture(t_data *data, int stripid);
double					get_texture_offset(t_data *data, int stripid);
uint32_t				get_texture_color(mlx_texture_t *texture, int x, int y);
uint32_t				create_trgb(int *rgb);
void					render_wall_strip(t_data *data, int stripid);

/* ************************************************************************** */
/*                                   CLEANUP                                  */
/* ************************************************************************** */
int						cleanup_error(t_data *data);
void					cleanup_success(t_data *data);

/* ************************************************************************** */
/*                            ARGUMENT CHECKING                               */
/* ************************************************************************** */
void					check_args(int ac, char *str);

/* ************************************************************************** */
/*                               FILE PARSING                                 */
/* ************************************************************************** */
int						parse_file(char *file, t_data *data);
int						parse_config(int fd, t_config *cfg);
int						parse_map(int fd, t_map_list **map_lines);

/* ************************************************************************** */
/*                               CONFIG HELPERS                               */
/* ************************************************************************** */
int						handle_texture_config(t_config *cfg, char **tmp);
int						handle_color_config(t_config *cfg, char **tmp,
							char *trimmed_line);
char					*extract_rgb_string(char *line, char *identifier);
int						validate_and_store_rgb(char **rgb, int *rgb_arr);
int						count_commas(char *str);

/* ************************************************************************** */
/*                            STRING / ARRAY UTILS                            */
/* ************************************************************************** */
char					**ft_split2(char *str);
int						arr_len(char **arr);
void					free2d(char **arr);
int						check_empty_line(char *line);

/* ************************************************************************** */
/*                             MAP LIST UTILS                                 */
/* ************************************************************************** */
t_map_list				*create_map_node(char *line);
void					add_map_line(t_map_list **list, t_map_list *new_node);
void					free_map_list(t_map_list *list);
int						map_height(t_map_list *head);
int						map_max_width(t_map_list *list);
char					**list_to_2d(t_map_list *head, int *final_height,
							int *final_width);

/* ************************************************************************** */
/*                              MAP VALIDATION                                */
/* ************************************************************************** */
int						is_map_line_valid(char *line);
int						validate_closed_map(t_map *map);
int						validate_map(t_map *map);

#endif
