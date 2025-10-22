/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 01:50:03 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/10/22 06:43:26 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void draw_rect(mlx_image_t *img, int x, int y, int width, int height, uint32_t color)
{
    int px0 = x;
    int py0 = y;
    int px1 = x + width - 1;
    int py1 = y + height - 1;

    if (px1 < 0 || py1 < 0 || px0 >= (int)img->width || py0 >= (int)img->height)
        return;

    if (px0 < 0) px0 = 0;
    if (py0 < 0) py0 = 0;
    if (px1 >= (int)img->width) px1 = (int)img->width - 1;
    if (py1 >= (int)img->height) py1 = (int)img->height - 1;

    for (int yy = py0; yy <= py1; yy++)
        for (int xx = px0; xx <= px1; xx++)
            mlx_put_pixel(img, xx, yy, color);
}

/* --- Bresenham line (kept as you had it) --- */
void draw_line(mlx_image_t *img, int x0, int y0, int x1, int y1, uint32_t color)
{
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;

    while (1)
    {
        if (x0 >= 0 && x0 < (int)img->width &&
            y0 >= 0 && y0 < (int)img->height)
            mlx_put_pixel(img, x0, y0, color);

        if (x0 == x1 && y0 == y1)
            break;

        int e2 = 2 * err;
        if (e2 > -dy)
        {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx)
        {
            err += dx;
            y0 += sy;
        }
    }
}

void render_minimap_player(t_data *data)
{
    int center_x;
    int center_y;
    int size;
    int line_end_x;
    int line_end_y;

    center_x = MINIMAP_OFFSET_X + MINIMAP_SIZE / 2;
    center_y = MINIMAP_OFFSET_Y + MINIMAP_SIZE / 2;
    size = 8;

    // Draw player square
    draw_rect(data->mlx.img, center_x - size / 2, center_y - size / 2,
              size, size, 0xFF0000FF);

    // Draw direction line (simple version)
    line_end_x = center_x + (int)(cos(data->player->player_angle) * 10);
    line_end_y = center_y + (int)(sin(data->player->player_angle) * 10);
    draw_line(data->mlx.img, center_x, center_y, line_end_x, line_end_y,
              0xFFFF00FF);  // Yellow line
}

static void draw_minimap_frame(t_data *data)
{
    int border_thickness = 28;  // Frame thickness

    int x0 = MINIMAP_OFFSET_X;
    int y0 = MINIMAP_OFFSET_Y;
    int x1 = MINIMAP_OFFSET_X + MINIMAP_SIZE + border_thickness;
    int y1 = MINIMAP_OFFSET_Y + MINIMAP_SIZE + border_thickness;

    uint32_t border_color = 0x000000FF; // Black HUD frame

    // TOP border (inside screen)
    draw_rect(data->mlx.img, x0, y0, MINIMAP_SIZE, border_thickness, border_color);

    // BOTTOM border
    draw_rect(data->mlx.img, x0, y1 - border_thickness, MINIMAP_SIZE + border_thickness, border_thickness, border_color);

    // LEFT border
    draw_rect(data->mlx.img, x0, y0, border_thickness, MINIMAP_SIZE, border_color);

    // RIGHT border
    draw_rect(data->mlx.img, x1 - border_thickness, y0, border_thickness, MINIMAP_SIZE, border_color);
}

/* --- stable world->minimap transform and draw loop --- */
void render_minimap(t_data *data)
{

	    draw_rect(data->mlx.img, 
              MINIMAP_OFFSET_X, 
              MINIMAP_OFFSET_Y,
              MINIMAP_SIZE + 28, 
              MINIMAP_SIZE + 28,  
              BLACK);
	
    double player_world_x = data->player->pos->x;
    double player_world_y = data->player->pos->y;

    /* center of minimap in screen coords */
    double center_x = (double)(MINIMAP_OFFSET_X + MINIMAP_SIZE / 2);
    double center_y = (double)(MINIMAP_OFFSET_Y + MINIMAP_SIZE / 2);

    /* world radius covered by minimap (in world units) */
    double world_radius = (MINIMAP_SIZE / 2.0) * MINIMAP_SCALE;

    /* world window bounds */
    double world_start_x = player_world_x - world_radius;
    double world_start_y = player_world_y - world_radius;
    double world_end_x   = player_world_x + world_radius;
    double world_end_y   = player_world_y + world_radius;

    /* tile indices to iterate (clamped to map bounds) */
    int tile_start_x = (int)floor(world_start_x / TILE_SIZE);
    int tile_start_y = (int)floor(world_start_y / TILE_SIZE);
    int tile_end_x   = (int)floor(world_end_x / TILE_SIZE);
    int tile_end_y   = (int)floor(world_end_y / TILE_SIZE);

    /* clamp to map array boundaries if you want safety (optional) */
    if (tile_start_x < -1) tile_start_x = -1;
    if (tile_start_y < -1) tile_start_y = -1;
    /* tile_end can be left as-is; optional clamp with data->map.width/height if known */

    /* size of a tile on minimap in pixels (float to avoid snapping) */
    double tile_pixel_size_f = (double)TILE_SIZE / MINIMAP_SCALE;
    int tile_pixel_size_i = (int)ceil(tile_pixel_size_f);
    if (tile_pixel_size_i < 1)
        tile_pixel_size_i = 1;

    /* iterate tiles and draw each using world->pixel transform (no tile-snapping) */
    for (int ty = tile_start_y; ty <= tile_end_y; ty++)
    {
        for (int tx = tile_start_x; tx <= tile_end_x; tx++)
        {
            /* tile top-left world coordinates */
            double tile_world_x = (double)tx * (double)TILE_SIZE;
            double tile_world_y = (double)ty * (double)TILE_SIZE;

            /* compute tile top-left screen position using centered world transform */
            double screen_x_f = center_x + (tile_world_x - player_world_x) / MINIMAP_SCALE;
            double screen_y_f = center_y + (tile_world_y - player_world_y) / MINIMAP_SCALE;

            /* rounding -> use round to avoid jitter from truncation */
            int screen_x = (int)round(screen_x_f);
            int screen_y = (int)round(screen_y_f);

            /* quick cull: completely outside minimap box? skip */
            if (screen_x + tile_pixel_size_i < MINIMAP_OFFSET_X ||
                screen_x > MINIMAP_OFFSET_X + MINIMAP_SIZE - 1 ||
                screen_y + tile_pixel_size_i < MINIMAP_OFFSET_Y ||
                screen_y > MINIMAP_OFFSET_Y + MINIMAP_SIZE - 1)
                continue;

            /* Determine whether tile is wall or floor.
               Use world coord inside tile to check (add small epsilon to be inside) */
            double check_x = tile_world_x + 0.5 * TILE_SIZE;
            double check_y = tile_world_y + 0.5 * TILE_SIZE;

            uint32_t color;
            if (check_x >= 0 && check_y >= 0 && has_wall_at(data, (float)check_x, (float)check_y))
                color = 0x808080FF;  /* wall gray */
            else
                color = 0xD3D3D3FF;  /* floor light gray */

            /* draw tile as filled rect */
            draw_rect(data->mlx.img, screen_x, screen_y, tile_pixel_size_i, tile_pixel_size_i, color);
        }
    }

    /* Draw player on top (center) */
    render_minimap_player(data);
    draw_minimap_frame(data);
}


