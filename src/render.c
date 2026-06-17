/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 14:59:20 by leramos-          #+#    #+#             */
/*   Updated: 2026/06/17 16:08:13 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Fake hardcoded map for testing
// 0 = empty space, 1 = wall
static int	g_world_map[24][24] = {
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

static void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_len + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

static void	draw_vertical_line(t_data *data, int x, int top, int bottom, int color)
{
	int	current_y;

	current_y = top;
	while (current_y <= bottom)
	{
		my_mlx_pixel_put(data->img, x, current_y, color);
		current_y++;
	}
}

int	render(void *param)
{
	t_data	*data;
	int		x;
	int		y;

	data = (t_data *)param;
	y = 0;
	while (y < data->height)
	{
		x = 0;
		while (x < data->width)
		{
			my_mlx_pixel_put(data->img, x, y, 0x00008B);
			x++;
		}
		y++;
	}
	my_mlx_pixel_put(data->img, 4, 4, 0x00FF0000);
	draw_vertical_line(data, 5, 0, 60, 0x00FF0000);
	mlx_put_image_to_window(data->mlx, data->win, data->img->img, 0, 0);
	return (0);
}

static int	dda_loop(
	double	*sidedist_x,
	double	*sidedist_y,
	int		*map_x,
	int		*map_y,
	int		step_x,
	int		step_y,
	double	deltadist_x,
	double	deltadist_y
)
{
	int		side;
	bool	hit;

	hit = false;
	while (hit == false)
	{
		// Jump to next map square, either in x-direction, or in y-direction
		if (*sidedist_x < *sidedist_y)
		{
			*sidedist_x += deltadist_x;
			*map_x += step_x;
			side = 0;
		}
		else
		{
			*sidedist_y += deltadist_y;
			*map_y += step_y;
			side = 1;
		}

		// Check if ray has hit a wall
		if (g_world_map[*map_x][*map_y] > 0)
			hit = true;
	}
	return (side);
}

static void	raycasting_loop(size_t current_x)
{
	double		camera_x;
	t_vector	ray_dir;
	t_vector	delta_distance;
	t_vector	side_distance;
	t_vector	step;
	t_vector	map;

	camera_x = 2.0 * x / data->width - 1.0;
	ray_dir.x = data->player.dir.x + data->plane.x * camera_x;
	ray_dir.y = data->player.dir.y + data->plane.y * camera_x;
	delta_distance.x = fabs(1.0 / ray_dir.x);
	delta_distance.y = fabs(1.0 / ray_dir.y);
	map.x = (int)data->player.loc.x;
	map.y = (int)data->player.loc.y;
	if (ray_dir.x < 0)
	{
		step.x = -1;
		side_distance.x = (data->player.loc.x - map.x) * delta_distance.x;
	}
	else
	{
		step.x = 1;
		side_distance.x = (map.x + 1.0 - data->player.loc.x) * delta_distance.x;
	}

	if (ray_dir.y < 0)
	{
		step.y = -1;
		side_distance.y = (data->player.loc.y - map.y) * delta_distance.y;
	}
	else
	{
		step.y = 1;
		side_distance.y = (map.y + 1.0 - data->player.loc.y) * delta_distance.y;
	}
}

int	render_frame(void *param)
{
	t_data	*data;
	size_t	x;
	int		map_x;
	int		map_y;
	double	camera_x;
	double	raydir_x;
	double	raydir_y;
	double	sidedist_x;
	double	sidedist_y;
	double	deltadist_x;
	double	deltadist_y;
	int		step_x;
	int		step_y;
	int		side;
	double	perpwalldist;
	int		line_height;
	int		draw_start;
	int		draw_end;

	data = (t_data *)param;


	// Raycasting Loop
	x = 0;
	while (x < (size_t)data->width)
	{
		raycasting_loop(x);

		// DDA Loop
		side = dda_loop(&sidedist_x, &sidedist_y, &map_x, &map_y,
			step_x, step_y, deltadist_x, deltadist_y);

		// After hitting a wall
		if (side == 0)
			perpwalldist = sidedist_x - deltadist_x;
		else
			perpwalldist = sidedist_y - deltadist_y;
		
		line_height = data->height / perpwalldist;
		draw_start = -line_height / 2 + data->height / 2;
		draw_end = line_height / 2 + data->height / 2;
		
		if (draw_start < 0)
			draw_start = 0;
		if (draw_end >= data->height)
			draw_end = data->height - 1;

		draw_vertical_line(data, x, draw_start, draw_end, 0x00FF0000);
		mlx_put_image_to_window(data->mlx, data->win, data->img->img, 0, 0);

		x++;
	}
	return (0);
}
