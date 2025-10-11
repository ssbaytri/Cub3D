/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 13:21:57 by naessgui          #+#    #+#             */
/*   Updated: 2025/10/11 21:52:49 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../cub.h"

void window_size(t_data *data)
{
	data->Mlx.win_h = WINDOW_HEIGHT;
	data->Mlx.win_w = WINDOW_WIDTH;

}

void draw_map(t_data *data)
{
   int i = 0;
    while (data->map.grid[i])
    {
        int j = 0;
        while (data->map.grid[i][j])
        {
            if (data->map.grid[i][j] == '1')
                draw_rectangle(data->Mlx.img, j, i, GRAY);
            else if (data->map.grid[i][j] == '0' || data->map.grid[i][j] == 'N' || data->map.grid[i][j] == 'S' || data->map.grid[i][j] == 'W' || data->map.grid[i][j] == 'E')
                draw_rectangle(data->Mlx.img, j, i, LIGHT_GRAY);
            j++;
        }
        i++;
    }
}
