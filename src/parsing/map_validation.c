/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores <adores@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 10:25:13 by adores            #+#    #+#             */
/*   Updated: 2026/05/29 14:57:21 by adores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	is_file_cub(char *filename)
{
	int		i;
	char	*cub;

	cub = ".cub";
	i = 0;
	while (filename[i])
		i++;
	if (ft_strncmp(&filename[i - 4], cub, 5) == 0)
		return (0);
	return (1);
}

t_types find_type(char *line)
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
	else
		return (ft_putstr_fd("Error: Invalid config.\n", 2), INVALID);
}

char	*extract_config(char *line)
{
	int i;
	i = skip_space(line);
	while(line[i] != ' ')
		i ++;
	i += skip_space(&line[i]);
	find_new_line(&line[i]);

	return (&line[i]);
}

static int	allocate_path(char *line, t_config *config, t_types type)
{
	char *path;

	path = ft_strdup(extract_config(line));
	if(!path)
		return (ft_putstr_fd("Error: Malloc error.\n", 2), 1);
	if (type == NO && config->no_path == NULL)
		config->no_path = path;
	else if(type == SO && config->so_path == NULL)
		config->so_path = path;
	else if(type == WE && config->we_path == NULL)
		config->we_path = path;
	else if(type == EA && config->ea_path == NULL)
		config->ea_path = path;
	else
		return (ft_putstr_fd("Error: Double path detected.\n", 2), free(path), 1);
	return (0);
}

int	allocate_configs(t_config *config, char *line)
{
	t_types type;
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
	return (0);
}

int	read_config(char *filename, t_config *config)
{
	char	*line;
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (-1);
	init_configs(config);
	line = get_next_line(fd);
	while (line)
	{
		if (line[0] != '\n' && allocate_configs(config, line) == 1)
		{
			free(line);
			close(fd);
			return (1);
			//break;
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}

void	print_config(t_config config)
{
	int i = 0;
	printf("%s\n", config.no_path);
	printf("%s\n", config.so_path);
	printf("%s\n", config.we_path);
	printf("%s\n", config.ea_path);
	while(i < 3)
	{
		printf("%d\n", config.f_rgb[i]);
		i++;
	}
	i = 0;
	while(i < 3)
	{
		printf("%d\n", config.c_rgb[i]);
		i++;
	}
}

int main()
{
	t_config config;
	char *filename = "maps/map.cub";
	if (is_file_cub(filename) == 0)
	{
		if(read_config(filename, &config) == 0)
			print_config(config);
		free_paths(&config);
	}
		

}