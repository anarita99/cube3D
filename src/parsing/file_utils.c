/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores <adores@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 11:42:53 by adores            #+#    #+#             */
/*   Updated: 2026/06/17 15:19:39 by adores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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

char	*extract_config(char *line)
{
	int	i;

	i = skip_space(line);
	while (line[i] != ' ')
		i ++;
	i += skip_space(&line[i]);
	find_new_line(&line[i]);
	return (&line[i]);
}

int	all_configs(t_config config)
{
	if (config.no_path == NULL)
		return (1);
	if (config.so_path == NULL)
		return (1);
	if (config.we_path == NULL)
		return (1);
	if (config.ea_path == NULL)
		return (1);
	if (config.f_rgb == -1)
		return (1);
	if (config.c_rgb == -1)
		return (1);
	return (0);
}
