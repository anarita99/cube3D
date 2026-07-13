/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runtime.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 10:33:42 by adores            #+#    #+#             */
/*   Updated: 2026/07/13 14:39:53 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RUNTIME_H
# define RUNTIME_H

# include <cub3d.h>

typedef	struct s_range
{
	int	start;
	int	end;
}	t_range;

typedef struct s_draw_data
{
	double		wall_x;
	t_vector	texture_pixel;
	double		step;
	double		texture_pos;
	int			color;
}				t_draw_data;

typedef struct s_wall_data
{
	t_range	range;
	double	perpwalldist;
	int		line_height;
}			t_wall_data;

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
void	draw_vertical_line(t_data *data, int x, t_range range, int color);
void	clear_img(t_data *data);

// Draw Textures
t_texture	select_wall_texture(t_data *data, t_raycast_data *rc);

// Draw
void	draw_ceiling_floor(t_data *data, int x, t_range wall);
void	draw_textured_wall(t_data *data, int x, t_raycast_data *rc, t_wall_data	wall);

// Movement Utils
int		get_orientation_index(char orientation);
char	get_orientation_at(int index);

// Movement
void	move_camera(t_data *data, int keycode);
void	move_player(t_data *data, int keycode);

// Raycast
t_raycast_data	init_raycast_data(t_data *data, size_t current_x);
void	dda_loop(t_raycast_data *rc, t_map map);

// Render
int		render_frame(void *param);

// Events
int		key_handler(int keycode, void *param);
int		destroy_handler(void *param);

// Main
void	game(t_data *data);

#endif