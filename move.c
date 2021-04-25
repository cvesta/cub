/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvesta <cvesta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 22:38:36 by cvesta            #+#    #+#             */
/*   Updated: 2021/04/24 22:38:54 by cvesta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	back(t_cub *cub)
{
	if (cub->keypress.up == 1)
	{
		if (ft_strchr("0SWEN", cub->map[(int)(cub->raycast.pos_x +\
		cub->raycast.dir_x * cub->raycast.movespeed)][(int)cub->raycast.pos_y]))
			cub->raycast.pos_x += cub->raycast.dir_x * cub->raycast.movespeed;
		if (ft_strchr("0SWEN", cub->map[(int)(cub->raycast.pos_x)]\
		[(int)(cub->raycast.pos_y + cub->raycast.dir_y * cub->raycast.movespeed)]))
			cub->raycast.pos_y += cub->raycast.dir_y * cub->raycast.movespeed;
	}
	if (cub->keypress.down == 1)
	{
		if (ft_strchr("0SWEN", cub->map[(int)(cub->raycast.posx -\
		cub->raycast.dir_x * cub->raycast.movespeed)][(int)(cub->raycast.pos_y)]))
			cub->raycast.pos_x -= cub->raycast.dir_x * cub->raycast.movespeed;
		if (ft_strchr("0SWEN", cub->map[(int)(cub->raycast.pos_x)]\
		[(int)(cub->raycast.pos_y - cub->raycast.dir_y * cub->raycast.movespeed)]))
			cub->raycast.pos_y -= cub->raycast.dir_y * cub->raycast.movespeed;
	}
}

void	sideways(t_cub *cub)
{
	if (cub->keypress.left == 1)
	{
		if (ft_strchr("0SWEN", cub->map[(int)(cub->raycast.pos_x)]\
		[(int)(cub->raycast.pos_y + cub->raycast.dir_x * cub->raycast.movespeed)]))
			cub->raycast.pos_y -= -cub->raycast.dir_x * cub->raycast.movespeed;
		if (ft_strchr("0SWEN", cub->map[(int)(cub->raycast.pos_x -\
		cub->raycast.dir_y * cub->raycast.movespeed)][(int)(cub->raycast
		.pos_y)]))
			cub->raycast.pos_x -= cub->raycast.dir_y * cub->raycast.movespeed;
	}
	if (cub->keypress.right == 1)
	{
		if (ft_strchr("0SWEN", cub->map[(int)(cub->raycast.pos_x)]\
		[(int)(cub->raycast.pos_y - cub->raycast.dir_x * cub->raycast.movespeed)]))
			cub->raycast.pos_y += -cub->raycast.dir_x * cub->raycast.movespeed;
		if (ft_strchr("0SWEN", cub->map[(int)(cub->raycast.pos_x +\
		cub->raycast.dir_y * cub->raycast.movespeed)][(int)(cub->raycast.pos_y)]))
			cub->raycast.pos_x += cub->raycast.dir_y * cub->raycast.movespeed;
	}
}

void	rotate(t_cub *cub, int x)
{
	double	olddirx;
	double	oldplanex;

	olddirx = cub->raycast.dir_x;
	cub->raycast.dir_x = cub->raycast.dir_x * cos(x * cub->raycast.movespeed)\
			- cub->raycast.dir_y * sin(x * cub->raycast.movespeed);
	cub->raycast.dir_y = olddirx * sin(x * cub->raycast.movespeed) + cub->raycast.diry\
			* cos(x * cub->raycast.movespeed);
	oldplanex = cub->raycast.flat_x;
	cub->raycast.flat_x = cub->raycast.flat_x * cos(x * cub->raycast.movespeed)\
			- cub->raycast.flat_y * sin(x * cub->raycast.movespeed);
	cub->raycast.flat_y = oldplanex * sin(x * cub->raycast.movespeed)\
			+ cub->raycast.flat_y * cos(x * cub->raycast.movespeed);
}