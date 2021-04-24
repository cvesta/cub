/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adds2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvesta <cvesta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 19:02:42 by cvesta            #+#    #+#             */
/*   Updated: 2021/04/24 17:43:10 by cvesta           ###   ########.fr       */
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
	if (cub->texs.south)
	{
		mlx_destroy_image(cub->mlx, cub->texs.south->img);
		free(cub->texs.south);
	}
	if (cub->texs.east)
	{
		mlx_destroy_image(cub->mlx, cub->texs.east->img);
		free(cub->texs.east);
	}
	if (cub->texs.north)
	{
		mlx_destroy_image(cub->mlx, cub->texs.north->img);
		free(cub->texs.north);
	}
	if (cub->texs.west)
	{
		mlx_destroy_image(cub->mlx, cub->texs.west->img);
		free(cub->texs.west);
	}

	if (cub->texs.sprite)
	{
		mlx_destroy_image(cub->mlx, cub->texs.sprite->img);
		free(cub->texs.sprite);
	}
}
