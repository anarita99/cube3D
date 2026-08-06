/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 12:05:44 by leramos-          #+#    #+#             */
/*   Updated: 2026/07/13 16:09:45 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	key_handler(int keycode, void *param, bool state)
{
	t_data	*data;

	data = (t_data *)param;
	if (keycode == XK_Escape)
		destroy_handler(data);
	else if (keycode == XK_w)
		data->movement.forward = state;
	else if (keycode == XK_s)
		data->movement.backward = state;
	else if (keycode == XK_a)
		data->movement.left = state;
	else if (keycode == XK_d)
		data->movement.right = state;
	else if (keycode == XK_Left)
		data->movement.look_left = state;
	else if (keycode == XK_Right)
		data->movement.look_right = state;
	return (0);
}

int	key_press_handler(int keycode, void *param)
{
	return (key_handler(keycode, param, true));
}

int	key_release_handler(int keycode, void *param)
{
	return (key_handler(keycode, param, false));
}

int	destroy_handler(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	ft_printf("Window closed by user. Exiting.\n");
	cleanup_and_exit(0, NULL, data);
	return (0);
}
