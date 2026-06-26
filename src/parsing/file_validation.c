/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores <adores@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 10:25:13 by adores            #+#    #+#             */
/*   Updated: 2026/06/26 14:53:57 by adores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	allocate_path(char *line, t_config *config, t_types type)
{
	char	*path;

	path = ft_strdup(extract_config(line));
	if (!path)
		return (ft_putstr_fd(MALL_ERR, 2), 1);
	if (access(path, R_OK))
	{
		ft_putstr_fd("Error\n No access to texture file.\n", 2);
		return (free(path), 1);
	}
	if (type == NO && config->no_path == NULL)
		config->no_path = path;
	else if (type == SO && config->so_path == NULL)
		config->so_path = path;
	else if (type == WE && config->we_path == NULL)
		config->we_path = path;
	else if (type == EA && config->ea_path == NULL)
		config->ea_path = path;
	else
	{
		ft_putstr_fd("Error\n Double path detected.\n", 2);
		return (free(path), 1);
	}
	return (0);
}

static int	allocate_configs(t_config *config, char *line)
{
	t_types	type;

	if (line[0] == '\n')
		return (0);
	type = find_type(line);
	if (type >= NO && type <= EA)
	{
		if (allocate_path(line, config, type) == 1)
			return (1);
	}
	else if (type == C || type == F)
	{
		if (allocate_colour (line, config, type) == 1)
			return (1);
	}
	else if (all_configs(*config) == 0 && type == MAP)
		return (2);
	else
		return (ft_putstr_fd("Error\n Invalid file.\n", 2), 1);
	return (0);
}

int	read_file(t_data *data, t_config *config, t_map *map)
{
	char	*line;
	int		ret;

	line = get_next_line(data->fd);
	while (line)
	{
		ret = allocate_configs(config, line);
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
