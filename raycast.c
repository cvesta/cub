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