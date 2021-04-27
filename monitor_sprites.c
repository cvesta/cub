/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_sprites.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvesta <cvesta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 15:24:18 by cvesta            #+#    #+#             */
/*   Updated: 2021/04/27 23:01:51 by cvesta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int					monitor_sprites(t_cub *cub)
{
	int				*order_sp;
	double			*spritelen;
	int				i;

	if (!(order_sp = malloc(sizeof(int) * (cub->rsp.numsprites))) ||
		!(spritelen = malloc(sizeof(double) * (cub->rsp.numsprites))))
		return (0);
	i = 0;
	while (i < cub->rsp.numsprites)
	{
		order_sp[i] = i;
		spritelen[i] = ((cub->ray.x_posit - cub->sprite[i].x)\
		* (cub->ray.x_posit - cub->sprite[i].x) + (cub->ray.y_posit -\
		cub->sprite[i].y) * (cub->ray.y_posit - cub->sprite[i].y));
		i++;
	}
	classify_spr(order_sp, spritelen, cub->rsp.numsprites);
	run_sprites(cub, order_sp);
	if (order_sp)
		free(order_sp);
	if (spritelen)
		free(spritelen);
	return (1);
}

void				count_depict(t_cub *cub, int *order_sp, int i)
{
	cub->rsp.x_sprite = cub->sprite[order_sp[i]].x - cub->ray.x_posit;
	cub->rsp.y_sprite = cub->sprite[order_sp[i]].y - cub->ray.y_posit;
	cub->rsp.invdet = 1.0 / (cub->ray.x_flat * cub->ray.y_dir - cub->ray.x_dir\
			* cub->ray.y_flat);
	cub->rsp.tx = cub->rsp.invdet * (cub->ray.y_dir * cub->rsp.x_sprite \
			- cub->ray.x_dir * cub->rsp.y_sprite);
	cub->rsp.ty = cub->rsp.invdet * (-cub->ray.y_flat * cub->rsp.x_sprite\
			+ cub->ray.x_flat * cub->rsp.y_sprite);
	cub->rsp.x_screen = (int)((cub->width / 2) * (1 +\
			cub->rsp.tx / cub->rsp.ty));
	cub->rsp.height = abs((int)(cub->height / (cub->rsp.ty)));
	cub->rsp.y_start = -cub->rsp.height / 2 + cub->height / 2;
	if (cub->rsp.y_start < 0)
		cub->rsp.y_start = 0;
	cub->rsp.y_end = cub->rsp.height / 2 + cub->height / 2;
	if (cub->rsp.y_end >= cub->height)
		cub->rsp.y_end = cub->height - 1;
	cub->rsp.width = abs((int)(cub->height\
	/ (cub->rsp.ty)));
	cub->rsp.x_start = -cub->rsp.width / 2 + cub->rsp.x_screen;
	if (cub->rsp.x_start < 0)
		cub->rsp.x_start = 0;
	cub->rsp.x_end = cub->rsp.width / 2 + cub->rsp.x_screen;
	if (cub->rsp.x_end >= cub->width)
		cub->rsp.x_end = cub->width - 1;
}

void				paint_sprites(t_cub *cub)
{
	int		band;
	t_image	*tex;
	int		y;

	tex = cub->tex.s;
	band = cub->rsp.x_start;
	while (band < cub->rsp.x_end)
	{
		cub->rsp.x_tex = (int)(256 * (band - (-cub->rsp.width / 2\
		+ cub->rsp.x_screen)) * tex->width\
		/ cub->rsp.width) / 256;
		if (cub->rsp.ty > 0 && band > 0 && band < cub->width
			&& cub->rsp.ty < cub->ray.zbuffer[band])
		{
			y = cub->rsp.y_start;
			while (y < cub->rsp.y_end)
			{
				depict_sprite(cub, y, tex, band);
				y++;
			}
		}
		band++;
	}
}

void				depict_sprite(t_cub *cub, int y, t_image *tex, int band)
{
	int				a;
	unsigned int	*colour;

	a = (y) * 256 - cub->height * 128 + cub->rsp.height * 128;
	cub->rsp.y_tex = ((a * tex->height) / cub->rsp.height) / 256;
	colour = (unsigned int*)(tex->addr + (cub->rsp.y_tex *\
	tex->len_line + cub->rsp.x_tex * (tex->bpp / 8)));
	if (((int)*colour & (0xFF << 24)) >= 0)
		pxl_put(&cub->image, band, y, (int)*colour);
}

void				run_sprites(t_cub *cub, int *order_sp)
{
	int				i;

	i = 0;
	while (i < cub->rsp.numsprites)
	{
		count_depict(cub, order_sp, i);
		paint_sprites(cub);
		i++;
	}
}
