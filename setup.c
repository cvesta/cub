/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvesta <cvesta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 14:04:45 by cvesta            #+#    #+#             */
/*   Updated: 2021/04/25 17:28:36 by cvesta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	setup_raysp(t_cub *cub)
{
	cub->raysprite.sprite_x = 0;
	cub->raysprite.sprite_y = 0;
	cub->raysprite.tx = 0;
	cub->raysprite.ty = 0;
	cub->raysprite.screen_x = 0;
	cub->raysprite.height = 0;
	cub->raysprite.start_y = 0;
	cub->raysprite.width = 0;
	cub->raysprite.start_x = 0;
	cub->raysprite.end_x = 0;
	cub->raysprite.tex_x = 0;
	cub->raysprite.tex_y = 0;
	cub->keypress.up = 0;
	cub->keypress.down = 0;
	cub->keypress.left = 0;
	cub->keypress.right = 0;
	cub->keypress.lookl = 0;
	cub->keypress.lookr = 0;
}

void	setup_arg(t_cub *cub)
{
	cub->width = -1;
	cub->height = -1;
	cub->textures.north = NULL;
	cub->textures.south = NULL;
	cub->textures.west = NULL;
	cub->textures.east = NULL;
	cub->textures.sprite = NULL;
	cub->texs.north = NULL;
	cub->texs.south = NULL;
	cub->texs.west = NULL;
	cub->texs.east = NULL;
	cub->texs.sprite = NULL;
	cub->down = -1;
	cub->up = - 1;
	cub->map = NULL;
	cub->img.img = NULL;
	cub->save = 0;
	cub->sizemapline = 0;
	cub->raysprite.numsprites = 0;
	setup_raysp(cub);
}

void	setup_raycast(t_cub *cub, int a)
{
	cub->raycast.camera_x = 2 * a / (double)cub->width - 1;
	cub->raycast.raydir_x = cub->raycast.dir_x + cub->raycast.flat_x *
			cub->raycast.camera_x;
	cub->raycast.raydir_y = cub->raycast.dir_y + cub->raycast.flat_y *
			cub->raycast.camera_x;
	cub->raycast.map_x = (int)cub->raycast.pos_x;
	cub->raycast.map_y = (int)cub->raycast.pos_y;
	cub->raycast.deltadist_x = sqrt(1 + (cub->raycast.raydir_y * cub->raycast
			.raydir_y)\
	/ (cub->raycast.raydir_x * cub->raycast.raydir_x));
	cub->raycast.deltadist_y = sqrt(1 + (cub->raycast.raydir_x * cub->raycast
			.raydir_x)\
	/ (cub->raycast.raydir_y * cub->raycast.raydir_y));
	cub->raycast.hit = 0;
}

void	setup_hit(t_cub *cub)
{
	while (cub->raycast.hit == 0)
	{
		if (cub->raycast.side_x < cub->raycast.side_y)
		{
			cub->raycast.side_x += cub->raycast.deltadist_x;
			cub->raycast.map_x += cub->raycast.step_x;
			if (cub->raycast.step_x == 1)
				cub->raycast.side = 0;
			else if (cub->raycast.step_x == -1)
				cub->raycast.side = 1;
		}
		else
		{
			cub->raycast.side_y += cub->raycast.deltadist_y;
			cub->raycast.map_y += cub->raycast.step_y;
			if (cub->raycast.step_y == 1)
				cub->raycast.side = 2;
			else if (cub->raycast.step_y == -1)
				cub->raycast.side = 3;
		}
		if (!ft_strchr("02NSWE", cub->map[cub->raycast.map_x][cub->raycast.map_y]))
			cub->raycast.hit = 1;
	}
}

void	setup_sided(t_cub *cub)
{
	if (cub->raycast.raydir_x < 0)
	{
		cub->raycast.step_x = -1;
		cub->raycast.side_y = (cub->raycast.pos_x - cub->raycast.map_x)\
		* cub->raycast.deltadist_x;
	}
	else
	{
		cub->raycast.step_x = 1;
		cub->raycast.side_y = (cub->raycast.map_x + 1.0 - cub->raycast.pos_x)\
		* cub->raycast.deltadist_x;
	}
	if (cub->raycast.raydir_y < 0)
	{
		cub->raycast.step_y = -1;
		cub->raycast.side_y = (cub->raycast.pos_y - cub->raycast.map_y)\
		* cub->raycast.deltadist_y;
	}
	else
	{
		cub->raycast.step_y = 1;
		cub->raycast.side_y = (cub->raycast.map_y + 1.0 - cub->raycast.pos_y)\
		* cub->raycast.deltadist_y;
	}
}