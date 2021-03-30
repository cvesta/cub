/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvesta <cvesta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 14:04:45 by cvesta            #+#    #+#             */
/*   Updated: 2021/03/24 15:06:36 by cvesta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	setup_player(t_cub *cub)
{
	cub->player.x = 0;
	cub->player.y = 0;
	cub->player.width = 0;
	cub->player.height = 0;
	cub->player.spinangle = 0;
	cub->player.turnspeed = 0;
	cub->player.walkspeed = 0;
	cub->player.spinspeed = 0
	cub->player.eyelevel = 0;
	cub->player.directwalk = 0;
	cub->player.directturn = 0;
	cub->player.directwalk_lr = 0;
}

void	setup_set(t_cub *cub)
{
	int i;

	cub->set.width = 0;
	cub->set.height = 0;
	cub->set.columns = 0;
	cub->set.lines = 0;
	cub->set.tile = 0;
	i = 0;
	while (i < TEXTURES)
		cub->set.texs[i++].textures_path = NULL;
	cub->set.down_color = 0;
	cub->set.up_color = 0;
	cub->set.map = 0;
	cub->set.spin_speed = .11;
	cub->set.walk_speed = .11;
	cub->set.updown_speed = 30;
	cub->set.eye_level = 0;
	cub->set.fov = 80 * M_PI / 180;
}