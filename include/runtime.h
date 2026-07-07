/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runtime.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 10:33:42 by adores            #+#    #+#             */
/*   Updated: 2026/07/06 15:43:37 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RUNTIME_H
# define RUNTIME_H

# include <cub3d.h>

typedef struct s_raycast_data
{
	t_vector	ray_dir;
	t_vector	delta_distance;
	t_vector	side_distance;
	t_vector	step;
	t_vector	map;
	bool		side;
}				t_raycast_data;

// MLX Initialization
void	init_mlx_window(t_data *data);
void	init_render_image(t_data *data, t_img *img);
void	load_textures(t_data *data);

// Utils
bool	is_wall_tile(t_map map, int x, int y);
int		get_texture_color(t_img *tex_img, int x, int y);

// Draw Utils
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
void	draw_vertical_line(t_data *data, int x, int top, int bottom, int color);
void	clear_img(t_data *data);

// Draw
void	draw_ceiling_floor(t_data *data, int x, int wall_start, int wall_end);
void	draw_textured_wall(t_data *data, int x, int wall_start, int wall_end, t_raycast_data *rc, double perpwalldist, int line_height);

// Movement
void	move_camera(t_data *data, int keycode);
void	move_player(t_data *data, int keycode);

// Render
int		render_frame(void *param);

// Events
int		key_handler(int keycode, void *param);
int		destroy_handler(void *param);

// Main
void	game(t_data *data);

#endif