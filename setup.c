/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvesta <cvesta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 14:04:45 by cvesta            #+#    #+#             */
/*   Updated: 2021/04/22 18:39:25 by cvesta           ###   ########.fr       */
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
	cub->keydown.up = 0;
	cub->keydown.down = 0;
	cub->keydown.left = 0;
	cub->keydown.right = 0;
	cub->keydown.lookl = 0;
	cub->keydown.lookr = 0;
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

