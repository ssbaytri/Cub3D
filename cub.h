/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 15:48:46 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/10/23 05:13:34 by ssbaytri         ###   ########.fr       */
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

# define MINIMAP_SIZE 200
# define MINIMAP_OFFSET_X 0
# define MINIMAP_OFFSET_Y 0
# define MINIMAP_SCALE 3

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
	mlx_texture_t		*door;
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

typedef struct s_animation
{
	mlx_texture_t		*frames[6];
	int					current_frame;
	int					is_playing;
	int					frame_delay;
	int					frame_counter;
	int					total_frames;
}						t_animation;

typedef struct s_pixel_coord
{
	int					x;
	int					y;
}						t_pixel_coord;

typedef struct s_weapon_draw
{
	int					weapon_x;
	int					weapon_y;
	int					final_width;
	int					final_height;
	double				scale;
}						t_weapon_draw;

typedef struct s_point
{
	int					x;
	int					y;
}						t_point;

typedef struct s_minimap_bounds
{
	double				player_x;
	double				player_y;
	double				center_x;
	double				center_y;
	double				world_start_x;
	double				world_start_y;
	double				world_end_x;
	double				world_end_y;
}						t_minimap_bounds;

typedef struct s_tile_bounds
{
	int					start_x;
	int					start_y;
	int					end_x;
	int					end_y;
}						t_tile_bounds;

typedef struct s_tile_draw
{
	t_minimap_bounds	bounds;
	int					tx;
	int					ty;
	int					screen_x;
	int					screen_y;
	int					tile_size;
}						t_tile_draw;

typedef struct s_door
{
	int					x;
	int					y;
	int					is_open;
}						t_door;

typedef struct s_door_list
{
	t_door				*doors;
	int					count;
}						t_door_list;

typedef struct s_data
{
	t_mlx				mlx;
	t_map				map;
	t_config			cfg;
	t_player			*player;
	t_dir				dir;
	t_ray				*ray;
	t_textures			textures;
	t_animation			weapon;
	t_door_list			door_list;
}						t_data;

/* ************************************************************************** */
/*                               INITIALIZATION                               */
/* ************************************************************************** */
void					window_size(t_data *data);
void					init_player(t_data *data);
int						load_textures(t_data *data);
bool					load_weapon_animation(t_data *data);
int						load_door_texture(t_data *data);
void					find_all_doors(t_data *data);

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
void					mouse_click_hook(mouse_key_t button, action_t action,
							modifier_key_t mods, void *param);
void					update_weapon_animation(t_data *data);
t_door					*find_nearest_door(t_data *data);

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
void					render_minimap(t_data *data);
void					draw_weapon(t_data *data);
void					draw_rect(mlx_image_t *img, t_point start, t_point size,
							uint32_t color);
void					draw_line(mlx_image_t *img, t_point p0, t_point p1,
							uint32_t color);
void					render_minimap_player(t_data *data);
void					draw_minimap_frame(t_data *data);
void					calculate_world_bounds(t_data *data,
							t_minimap_bounds *bounds);
void					calculate_tile_bounds(t_minimap_bounds *bounds,
							t_tile_bounds *tiles);
int						calculate_tile_pixel_size(void);
int						find_door_at(t_data *data, int map_x, int map_y);
uint32_t				get_door_color(t_data *data, int door_index);

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
