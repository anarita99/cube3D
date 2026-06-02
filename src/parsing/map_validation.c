/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores <adores@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 10:25:13 by adores            #+#    #+#             */
/*   Updated: 2026/06/02 10:15:28 by adores           ###   ########.fr       */
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
	{
		if(filename[i] == '/' && filename[i + 1] == '.')
			return (1);
		i++;
	}
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
	else if (ft_strncmp(&line[i], "1", 1) == 0)
		return (MAP);
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
	if (!path)
		return (ft_putstr_fd("Error: Malloc error.\n", 2), 1);
	if (access(path, O_RDONLY))
	{
		ft_putstr_fd("Error: No access to texture file.\n", 2);
		return(free(path), 1);
	}
	if (type == NO && config->no_path == NULL)
		config->no_path = path;
	else if(type == SO && config->so_path == NULL)
		config->so_path = path;
	else if(type == WE && config->we_path == NULL)
		config->we_path = path;
	else if(type == EA && config->ea_path == NULL)
		config->ea_path = path;
	else
	{
		ft_putstr_fd("Error: Double path detected.\n", 2);
		return (free(path), 1);
	}
	return (0);
}

int	allocate_configs(t_config *config, char *line)
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
	else if (type == MAP)
	{
		printf("map\n");
		return (2);
	}
	else
		return (1);
	return (0);
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
	return(0);
}

int	read_config(char *filename, t_config *config)
{
	char	*line;
	int		fd;
	int		ret;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (ft_putstr_fd("Error: Can't open file.\n", 2), 1);
	init_configs(config);
	line = get_next_line(fd);
	while (line)
	{
		ret = allocate_configs(config, line);
		if (ret == 1)
		{
			free(line);
			close(fd);
			return (1);
		}
		if (ret == 2)
		{
			free(line);
			close(fd);
			return (0);
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}

void	print_config(t_config config)
{

	printf("%s\n", config.no_path);
	printf("%s\n", config.so_path);
	printf("%s\n", config.we_path);
	printf("%s\n", config.ea_path);
	
	printf("%d\n", config.f_rgb);
	printf("%d\n", config.c_rgb);
}

int main(int ac, char **av)
{
	t_config config;
	if (ac != 2)
		return (ft_putstr_fd("Error: Invalid number of arguments.\n", 2), 1);
	if (is_file_cub(av[1]) == 0)
	{
		if (read_config(av[1], &config) == 0 && all_configs(config) == 0)
		{
			print_config(config);
		}
		free_paths(&config);
		
	}
	else
		return (ft_putstr_fd("Error: Wrong file.\n", 2), 1);
	return (0);
}
