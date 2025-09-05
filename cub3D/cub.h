/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 15:48:46 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/09/05 18:35:30 by ssbaytri         ###   ########.fr       */
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
	int			got_no;
	int			got_so;
	int			got_we;
	int			got_ea;
	int			got_f;
	int			got_c;
}				t_marked;

typedef struct s_config
{
	char		*no_path;
	char		*so_path;
	char		*we_path;
	char		*ea_path;
	int			floor_rgb[3];
	int			ceil_rgb[3];
	t_marked	taken;
}				t_config;

void			check_args(int ac, char *str);
int				parse_config(char *file, t_config *cfg);
char			**ft_split2(char *str);
int				arr_len(char **arr);
void			free2d(char **arr);
char			*extract_rgb_string(char *line, char *identifier);
int				validate_and_store_rgb(char **rgb, int *rgb_arr);
int				handle_texture_config(t_config *cfg, char **tmp);
int				handle_color_config(t_config *cfg, char **tmp,
					char *trimmed_line);
int				check_empty_line(char *line);
int				count_commas(char *str);

#endif
