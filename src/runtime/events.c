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

int	key_handler(int keycode, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (keycode == XK_Escape)
		destroy_handler(data);
	else if (keycode == XK_Left || keycode == XK_Right)
		move_camera(data, keycode);
	else if (
		keycode == XK_w || keycode == XK_a
		|| keycode == XK_s || keycode == XK_d)
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
