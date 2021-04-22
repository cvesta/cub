/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adds2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvesta <cvesta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 19:02:42 by cvesta            #+#    #+#             */
/*   Updated: 2021/04/22 19:05:14 by cvesta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	wipe_image(t_cub *cub)
{
	if (cub->img.img)
		mlx_destroy_image(cub->mlx, cub->img.img);
}

void	wipe_textures(t_cub *cub)
{

}
