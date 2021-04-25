/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_sprites.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvesta <cvesta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 15:24:18 by cvesta            #+#    #+#             */
/*   Updated: 2021/04/25 16:04:12 by cvesta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		monitor_sprites(t_cub *cub)
{
	int		*order_sp;
	double	*spritelen;
	int		i;

	if (!(order_sp = malloc(sizeof(int) * (cub->raysprite.numsprites))) ||
		!(spritelen = malloc(sizeof(double) * (cub->raysprite.numsprites))))
		return (0);
	i = 0;
	while (i < cub->raysprite.numsprites)
	{
		order_sp[i] = i;
		spritelen[i] = ((cub->raycast.pos_x - cub->sprite[i].x)\
				* (cub->raycast.pos_x - cub->sprite[i].x) + (cub->raycast.pos_y -\
				cub->sprite[i].y) * (cub->raycast.pos_y - cub->sprite[i].y));
		i++;
	}
	classify_spr(order_sp, spritelen, cub->raysprite.numsprites);
	run_sprites(cub, order_sp);
	if (order_sp)
		free(order_sp);
	if (spritelen)
		free(spritelen);
	return (1);
}

void	count_depict(t_cub *cub, int *order_sp, int i)
{
	cub->raysprite.sprite_x = cub->sprite[order_sp[i]].x - cub->raycast.pos_x;
	cub->raysprite.sprite_y = cub->sprite[order_sp[i]].y - cub->raycast.pos_y;
	cub->raysprite.invdet = 1.0 / (cub->raycast.flat_x * cub->raycast.dir_y -
			cub->raycast.dir_x\
			* cub->raycast.flat_y);
	cub->raysprite.tx = cub->raysprite.invdet * (cub->raycast.dir_y * cub->raysprite.sprite_x\
			- cub->raycast.dir_x * cub->raysprite.sprite_y);
	cub->raysprite.ty = cub->raysprite.invdet * (-cub->raycast.flat_y * cub->raysprite.sprite_x\
			+ cub->raycast.flat_x * cub->raysprite.sprite_y);
	cub->raysprite.screen_x = (int)((cub->width / 2) * (1 +\
				cub->raysprite.tx / cub->raysprite.ty));
	cub->raysprite.height = abs((int)(cub->height / (cub->raysprite.ty)));
	cub->raysprite.start_y = -cub->raysprite.height / 2 + cub->height / 2;
	if (cub->raysprite.start_y < 0)
		cub->raysprite.start_y = 0;
	cub->raysprite.end_y = cub->raysprite.height / 2 + cub->height / 2;
	if (cub->raysprite.end_y >= cub->height)
		cub->raysprite.end_y = cub->height - 1;
	cub->raysprite.width = abs((int)(cub->height\
				/ (cub->raysprite.ty)));
	cub->raysprite.start_x = -cub->raysprite.width / 2 + cub->raysprite.screen_x;
	if (cub->raysprite.start_x < 0)
		cub->raysprite.start_x = 0;
	cub->raysprite.end_x = cub->raysprite.width / 2 + cub->raysprite.screen_x;
	if (cub->raysprite.end_x >= cub->width)
		cub->raysprite.end_x = cub->width - 1;
}


void	paint_sprites(t_cub *cub)
{
	int		band;
	t_image *tex;
	int		y;

	tex = cub->texs.sprite;
	band = cub->raysprite.start_x;
	while (band < cub->raysprite.end_x)
	{
		cub->raysprite.tex_x = (int)(256 * (band - (-cub->raysprite.width / 2\
						+ cub->raysprite.screen_x)) * tex->width\
				/ cub->raysprite.width) / 256;
		if (cub->raysprite.ty > 0 && band > 0 && band < cub->width
			&& cub->raysprite.ty < cub->raycast.zbuffer[band])
		{
			y = cub->raysprite.start_y;
			while (y < cub->raysprite.end_y)
			{
				depict_sprite(cub, y, tex, band);
				y++;
			}
		}
		band++;
	}
}

void	depict_sprite(t_cub *cub, int y, t_image *tex, int band)
{
	int				d;
	unsigned int	*colour;

	d = (y) * 256 - cub->height * 128 + cub->raysprite.height * 128;
	cub->raysprite.tex_y = ((d * tex->height) / cub->raysprite.height) / 256;
	colour = (unsigned int*)(tex->addr + (cub->raysprite.tex_y *\
				tex->len_line + cub->raysprite.tex_x * (tex->bpp / 8)));
	if (((int)*colour & (0xFF << 24)) >= 0)
		mlx_pixel_put_(&cub->img, band, y, (int)*colour);
}

void	 run_sprites(t_cub *cub, int *order_sp)
{
	int		i;

	i = 0;
	while (i < cub->raysprite.numsprites)
	{
		count_depict(cub, order_sp, i);
		paint_sprites(cub);
		i++;
	}
}

