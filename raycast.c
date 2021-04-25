/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvesta <cvesta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 17:58:53 by cvesta            #+#    #+#             */
/*   Updated: 2021/04/24 20:52:49 by cvesta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
		save_to_bmp(win);
		wipe(cub);
		return (0);
	}
	move(cub);
	mlx_put_image_to_window(cub->mlx, cub->cub, cub->img.img, 0, 0);
	return (1);
}

void	img_make(t_cub *cub)
{
	win->img.img = mlx_new_image(win->mlx, win->width, win->height);
	win->img.addr = mlx_get_data_addr(win->img.img, &win->img.bpp,\
			&win->img.line_length, &win->img.endian);
}
