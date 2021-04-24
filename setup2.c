/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvesta <cvesta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 19:47:43 by cvesta            #+#    #+#             */
/*   Updated: 2021/04/24 20:52:49 by cvesta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_image	*make_tex(t_cub *cub, char *way)
{
	t_image *texture;

	if (!(texture = malloc(sizeof(t_image))))
		return (NULL);
	if (!(texture->img = mlx_xpm_file_to_image(cub->mlx, (char *)way,
										   &texture->width, &texture->height)))
	{
		free(texture);
		return (NULL);
	}
	if (!(texture->addr = mlx_get_data_addr(texture->img, &texture->bpp,
										&texture->len_line, &texture->endian)))
	{
		free(texture->img);
		free(texture);
		return (NULL);
	}
	return (texture);
}

int		setup_textures(t_cub *cub)
{
	if ((cub->texs.south = make_tex(cub, cub->texs.south)) == NULL)
		return (0);
	if ((cub->texs.north = make_tex(cub, cub->texs.north)) == NULL)
		return (0);
	if ((cub->texs.west = make_tex(cub, cub->texs.west)) == NULL)
		return (0);
	if ((cub->texs.east = make_tex(cub, cub->texs.east)) == NULL)
		return (0);
	if ((cub->texs.sprite = make_tex(cub, cub->texs.sprite)) == NULL)
		return (0);
	return (1);
}
