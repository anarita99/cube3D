/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 14:53:44 by leramos-          #+#    #+#             */
/*   Updated: 2026/07/13 16:11:03 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "runtime.h"

void	move_camera(t_data *data, int keycode)
{
	int	index;

	index = get_orientation_index(data->player.orientation);
	if (keycode == XK_Left)
		data->player.orientation = get_orientation_at(index - 1);
	else if (keycode == XK_Right)
		data->player.orientation = get_orientation_at(index + 1);
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

static void	clamp_position(t_data *data, t_vector *pos)
{
	if (pos->x < 0.0)
		pos->x = 1.0;
	else if (pos->x > data->map.width - 1.0)
		pos->x = data->map.width - 1.0;
	if (pos->y < 0.0)
		pos->y = 1.0;
	else if (pos->y > data->map.height - 1.0)
		pos->y = data->map.height - 1.0;
}

void	move_player(t_data *data, int keycode)
{
	t_vector	delta;
	t_vector	new;

	delta = compute_move_delta(data, keycode, 0.1);
	new.x = data->player.loc.x + delta.x;
	new.y = data->player.loc.y + delta.y;
	if (is_wall_tile(data->map, (int)new.x, (int)new.y))
		new = data->player.loc;
	clamp_position(data, &new);
	data->player.loc = new;
}
