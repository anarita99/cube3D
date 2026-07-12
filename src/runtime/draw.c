/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 14:53:44 by leramos-          #+#    #+#             */
/*   Updated: 2026/07/06 15:52:24 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "runtime.h"

void	draw_ceiling_floor(t_data *data, int x, t_range wall)
{
	t_range	range;

	range.start = 0;
	range.end = wall.start - 1;
	draw_vertical_line(data, x, range, data->assets.ceiling_rgb);
	range.start = wall.end;
	range.end = data->height - 1;
	draw_vertical_line(data, x, range, data->assets.floor_rgb);
}

void	draw_textured_wall(
	t_data *data,
	int x,
	t_range	wall,
	t_raycast_data *rc,
	double perpwalldist,
	int line_height
)
{
	double		wall_x;
	int			texture_x;
	int			texture_y;
	double		step;
	double		texture_pos;
	size_t		y;
	int			color;
	t_texture	texture_to_use;
	
	if (rc->side == false)
		wall_x = data->player.loc.y + perpwalldist * rc->ray_dir.y;
	else
		wall_x = data->player.loc.x + perpwalldist * rc->ray_dir.x;
	wall_x -= floor(wall_x);
	texture_to_use = select_wall_texture(data, rc);
	
	texture_x = (int)(wall_x * (double)texture_to_use.width);
	if (rc->side == false && rc->ray_dir.x > 0)
		texture_x = texture_to_use.width - texture_x - 1;
	if (rc->side == true && rc->ray_dir.y < 0)
		texture_x = texture_to_use.width - texture_x - 1;
	
	step = 1.0 * (texture_to_use.height) / line_height;
	texture_pos = (wall.start - data->height / 2 + line_height / 2) * step;

	y = wall.start;
	while ((int)y < wall.end)
	{
		texture_y = (int)(texture_pos) & (texture_to_use.height - 1);
		texture_pos += step;
		color = get_texture_color(&texture_to_use.img, texture_x, texture_y);
		my_mlx_pixel_put(data->img, x, y, color);
		y++;
	}
}
