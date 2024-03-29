/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvesta <cvesta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 22:00:19 by cvesta            #+#    #+#             */
/*   Updated: 2021/04/27 22:36:55 by cvesta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		pos_sprite(t_cub *cub)
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

int			count_sprite(t_cub *cub)
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
				cub->rsp.numsprites++;
			}
			y++;
		}
		x++;
	}
	return (1);
}

int			setup_sprite(t_cub *cub)
{
	if (!count_sprite(cub))
		return (0);
	if (!(cub->sprite = malloc(sizeof(t_sprite) * (cub->rsp.numsprites))))
		return (0);
	if (!(cub->ray.zbuffer = malloc(sizeof(double) * cub->width)))
		return (0);
	pos_sprite(cub);
	return (1);
}
