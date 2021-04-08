/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_set2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvesta <cvesta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 18:37:13 by cvesta            #+#    #+#             */
/*   Updated: 2021/04/08 18:51:16 by cvesta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		check_map_size(char **map)
{
	int		y;
	int 	x;
	int 	y_max;

	x = 0;
	y_max = 0;
	while (map[x])
	{
		y = 0;
		while (map[x][y])
		{
			if (y > y_max)
				y_max = y;
			y++;
		}
		x++;
	}
	if (!y_max && !x)
		return (0);
	return (1);
}

int		check_player(char **map)
{
	int		i;
	int 	j;
	int 	count;

	i = 0;
	count = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] = 'S' || map[i][j] == 'W' ||
					map[i][j] == 'E')
				count++;
			j++;
		}
		i++;
	}
	if (count != 1)
	{
		ft_putstr_fd("error\nuser count fail\n", 1);
		return (0);
	}
	return (1);
}

int		check_angle(char **map)
{
	int		i;
	int 	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (mapi][j] == '0')
			{
				if ((!map[i - 1][j - 1] || map[i - 1][j - 1] == ' ') ||
				(!map[i + 1][j + 1] || map[i + 1][j  + 1] == ' ') || (!map[i
				- 1][j + 1] || map[i - 1][j + 1] == ' ') || (!map[i + 1][j -
				1] || map[i + 1][j - 1] == ' '))
				{
					return (0);
				}
			}
			j++;
		}
		i++;
	}
	return (1);
}
