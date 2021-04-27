/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvesta <cvesta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 16:23:16 by cvesta            #+#    #+#             */
/*   Updated: 2021/04/27 21:51:23 by cvesta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			check_vert(int j, char **map, char *vert)
{
	int		i;

	while (--j >= 0)
	{
		i = 0;
		while (map[i])
		{
			if (j < (int)ft_strlen(map[i]))
				vert[i] = map[i][j];
			else
				vert[i] = ' ';
			i++;
		}
		vert[i] = '\0';
		if (!(check_insulation(vert)))
			return (0);
	}
	return (1);
}

int			check_insulation(char *line)
{
	char	**array;
	char	*l;
	int		i;

	i = 0;
	if (!(l = ft_strtrim(line, " ")))
		return (0);
	if (!(array = ft_split(l, ' ')))
	{
		free(l);
		return (0);
	}
	while (array[i])
	{
		if (array[i][0] != '1' || array[i][ft_strlen(array[i]) - 1] != '1')
		{
			free(l);
			free_array(array);
			return (0);
		}
		i++;
	}
	free(l);
	free_array(array);
	return (1);
}

int			check_char(char *line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '1' && line[i] != '0' && line[i] != ' ' &&
			line[i] != '2' && line[i] != 'N' && line[i] != 'S' &&
			line[i] != 'E' && line[i] != 'W')
			return (0);
		if (line[i] == '0' && (line[i - 1] == ' ' ||
			line[i + 1] == ' '))
			return (0);
		i++;
	}
	return (1);
}

int			check_map(char **map)
{
	int		i;
	int		j;
	char	*vert_line;

	i = -1;
	j = 0;
	while (map[++i])
	{
		if ((int)ft_strlen(map[i]) > j)
			j = (int)ft_strlen(map[i]);
		if (!(check_char(map[i])) || !(check_insulation(map[i])))
			return (0);
	}
	if (!(vert_line = malloc(sizeof(char) * i + 1)))
		return (0);
	if (!check_vert(j, map, vert_line))
		return (0);
	free(vert_line);
	if (!check_map_size(map))
		return (0);
	if (!check_player(map))
		return (0);
	if (!check_angle(map))
		return (0);
	return (1);
}
