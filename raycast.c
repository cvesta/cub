/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvesta <cvesta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 17:58:53 by cvesta            #+#    #+#             */
/*   Updated: 2021/04/27 22:58:36 by cvesta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			classify_spr(int *order, double *dist, int amount)
{
	int			i;
	int			j;
	int			tmp1;
	double		tmp2;

	i = 0;
	while (i < amount - 1)
	{
		j = 0;
		while (j < amount - i - 1)
		{
			if (dist[j] < dist[j + 1])
			{
				tmp1 = order[j];
				order[j] = order[j + 1];
				order[j + 1] = tmp1;
				tmp2 = dist[j];
				dist[j] = dist[j + 1];
				dist[j + 1] = tmp2;
			}
			j++;
		}
		i++;
	}
}

int				raycast(t_cub *cub)
{
	int			widt_h;
	int			heigh_t;

	if (!(cub->mlx = mlx_init()))
		return (0);
	if (!setup_textures(cub))
	{
		wipe_textures(cub);
		return (0);
	}
	mlx_get_screen_size(cub->mlx, &widt_h, &heigh_t);
	if (cub->width > widt_h)
		cub->width = widt_h;
	if (cub->height > heigh_t)
		cub->height = heigh_t;
	cub->cub = mlx_new_window(cub->mlx, cub->width, cub->height, "cub3D");
	mlx_hook(cub->cub, 17, (1L << 17), wipe, cub);
	mlx_hook(cub->cub, 2, (1L << 0), keypress, cub);
	mlx_hook(cub->cub, 3, (1L << 1), keyrelease, cub);
	mlx_loop_hook(cub->mlx, cycle, cub);
	mlx_loop(cub->mlx);
	return (1);
}

int				cycle(t_cub *cub)
{
	int			x;

	x = 0;
	wipe_image(cub);
	img_make(cub);
	paint_texs(cub);
	if (!monitor_sprites(cub))
	{
		wipe(cub);
		return (0);
	}
	if (cub->save == 1)
	{
		cub->save = 0;
		bmp(cub);
		wipe(cub);
		return (0);
	}
	move(cub);
	mlx_put_image_to_window(cub->mlx, cub->cub, cub->image.image, 0, 0);
	return (1);
}

void			img_make(t_cub *cub)
{
	cub->image.image = mlx_new_image(cub->mlx, cub->width, cub->height);
	cub->image.addr = mlx_get_data_addr(cub->image.image, &cub->image.bpp,\
			&cub->image.len_line, &cub->image.endian);
}

void			paint_texs(t_cub *cub)
{
	int		a;

	a = 0;
	while (a < cub->width)
	{
		setup_raycast(cub, a);
		setup_sided(cub);
		setup_hit(cub);
		monitor_raycast(cub, a);
		cub->ray.zbuffer[a] = cub->ray.len_ray;
		a++;
	}
}
