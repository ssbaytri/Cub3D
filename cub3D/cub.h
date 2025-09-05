/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 15:48:46 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/09/05 10:20:00 by ssbaytri         ###   ########.fr       */
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
void			parse_config(char *file, t_config *cfg);

#endif
