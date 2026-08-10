/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 10:25:13 by adores            #+#    #+#             */
/*   Updated: 2026/08/10 13:25:38 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*extract_valid_path(char *line)
{
	char	*path;

	path = ft_strdup(extract_assets(line));
	if (!path)
		return (NULL);
	if (count_words(path, ' ') != 1)
		return (free(path), NULL);
	return (path);
}

static int	assign_texture_path(t_assets *assets, char *path, t_types type)
{
	if (type == NO && assets->no.path == NULL)
		assets->no.path = path;
	else if (type == SO && assets->so.path == NULL)
		assets->so.path = path;
	else if (type == WE && assets->we.path == NULL)
		assets->we.path = path;
	else if (type == EA && assets->ea.path == NULL)
		assets->ea.path = path;
	else
		return (free(path), 1);
	return (0);
}

static bool	are_assets_valid(t_assets assets)
{
	if (assets.no.path == NULL)
		return (false);
	if (assets.so.path == NULL)
		return (false);
	if (assets.we.path == NULL)
		return (false);
	if (assets.ea.path == NULL)
		return (false);
	if (assets.floor_rgb == -1)
		return (false);
	if (assets.ceiling_rgb == -1)
		return (false);
	return (true);
}

static int	parse_asset_line(t_assets *assets, char *line)
{
	t_types	type;
	char	*path;

	if (line[0] == '\n')
		return (0);
	type = find_type(line);
	if (type >= NO && type <= EA)
	{
		path = extract_valid_path(line);
		if (!path)
			return (1);
		if (assign_texture_path(assets, path, type) == 1)
			return (1);
	}
	else if (type == C || type == F)
	{
		if (assign_color(line, assets, type) == 1)
			return (1);
	}
	else if (are_assets_valid(*assets) && type == MAP)
		return (2);
	else
		return (1);
	return (0);
}

bool	is_map_file_valid(t_data *data)
{
	char	*line;
	int		ret;

	ret = 0;
	line = get_next_line(data->fd);
	while (line)
	{
		ret = parse_asset_line(&data->assets, line);
		if (ret == 1)
			return (free(line), false);
		if (ret == 2)
			break ;
		free(line);
		line = get_next_line(data->fd);
	}
	if (!line)
		return (false);
	data->map.grid = make_map_grid(line, data->fd, &data->map);
	if (!is_grid_valid(data->map.grid, data))
		return (false);
	if (rectangularize_map(&data->map) == 1)
		return (false);
	if (!is_map_valid(data->map) || !are_assets_valid(data->assets))
		return (false);
	return (true);
}
