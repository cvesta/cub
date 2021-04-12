/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvesta <cvesta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 14:04:45 by cvesta            #+#    #+#             */
/*   Updated: 2021/04/12 17:36:50 by cvesta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	setup_raysp(t_cub *cub);
{

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