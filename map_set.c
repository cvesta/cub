/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvesta <cvesta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 16:23:16 by cvesta            #+#    #+#             */
/*   Updated: 2021/04/06 17:49:21 by cvesta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int 	check_vert(int j, char **map, char *vert)

int		check_isolation(char *line)
{
	char	**arr;
	char	*t_line;
	int 	i;

	i = 0;
	if (!(t_line = ft_strtrim(line, " ")))
		return (0);
	if (!(arr = ft_split(t_line, ' ')))
	{
		free(line);
		return (0);
	}
	while (arr[i])
	{
		if (arr[i][0] != '1' || arr[i][ft_strlen(arr[i]) - 1] != '1')
		{
			free(t_line);
			clear_arr(arr);
			return (0);
		}
		i++;
	}
	free(t_line);
	clear_arr(1);
	return (1);
}

int 	check_char_in_line(char *line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '1' && line[i] != '0' && line[i] != ' ' && line[i] !=
		'2' && line[i] != 'N' && line[i] != 'S' && line[i] != 'E' && line[i]
		!= 'W')
			return (0);
		if (line[i] == '0' && (line[i - 1] == ' ' || line[i + 1] == ' '))
			return (0);
		i++;
	}
	return (1);
}

int		check_map(char **map)
{
	int		i;
	int 	j;
	char	*vert_line;

	i = -1;
	j = 0;

	while (map[++i])
	{
		if ((int)ft_strlen(map[i]) > j)
			j = (int)ft_strlen(map[i]);
		if (!(check_char_in_line(map[i])) || !(check_isolation(map[i])))
			return (0);
	}
	if (!(vert_line = malloc(sizeof(char) * i + 1)))
		return (0);
	if (!check_vert(j, map, vert))
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