/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 12:05:44 by leramos-          #+#    #+#             */
/*   Updated: 2026/06/29 14:50:17 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "runtime.h"

static void	move_player(t_data *data, int keycode)
{
	t_vector	new;
	t_vector	current;
	double		step;
	
	if (keycode != XK_d && keycode != XK_a && keycode != XK_w && keycode != XK_s)
		return ;
	step = 0.4;
	current = data->player.loc;
	new = current;

	if (keycode == XK_d)
	{
		new.x = current.x + (step * data->plane.x);
		new.y = current.y + (step * data->plane.y);
	}
		
	else if (keycode == XK_a)
	{
		new.x = current.x - (step * data->plane.x);
		new.y = current.y - (step * data->plane.y);
	}
		
	else if (keycode == XK_w)
	{
		new.x = current.x + (step * data->player.dir.x);
		new.y = current.y + (step * data->player.dir.y);
	}

	else if (keycode == XK_s)
	{
		new.x = current.x - (step * data->player.dir.x);
		new.y = current.y - (step * data->player.dir.y);
	}

	if (is_wall_tile(data->map, (int)new.x, (int)new.y))
	{
		new.x = current.x;
		new.y = current.y;
	}

	if (new.x < 0.0)
		new.x = 1.0;
	else if (new.x > data->map.width - 1.0)
		new.x = data->map.width - 1.0;

	if (new.y < 0.0)
		new.y = 1.0;
	else if (new.y > data->map.height - 1.0)
		new.y = data->map.height - 1.0;
	
	data->player.loc.x = new.x;
	data->player.loc.y = new.y;
}

static void	move_camera(t_data *data, int keycode)
{
	if (data->player.orientation == 'N')
	{
		if (keycode == XK_Left)
			data->player.orientation = 'W';
		else if (keycode == XK_Right)
			data->player.orientation = 'E';
	}

	else if (data->player.orientation == 'E')
	{
		if (keycode == XK_Left)
			data->player.orientation = 'N';
		else if (keycode == XK_Right)
			data->player.orientation = 'S';
	}

	else if (data->player.orientation == 'S')
	{
		if (keycode == XK_Left)
			data->player.orientation = 'E';
		else if (keycode == XK_Right)
			data->player.orientation = 'W';
	}

	else if (data->player.orientation == 'W')
	{
		if (keycode == XK_Left)
			data->player.orientation = 'S';
		else if (keycode == XK_Right)
			data->player.orientation = 'N';
	}
}

int	key_handler(int keycode, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (keycode == XK_Escape)
		destroy_handler(data);
	else if (keycode == XK_Left || keycode == XK_Right)
		move_camera(data, keycode);
	else
		move_player(data, keycode);
	return (0);
}

int	destroy_handler(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	ft_printf("Window closed by user. Exiting.\n");
	
	cleanup_and_exit(0, NULL, data);
	return (0);
}

