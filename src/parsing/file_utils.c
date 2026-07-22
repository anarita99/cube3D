/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores <adores@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 11:42:53 by adores            #+#    #+#             */
/*   Updated: 2026/07/22 10:51:59 by adores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_file_cub(char *filename)
{
	int		i;
	char	*cub;

	cub = ".cub";
	i = 0;
	while (filename[i])
	{
		if (filename[i] == '/' && filename[i + 1] == '.')
			return (1);
		i++;
	}
	if (ft_strncmp(&filename[i - 4], cub, 5) == 0)
		return (0);
	return (1);
}

t_types	find_type(char *line)
{
	int	i;

	i = skip_space(line);
	if (ft_strncmp(&line[i], "NO", 2) == 0 && line[i + 2] == ' ')
		return (NO);
	else if (ft_strncmp(&line[i], "SO", 2) == 0 && line[i + 2] == ' ')
		return (SO);
	else if (ft_strncmp(&line[i], "WE", 2) == 0 && line[i + 2] == ' ')
		return (WE);
	else if (ft_strncmp(&line[i], "EA", 2) == 0 && line[i + 2] == ' ')
		return (EA);
	else if (ft_strncmp(&line[i], "F", 1) == 0 && line[i + 1] == ' ')
		return (F);
	else if (ft_strncmp(&line[i], "C", 1) == 0 && line[i + 1] == ' ')
		return (C);
	else if (ft_strncmp(&line[i], "1", 1) == 0)
		return (MAP);
	else
		return (INVALID);
}

char	*extract_assets(char *line)
{
	int	i;

	i = skip_space(line);
	while (line[i] != ' ')
		i++;
	i += skip_space(&line[i]);
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
