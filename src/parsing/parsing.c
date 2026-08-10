/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores <adores@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 12:16:34 by adores            #+#    #+#             */
/*   Updated: 2026/08/04 11:29:31 by adores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parsing(t_data *data, int ac, char **av)
{
	if (ac != 2)
		cleanup_and_exit(1, ERR_ARG_NUM, data);
	data->fd = open(av[1], O_RDONLY);
	if (data->fd < 0)
		cleanup_and_exit(1, ERR_INV_FILE, data);
	if (!is_file_cub(av[1]))
		cleanup_and_exit(1, ERR_WRONG_FILE, data);
	if (!is_map_file_valid(data))
		cleanup_and_exit(1, ERR_INVALID_MAP, data);
}
