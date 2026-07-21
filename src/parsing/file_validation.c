/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores <adores@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 10:25:13 by adores            #+#    #+#             */
/*   Updated: 2026/07/21 15:01:46 by adores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	allocate_path(char *line, t_assets *assets, t_types type)
{
	char	*path;

	path = ft_strdup(extract_assets(line));
	if (!path)
		return (ft_putstr_fd(MALL_ERR, 2), 1);
	/*if (access(path, R_OK))
	{
		ft_putstr_fd("Error\n No access to texture file.\n", 2);
		return (free(path), 1);
	}*/
	if (type == NO && assets->no.path == NULL)
		assets->no.path = path;
	else if (type == SO && assets->so.path == NULL)
		assets->so.path = path;
	else if (type == WE && assets->we.path == NULL)
		assets->we.path = path;
	else if (type == EA && assets->ea.path == NULL)
		assets->ea.path = path;
	else
	{
		ft_putstr_fd("Error\n Double path detected.\n", 2);
		return (free(path), 1);
	}
	return (0);
}

static int	allocate_assets(t_assets *assets, char *line)
{
	t_types	type;

	if (line[0] == '\n')
		return (0);
	type = find_type(line);
	if (type >= NO && type <= EA)
	{
		if (allocate_path(line, assets, type) == 1)
			return (1);
	}
	else if (type == C || type == F)
	{
		if (allocate_colour (line, assets, type) == 1)
			return (1);
	}
	else if (all_assets(*assets) == 0 && type == MAP)
		return (2);
	else
		return (ft_putstr_fd("Error\n Invalid file.\n", 2), 1);
	return (0);
}

int	read_file(t_data *data, t_assets *assets, t_map *map)
{
	char	*line;
	int		ret;

	line = get_next_line(data->fd);
	while (line)
	{
		ret = allocate_assets(assets, line);
		if (ret == 1)
			return (free(line), 1);
		if (ret == 2)
			break ;
		free(line);
		line = get_next_line(data->fd);
	}
	if (!line)
		return (ft_putstr_fd("Error\n No map found.\n", 2), 1);
	map->grid = make_map_grid(line, data->fd, map);
	if (!map->grid || valid_characters(map->grid, data) == 1)
		return (1);
	if (put_map_rect(map) == 1)
		return (1);
	if (is_map_valid(map->grid, map->height) == 1)
		return (1);
	return (0);
}
