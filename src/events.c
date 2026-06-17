/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 12:05:44 by leramos-          #+#    #+#             */
/*   Updated: 2026/06/02 18:10:17 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	destroy_handler(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	ft_printf("Window closed by user. Exiting.\n");
	cleanup_and_exit(0, NULL, data);
	return (0);
}

