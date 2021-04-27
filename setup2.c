/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvesta <cvesta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 19:47:43 by cvesta            #+#    #+#             */
/*   Updated: 2021/04/27 22:34:40 by cvesta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_image		*make_tex(t_cub *cub, char *way)
{
	t_image *tex;

	if (!(tex = malloc(sizeof(t_image))))
		return (NULL);
	if (!(tex->image = mlx_xpm_file_to_image(cub->mlx, (char *)way,
	&tex->width, &tex->height)))
	{
		free(tex);
		return (NULL);
	}
	if (!(tex->addr = mlx_get_data_addr(tex->image, &tex->bpp,
										&tex->len_line, &tex->endian)))
	{
		free(tex->image);
		free(tex);
		return (NULL);
	}
	return (tex);
}

int			setup_textures(t_cub *cub)
{
	if ((cub->tex.south = make_tex(cub, cub->texture.south)) == NULL)
		return (0);
	if ((cub->tex.north = make_tex(cub, cub->texture.north)) == NULL)
		return (0);
	if ((cub->tex.east = make_tex(cub, cub->texture.east)) == NULL)
		return (0);
	if ((cub->tex.west = make_tex(cub, cub->texture.west)) == NULL)
		return (0);
	if ((cub->tex.s = make_tex(cub, cub->texture.s)) == NULL)
		return (0);
	return (1);
}
