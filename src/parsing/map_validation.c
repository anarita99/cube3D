/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores <adores@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 10:25:13 by adores            #+#    #+#             */
/*   Updated: 2026/05/26 16:11:35 by adores           ###   ########.fr       */
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

char	*find_path(char *line, char *texture)
{
	int	i;

	i = skip_space(line);
	if ((ft_strncmp(&line[i], texture, 2) == 0) && line[i + 2] == ' ')
	{
		i += 2;
		i += skip_space(&line[i]);
		find_new_line(&line[i]);
		printf("%s", &line[i]);
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

int	find_path_and_allocate (char *line, char *path, char *config)
{
	if (path == NULL)
			path = ft_strdup(find_path(line, config));
	else
	{
		printf("Error: Already has a path for %s.\n", config);
		return (1);
	}
	return (0);
}

int	find_colour_and_allocate (char *line, char *colour, char config)
{
	if (colour == NULL)
		colour = ft_strdup(find_colours(line, config));
	else
	{
		printf("Error: Already has a colour for %c.\n", config);
		return (1);
	}
	return (0);
}



/*int	allocate_path(t_config *config, char *line)
{
	if (find_path(line, "NO") != NULL)
	{
		if (find_path_and_allocate(line, config->no_path, "NO") == 1)
			return (1);
	}
	else if (find_path(line, "SO") != NULL)
	{
		if (find_path_and_allocate(line, config->so_path, "SO") == 1)
			return (1);
	}
	else if (find_path(line, "WE") != NULL)
	{
		if (find_path_and_allocate(line, config->we_path, "WE") == 1)
			return (1);
	}
	else if (find_path(line, "EA") != NULL)
	{
		if (find_path_and_allocate(line, config->ea_path, "EA") == 1)
			return (1);
	}
	else if (find_colours(line, 'F') != NULL)
	{
		if (config->f_rgb == NULL)
			config->f_rgb = ft_strdup(find_colours(line, 'F'));
		else
		{
			printf("Error: Already has a colour for F.\n");
			return (1);
		}
	}
	else if (find_colours(line, 'C') != NULL)
	{
		if (config->c_rgb == NULL)
			config->c_rgb = ft_strdup(find_colours(line, 'C'));
		else
		{
			printf("Error: Already has a colour for C.\n");
			return (1);
		}
	}
	return (0);
}*/

int	allocate_path(t_config *config, char *line)
{
	if (find_path(line, "NO") != NULL)
	{
		if (config->no_path == NULL)
			config->no_path = ft_strdup(find_path(line, "NO"));
		else
		{
			printf("Error: Already has a path for NO.\n");
			return (1);
		}
	}
	else if (find_path(line, "SO") != NULL)
	{
		if (config->so_path == NULL)
			config->so_path = ft_strdup(find_path(line, "SO"));
		else
		{
			printf("Error: Already has a path for SO.\n");
			return (1);
		}
	}
	else if (find_path(line, "WE") != NULL)
	{
		if (config->we_path == NULL)
			config->we_path = ft_strdup(find_path(line, "WE"));
		else
		{
			printf("Error: Already has a path for WE.\n");
			return (1);
		}
	}
	else if (find_path(line, "EA") != NULL)
	{
		if (config->ea_path == NULL)
			config->ea_path = ft_strdup(find_path(line, "EA"));
		else
		{
			printf("Error: Already has a path for EA.\n");
			return (1);
		}
	}
	else if (find_colours(line, 'F') != NULL)
	{
		if (config->f_rgb == NULL)
			config->f_rgb = ft_strdup(find_colours(line, 'F'));
		else
		{
			printf("Error: Already has a colour for F.\n");
			return (1);
		}
	}
	else if (find_colours(line, 'C') != NULL)
	{
		if (config->c_rgb == NULL)
			config->c_rgb = ft_strdup(find_colours(line, 'C'));
		else
		{
			printf("Error: Already has a colour for C.\n");
			return (1);
		}
	}
	return (0);
}

int read_config(char *filename)
{
	char	*line;
	int		fd;
	t_config	config;

	//config = malloc(sizeof(t_config));
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (-1);
	init_configs(&config);
	while((line = get_next_line(fd)))
	{
		allocate_path(&config, line);
		free(line);
	}
	close(fd);
	free_paths(&config);
	return (0);
}

int main()
{
	char *filename = "maps/map.cub";
	if(is_file_cub(filename) == 0)
		read_config(filename);
}