/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvesta <cvesta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 21:42:13 by cvesta            #+#    #+#             */
/*   Updated: 2021/04/27 22:35:47 by cvesta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		player_position(t_cub *cub, int x, int y)
{
	if (x < 1 || y < 1)
		return (0);
	cub->ray.x_posit = x + 0.5;
	cub->ray.y_posit = y + 0.5;
	cub->ray.mvspeed = 0.07;
	return (1);
}

int		player_flatness(t_cub *cub, char c)
{
	if (c == 'N')
	{
		cub->ray.x_flat = 0;
		cub->ray.y_flat = 0.66;
	}
	else if (c == 'S')
	{
		cub->ray.x_flat = 0;
		cub->ray.y_flat = -0.66;
	}
	else if (c == 'W')
	{
		cub->ray.x_flat = -0.66;
		cub->ray.y_flat = 0;
	}
	else if (c == 'E')
	{
		cub->ray.x_flat = 0.66;
		cub->ray.y_flat = 0;
	}
	else
		return (0);
	return (1);
}

int		player_direct(t_cub *cub, char c)
{
	if (c == 'N')
	{
		cub->ray.x_dir = -1;
		cub->ray.y_dir = 0;
	}
	else if (c == 'S')
	{
		cub->ray.x_dir = 1;
		cub->ray.y_dir = 0;
	}
	else if (c == 'W')
	{
		cub->ray.x_dir = 0;
		cub->ray.y_dir = -1;
	}
	else if (c == 'E')
	{
		cub->ray.x_dir = 0;
		cub->ray.y_dir = 1;
	}
	else
		return (0);
	return (1);
}

int		setup_player(t_cub *cub)
{
	int	x;
	int	y;

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
