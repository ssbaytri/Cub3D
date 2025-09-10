/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naessgui <naessgui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 13:21:57 by naessgui          #+#    #+#             */
/*   Updated: 2025/09/09 11:51:30 by naessgui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../cub.h"


// void init_map(t_data *data)
// {
// 	int k = 0;
// 	while ( k < 13)
// 	{
// 		data->map.grid[k] = malloc(13);
// 		k++;
// 	}
// 	// Example map initialization
// 	// data->map = malloc(10);
// 	data->map.grid[0] = "1111111111111111111111";
// 	data->map.grid[1] = "1000000000000000000001";	
// 	data->map.grid[2] = "1000000000000000000001";
// 	data->map.grid[3] = "1000110000000000000001";
// 	data->map.grid[4] = "1000110000000000000001";
// 	data->map.grid[5] = "1000000000000000000001";
// 	data->map.grid[6] = "1000000000000001000001";
// 	data->map.grid[7] = "1000000000000001000001";
// 	data->map.grid[8] = "1000000000000001000001";
// 	data->map.grid[9] = "1000000000000001000001";
// 	data->map.grid[10] = "1111111111111111111111";	
// 	data->map.grid[11] = NULL;
	
// }
void window_size(t_data *data)
{
	// data->map.n_rows = 0;
	// while (data->map.grid[data->map.n_rows])
	// 	data->map.n_rows++;
	// data->map.n_column = strlen(data->map.grid[0]);
	
	// data->map.tile_size = 50;
	data->Mlx.win_h =data->map.height * tile_size;
	data->Mlx.win_w = data->map.width * tile_size;
    printf("width =%d , height = %d\n", data->map.width, data->map.height);

	// data->Mlx.win_w = data->map.tile_size * data->map.n_column;
	// data->Mlx.win_h = data->map.tile_size * data->map.n_rows;

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