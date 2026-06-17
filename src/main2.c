/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores <adores@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 11:39:36 by adores            #+#    #+#             */
/*   Updated: 2026/06/15 12:44:20 by adores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	print_config(t_config config, t_game game)
{
	int	i;

	i = 0;
	printf("%s\n", config.no_path);
	printf("%s\n", config.so_path);
	printf("%s\n", config.we_path);
	printf("%s\n", config.ea_path);
	printf("%d\n", config.f_rgb);
	printf("%d\n", config.c_rgb);
	while (game.map[i])
	{
		printf("%s\n", game.map[i]);
		i++;
	}
}

int	main(int ac, char **av)
{
	t_config	config;
	t_game		game;
	int			line;

	if (ac != 2)
		return (ft_putstr_fd("Error\n Invalid number of arguments.\n", 2), 1);
	game.fd = open(av[1], O_RDONLY);
	if (game.fd < 0)
		return (ft_putstr_fd("Error\n Can't open file.\n", 2), 1);
	init_configs(&config, &game);
	if (is_file_cub(av[1]) == 0)
	{
		if (read_file(&game, &config) == 0 && all_configs(config) == 0)
		{
			print_config(config, game);
			line = find_big_line(game.map);
			printf("%d\n", line);
		}
		free_things(&config, &game);
	}
	else
		return (ft_putstr_fd("Error\n Wrong file.\n", 2), 1);
	return (0);
}
