/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores <adores@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 12:16:34 by adores            #+#    #+#             */
/*   Updated: 2026/08/04 11:29:31 by adores           ###   ########.fr       */
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

int	assign_texture(char *line, t_assets *assets, t_types type)
{
	char	*path;

	path = extract_valid_path(line);
	if (!path)
		return (1);
	if (assign_texture_path(assets, path, type) == 1)
		return (1);
	return (0);
}
