/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores <adores@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 10:25:13 by adores            #+#    #+#             */
/*   Updated: 2026/05/27 16:18:21 by adores           ###   ########.fr       */
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
	else if (ft_strncmp(&line[i], "F", 2) == 0 && line[i + 1] == ' ')
		return (F);
	else if (ft_strncmp(&line[i], "C", 2) == 0 && line[i + 1] == ' ')
		return (C);
	else
		return(ft_putstr_fd("Error: Invalid config.", 2), INVALID);
}

char	*find_path(char *line, char *texture)
{
	int	i;

	i = skip_space(line);
	if ((ft_strncmp(&line[i], texture, 2) == 0) && line[i + 2] == ' ')
	{
		i += 2;
		i += skip_space(&line[i]);
		find_new_line(&line[i]);
		printf("%s\n", &line[i]);
		return (&line[i]);
	}
	return (NULL);
}

char	*find_colours(char *line, char configs)
{
	int	i;

	i = skip_space(line);
	if (line[i] == configs && line[i + 1] == ' ')
	{
		i += 2;
		i += skip_space(&line[i]);
		find_new_line(&line[i]);
		printf("%s", &line[i]);
		return (&line[i]);
	}
	return(NULL);
}

int	find_path_and_allocate (char *line, char **path, char *config)
{
	if (*path == NULL)
		*path = ft_strdup(find_path(line, config));
	else
	{
		ft_putstr_fd("Error: Double path detected", 2);
		return (1);
	}
	return (0);
}

int	find_colour_and_allocate (char *line, t_config *config, char colour)
{
	if(colour == 'F')
	{
		if (config->f_rgb == NULL)
			config->f_rgb = ft_strdup(find_colours(line, colour));
		else
		{
			ft_putstr_fd("Error: Double colour detected", 2);
			return (1);
		}
	}
	else if(colour == 'C')
	{
		if (config->c_rgb == NULL)
			config->c_rgb = ft_strdup(find_colours(line, colour));
		else
		{
			ft_putstr_fd("Error: Double colour detected", 2);
			return (1);
		}
	}
	return (0);
}

int	allocate_path(t_config *config, char *line)
{
	if (find_path(line, "NO") != NULL)
	{
		if (find_path_and_allocate(line, &config->no_path, "NO") == 1)
			return (1);
	}
	else if (find_path(line, "SO") != NULL)
	{
		if (find_path_and_allocate(line, &config->so_path, "SO") == 1)
			return (1);
	}
	else if (find_path(line, "WE") != NULL)
	{
		if (find_path_and_allocate(line, &config->we_path, "WE") == 1)
			return (1);
	}
	else if (find_path(line, "EA") != NULL)
	{
		if (find_path_and_allocate(line, &config->ea_path, "EA") == 1)
			return (1);
	}
	else if (find_colours(line, 'F') != NULL)
	{
		if(find_colour_and_allocate(line, &config, 'F') == 1)
			return (1);
	}
	else if (find_colours(line, 'C') != NULL)
	{
		if(find_colour_and_allocate(line, &config, 'C') == 1)
			return (1);
	}
	return (0);
}

int read_config(char *filename, t_config *config)
{
	char	*line;
	int		fd;

	//config = malloc(sizeof(t_config));
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (-1);
	init_configs(config);
	line = get_next_line(fd);
	while(line)
	{
		if(allocate_path(config, line) == 1)
		{
			free(line);
			break;
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}

void print_config(t_config config)
{
	printf("%s\n", config.no_path);
	printf("%s\n", config.so_path);
	printf("%s\n", config.we_path);
	printf("%s\n", config.ea_path);
	printf("%s\n", config.f_rgb);
	printf("%s\n", config.c_rgb);
}

int main()
{
	t_config config;
	char *filename = "maps/map.cub";
	if(is_file_cub(filename) == 0)
		read_config(filename, &config);
	print_config(config);
	free_paths(&config);
}