/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvesta <cvesta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 14:04:45 by cvesta            #+#    #+#             */
/*   Updated: 2021/04/27 22:58:05 by cvesta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	setup_rsp(t_cub *cub)
{
	cub->rsp.x_sprite = 0;
	cub->rsp.y_sprite = 0;
	cub->rsp.tx = 0;
	cub->rsp.ty = 0;
	cub->rsp.x_screen = 0;
	cub->rsp.height = 0;
	cub->rsp.y_start = 0;
	cub->rsp.width = 0;
	cub->rsp.x_start = 0;
	cub->rsp.x_end = 0;
	cub->rsp.x_tex = 0;
	cub->rsp.y_tex = 0;
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
	cub->texture.north = NULL;
	cub->texture.south = NULL;
	cub->texture.west = NULL;
	cub->texture.east = NULL;
	cub->texture.s = NULL;
	cub->tex.north = NULL;
	cub->tex.south = NULL;
	cub->tex.west = NULL;
	cub->tex.east = NULL;
	cub->tex.s = NULL;
	cub->floor = -1;
	cub->ceiling = -1;
	cub->map = NULL;
	cub->image.image = NULL;
	cub->save = 0;
	cub->line_size = 0;
	cub->rsp.numsprites = 0;
	setup_rsp(cub);
}

void	setup_raycast(t_cub *cub, int x)
{
	cub->ray.x_cam = 2 * x / (double)cub->width - 1;
	cub->ray.x_raydir = cub->ray.x_dir + cub->ray.x_flat * cub->ray.x_cam;
	cub->ray.y_raydir = cub->ray.y_dir + cub->ray.y_flat * cub->ray.x_cam;
	cub->ray.x_map = (int)cub->ray.x_posit;
	cub->ray.y_map = (int)cub->ray.y_posit;
	cub->ray.x_deltad = sqrt(1 + (cub->ray.y_raydir * cub->ray.y_raydir)\
	/ (cub->ray.x_raydir * cub->ray.x_raydir));
	cub->ray.y_deltad = sqrt(1 + (cub->ray.x_raydir * cub->ray.x_raydir)\
	/ (cub->ray.y_raydir * cub->ray.y_raydir));
	cub->ray.hit = 0;
}

void	setup_hit(t_cub *cub)
{
	while (cub->ray.hit == 0)
	{
		if (cub->ray.x_side < cub->ray.y_side)
		{
			cub->ray.x_side += cub->ray.x_deltad;
			cub->ray.x_map += cub->ray.x_step;
			if (cub->ray.x_step == 1)
				cub->ray.side = 0;
			else if (cub->ray.x_step == -1)
				cub->ray.side = 1;
		}
		else
		{
			cub->ray.y_side += cub->ray.y_deltad;
			cub->ray.y_map += cub->ray.y_step;
			if (cub->ray.y_step == 1)
				cub->ray.side = 2;
			else if (cub->ray.y_step == -1)
				cub->ray.side = 3;
		}
		if (!ft_strchr("02NSWE", cub->map[cub->ray.x_map][cub->ray.y_map]))
			cub->ray.hit = 1;
	}
}

void	setup_sided(t_cub *cub)
{
	if (cub->ray.x_raydir < 0)
	{
		cub->ray.x_step = -1;
		cub->ray.x_side = (cub->ray.x_posit - cub->ray.x_map)\
		* cub->ray.x_deltad;
	}
	else
	{
		cub->ray.x_step = 1;
		cub->ray.x_side = (cub->ray.x_map + 1.0 - cub->ray.x_posit)\
		* cub->ray.x_deltad;
	}
	if (cub->ray.y_raydir < 0)
	{
		cub->ray.y_step = -1;
		cub->ray.y_side = (cub->ray.y_posit - cub->ray.y_map)\
		* cub->ray.y_deltad;
	}
	else
	{
		cub->ray.y_step = 1;
		cub->ray.y_side = (cub->ray.y_map + 1.0 - cub->ray.y_posit)\
		* cub->ray.y_deltad;
	}
}
