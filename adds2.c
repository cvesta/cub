/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adds2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvesta <cvesta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 19:02:42 by cvesta            #+#    #+#             */
/*   Updated: 2021/04/27 21:36:01 by cvesta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	wipe_image(t_cub *cub)
{
	if (cub->image.image)
		mlx_destroy_image(cub->mlx, cub->image.image);
}

void	wipe_textures(t_cub *cub)
{
	if (cub->tex.south)
	{
		mlx_destroy_image(cub->mlx, cub->tex.south->image);
		free(cub->tex.south);
	}
	if (cub->tex.north)
	{
		mlx_destroy_image(cub->mlx, cub->tex.north->image);
		free(cub->tex.north);
	}
	if (cub->tex.east)
	{
		mlx_destroy_image(cub->mlx, cub->tex.east->image);
		free(cub->tex.east);
	}
	if (cub->tex.west)
	{
		mlx_destroy_image(cub->mlx, cub->tex.west->image);
		free(cub->tex.west);
	}
	if (cub->tex.s)
	{
		mlx_destroy_image(cub->mlx, cub->tex.s->image);
		free(cub->tex.s);
	}
}

void	pxl_put(t_image *image, int x, int y, int colour)
{
	unsigned char		*dest;

	dest = (unsigned char *)&colour;
	image->addr[y * image->len_line + x *\
		(image->bpp / 8)] = dest[0];
	image->addr[y * image->len_line + x *\
		(image->bpp / 8) + 1] = dest[1];
	image->addr[y * image->len_line + x *\
		(image->bpp / 8) + 2] = dest[2];
}
