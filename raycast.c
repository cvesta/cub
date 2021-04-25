/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvesta <cvesta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 17:58:53 by cvesta            #+#    #+#             */
/*   Updated: 2021/04/25 17:27:23 by cvesta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	classify_spr(int *order, double  *len, int num)
{
	int		i;
	int		j;
	int		tmp1;
	double	tmp2;

	i = 0;
	while (i < num - 1)
	{
		j = 0;
		while (j < num - i - 1)
		{
			if (len[j] < len[j + 1])
			{
				tmp1 = order[j];
				order[j] = order[j + 1];
				order[j + 1] = tmp1;
				tmp2 = len[j];
				len[j] = len[j + 1];
				len[j + 1] = tmp2;
			}
			j++;
		}
		i++;
	}
}

int		raycast(t_cub *cub)
{
	int		widt_h;
	int 	heigh_t;

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
	mlx_loop_hook(cub->mlx, loop, cub);
	mlx_loop(cub->mlx);
	return (1);
}

int		loop(t_cub *cub)
{
	int		a;

	a = 0;
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
		save_to_bmp(cub);
		wipe(cub);
		return (0);
	}
	move(cub);
	mlx_put_image_to_window(cub->mlx, cub->cub, cub->img.img, 0, 0);
	return (1);
}

void	img_make(t_cub *cub)
{
	cub->img.img = mlx_new_image(cub->mlx, cub->width, cub->height);
	cub->img.addr = mlx_get_data_addr(cub->img.img, &cub->img.bpp,\
			&cub->img.len_line, &cub->img.endian);
}

void	paint_texs(t_cub *cub)
{
	int		a;

	a = 0;
	while (a < cub->width)
	{
		setup_raycast(cub, a);
		setup_sided(cub);
		setup_hit(cub);
		monitor_raycast(cub, a);
		cub->raycast.zbuffer[a] = cub->raycast.perpwalldist;
		a++;
	}
}