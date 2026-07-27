/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 14:53:44 by leramos-          #+#    #+#             */
/*   Updated: 2026/07/27 14:42:51 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_camera(t_data *data, int keycode)
{
	double		step;
	double		angle;
	t_vector	old_dir;
	t_vector	old_plane;

	step = 0.05;
	if (keycode == XK_Left)
		angle = -step;
	else if (keycode == XK_Right)
		angle = step;
	else
		return ;
	old_dir = data->player.dir;
	data->player.dir.x = old_dir.x * cos(angle) - old_dir.y * sin(angle);
	data->player.dir.y = old_dir.x * sin(angle) + old_dir.y * cos(angle);
	old_plane = data->plane;
	data->plane.x = old_plane.x * cos(angle) - old_plane.y * sin(angle);
	data->plane.y = old_plane.x * sin(angle) + old_plane.y * cos(angle);
}

static t_vector	compute_move_delta(t_data *data, int keycode, double step)
{
	t_vector	delta;

	delta.x = 0.0;
	delta.y = 0.0;
	if (keycode == XK_d)
	{
		delta.x = step * data->plane.x;
		delta.y = step * data->plane.y;
	}
	else if (keycode == XK_a)
	{
		delta.x = -step * data->plane.x;
		delta.y = -step * data->plane.y;
	}
	else if (keycode == XK_w)
	{
		delta.x = step * data->player.dir.x;
		delta.y = step * data->player.dir.y;
	}
	else if (keycode == XK_s)
	{
		delta.x = -step * data->player.dir.x;
		delta.y = -step * data->player.dir.y;
	}
	return (delta);
}

static bool	collides(t_map map, t_vector pos)
{
	return (is_wall_tile(map, (int)(pos.x - PLAYER_RADIUS), (int)pos.y)
		|| is_wall_tile(map, (int)(pos.x + PLAYER_RADIUS), (int)pos.y)
		|| is_wall_tile(map, (int)pos.x, (int)(pos.y - PLAYER_RADIUS))
		|| is_wall_tile(map, (int)pos.x, (int)(pos.y + PLAYER_RADIUS)));
}

void	move_player(t_data *data, int keycode)
{
	t_vector	delta;
	t_vector	new;

	delta = compute_move_delta(data, keycode, 0.1);
	new.x = data->player.loc.x + delta.x;
	new.y = data->player.loc.y + delta.y;
	if (collides(data->map, new))
		new = data->player.loc;
	data->player.loc = new;
}
