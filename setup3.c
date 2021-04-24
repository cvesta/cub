/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvesta <cvesta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 21:42:13 by cvesta            #+#    #+#             */
/*   Updated: 2021/04/24 21:53:16 by cvesta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		player_position(t_cub *cub, int x, int y)
{
	if (x < 1 || y < 1)
		return (0);
	cub->raycast.pos_x = x + 0.5;
	cub->raycast.pos_y = y + 0.5;
	cub->raycast.movespeed = 0.10;
	return (1);
}

int		player_flatness(t_cub *cub, char c)
{
	if (c == 'N')
	{
		cub->raycast.flat_x = 0;
		cub->raycast.flat_y = 0.66;
	}
	else if (c == 'S')
	{
		cub->raycast.flat_x = 0;
		cub->raycast.flat_y = -0.66;
	}
	else if (c == 'W')
	{
		cub->raycast.flat_x = -0.66;
		cub->raycast.flat_y = 0;
	}
	else if (c == 'E')
	{
		cub->raycast.flat_x= 0.66;
		cub->raycast.flat_y = 0;
	}
	else
		return (0);
	return (1);
}

int		player_direct(t_cub *cub, char c)
{
	if (c == 'N')
	{
		cub->raycast.dir_x = -1;
		cub->raycast.dir_y = 0;
	}
	else if (c == 'S')
	{
		cub->raycast.dir_x = 1;
		cub->raycast.dir_y = 0;
	}
	else if (c == 'W')
	{
		cub->raycast.dir_x = 0;
		cub->raycast.dir_y = -1;
	}
	else if (c == 'E')
	{
		cub->raycast.dir_x = 0;
		cub->raycast.dir_y = 1;
	}
	else
		return (0);
	return (1);
}

int		setup_player(t_cub *cub)
{
	int		x;
	int 	y;

	x = 0;
	while (cub->map[x])
	{
		y = 0;
		while (cub->map[x][y])
		{
			if (ft_strchr("NSWE", cub->map[x][y]))
			{
				if (!player_direct(cub, cub->map[x][y]))
					return (0);
				if (!player_flatness(cub, cub->map[x][y]))
					return (0);
				if (!player_position(cub, x, y))
					return (0);
				return (1);
			}
			y++;
		}
		x++;
	}
	return (0);
}