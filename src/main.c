/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores <adores@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 11:39:36 by adores            #+#    #+#             */
/*   Updated: 2026/07/21 14:52:51 by adores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_assets(t_assets assets, t_map map)
{
	int	i;

	i = 0;
	printf("%s\n", assets.no.path);
	printf("%s\n", assets.so.path);
	printf("%s\n", assets.we.path);
	printf("%s\n", assets.ea.path);
	printf("%d\n", assets.floor_rgb);
	printf("%d\n", assets.ceiling_rgb);
	while (map.grid[i])
	{
		printf("%s\n", map.grid[i]);
		i++;
	}
}

int	main(int ac, char **av)
{
	t_data		data;

	if (ac != 2)
		return (ft_putstr_fd("Error\n Invalid number of arguments.\n", 2), 1);
	init(&data);
	data.fd = open(av[1], O_RDONLY);
	if (data.fd < 0)
		return (ft_putstr_fd("Error\n Can't open file.\n", 2), 1);
	if (is_file_cub(av[1]) == 0)
	{
		if (read_file(&data, &data.assets, &data.map) == 0 \
&& all_assets(data.assets) == 0)
		{
			//print_assets(data.assets, data.map);
			game(&data);
		}
		close(data.fd);
	}
	else
		return (ft_putstr_fd("Error\n Wrong file.\n", 2), 1);
	
	cleanup_and_exit(0, NULL, &data);
}
