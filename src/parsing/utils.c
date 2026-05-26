/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores <adores@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 14:17:27 by adores            #+#    #+#             */
/*   Updated: 2026/05/26 14:19:17 by adores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	skip_space(char *line)
{
	int i;

	i = 0;
	while(line[i] == ' ')
		i++;
	return (i);
}

char	*find_new_line(char *str)
{
	int	i;

	i = 0;
	while(str[i] != '\0')
	{
		if(str[i] == '\n')
			str[i] = '\0';
		i++;
	}
	return (str);
}

void	free_paths(t_config *config)
{
	free(config->no_path);
	free(config->so_path);
	free(config->we_path);
	free(config->ea_path);
	free(config->f_rgb);
	free(config->c_rgb);
}