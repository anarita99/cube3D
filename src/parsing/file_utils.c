/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores <adores@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 11:42:53 by adores            #+#    #+#             */
/*   Updated: 2026/08/14 14:59:44 by adores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_file_cub(char *filename)
{
	char	*slash;
	char	*name;
	char	*dot;

	slash = ft_strrchr(filename, '/');
	if (slash)
		name = slash + 1;
	else
		name = filename;
	dot = ft_strrchr(name, '.');
	if (!dot)
		return (1);
	if (ft_strncmp(dot, ".cub", 5) == 0)
	{
		if (dot == name)
			return (1);
		return (0);
	}
	return (1);
}

int	is_ws(char c)
{
	return (c == ' ' || c == '\t');
}

t_types	find_type(char *line)
{
	int	i;

	i = skip_ws(line);
	if (ft_strncmp(&line[i], "NO", 2) == 0 && is_ws(line[i + 2]))
		return (NO);
	else if (ft_strncmp(&line[i], "SO", 2) == 0 && is_ws(line[i + 2]))
		return (SO);
	else if (ft_strncmp(&line[i], "WE", 2) == 0 && is_ws(line[i + 2]))
		return (WE);
	else if (ft_strncmp(&line[i], "EA", 2) == 0 && is_ws(line[i + 2]))
		return (EA);
	else if (ft_strncmp(&line[i], "F", 1) == 0 && is_ws(line[i + 1]))
		return (F);
	else if (ft_strncmp(&line[i], "C", 1) == 0 && is_ws(line[i + 1]))
		return (C);
	else if (ft_strncmp(&line[i], "1", 1) == 0
		|| ft_strncmp(&line[i], " ", 1) == 0)
		return (MAP);
	else
		return (INVALID);
}

char	*extract_assets(char *line)
{
	int	i;

	i = skip_ws(line);
	while (line[i] && line[i] != ' ' && line[i] != '\t')
		i++;
	i += skip_ws(&line[i]);
	find_new_line(&line[i]);
	return (&line[i]);
}

int	all_assets(t_assets assets)
{
	if (assets.no.path == NULL)
		return (1);
	if (assets.so.path == NULL)
		return (1);
	if (assets.we.path == NULL)
		return (1);
	if (assets.ea.path == NULL)
		return (1);
	if (assets.floor_rgb == -1)
		return (1);
	if (assets.ceiling_rgb == -1)
		return (1);
	return (0);
}
