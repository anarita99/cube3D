/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores <adores@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 14:03:44 by leramos-          #+#    #+#             */
/*   Updated: 2026/06/26 13:54:25 by adores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	cleanup_mlx(t_data *data)
{
	if (!(data->mlx))
		return ;
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	data->mlx = NULL;
}

void	cleanup_and_exit(int status_code, const char *error_msg, t_data *data)
{
	cleanup_mlx(data);
	if (status_code != 0)
	{
		ft_printf("Error\n");
		if (error_msg)
			ft_printf("%s\n", error_msg);
	}
	free_things(&data->config, &data->map);
	exit(status_code);
}
