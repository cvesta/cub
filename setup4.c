/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvesta <cvesta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 22:00:19 by cvesta            #+#    #+#             */
/*   Updated: 2021/04/24 22:12:03 by cvesta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		pos_sprite(t_cub *cub)
{
	int		x;
	int		y;
	int		i;
	char	**map;

	x = 0;
	i = 0;
	map = cub->map;
	while (map[x])
	{
		y = 0;
		while (map[x][y])
		{
			if (map[x][y] == '2')
			{
				cub->sprite[i].x = x + 0.5;
				cub->sprite[i].y = y + 0.5;
				i++;
			}
			y++;
		}
		x++;
	}
}

int		count_sprite(t_cub *cub)
{
	int		x;
	int		y;
	char	**map;

	map = cub->map;
	x = 0;
	while (map[x])
	{
		y = 0;
		while (map[x][y])
		{
			if (map[x][y] == '2')
			{
				cub->raysprite.numsprites++;
			}
			y++;
		}
		x++;
	}
	return (1);
}

int		setup_sprite(t_cub *cub)
{
	if (!count_sprite(cub))
		return (0);
	if (!(cub->sprite = malloc(sizeof(t_sprite) * (cub->raysprite.numsprites))))
		return (0);
	if (!(cub->raycast.zbuffer = malloc(sizeof(double) * cub->width)))
		return (0);
	pos_sprite(win);
	return (SUCCESS);
}