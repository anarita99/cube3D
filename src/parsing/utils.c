/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 14:17:27 by adores            #+#    #+#             */
/*   Updated: 2026/07/13 15:53:00 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	skip_space(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	return (i);
}

char	*find_new_line(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\n')
			str[i] = '\0';
		i++;
	}
	return (str);
}

int	count_commas(char *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if (s[i] == ',')
			count++;
		i++;
	}
	return (count);
}

int	count_words(char *str, char sep)
{
	int	count;
	int	inword;
	int	i;

	count = 0;
	inword = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] != sep)
		{
			if (inword == 0)
			{
				inword = 1;
				count++;
			}
		}
		else
			inword = 0;
		i++;
	}
	return (count);
}
