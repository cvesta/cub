/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_raycast.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvesta <cvesta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 22:29:02 by cvesta            #+#    #+#             */
/*   Updated: 2021/04/24 22:38:54 by cvesta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		move(t_cub *cub)
{
	if (cub->keypress.up == 1 || cub->keypress.down == 1)
		backforth(win);
	if (win->keydown.left == 1 || win->keydown.right == 1)
		sideways(win);
	if (win->keydown.lookleft == 1)
		rotate(win, 1);
	if (win->keydown.lookright == 1)
		rotate(win, -1);
}

int		keyrelease(int keycode, t_cub *cub)
{
	if (keycode == 13 && cub->keypress.up == 1)
		cub->keypress.up = 0;
	if (keycode == 1 && cub->keypress.down == 1)
		cub->keypress.down = 0;
	if (keycode == 0 && cub->keypress.left == 1)
		cub->keypress.left = 0;
	if (keycode == 2 && cub->keypress.right == 1)
		cub->keypress.right = 0;
	if (keycode == 123 && cub->keypress.lookl == 1)
		cub->keypress.lookl = 0;
	if (keycode == 124 && cub->keypress.lookr == 1)
		cub->keypress.lookr = 0;
	return (1);
}

int		keypress(int keycode, t_cub *cub)
{
	if (keycode == 13)
		cub->keypress.up = 1;
	if (keycode == 1)
		cub->keypress.down = 1;
	if (keycode == 0)
		cub->keypress.left = 1;
	if (keycode == 2)
		cub->keypress.right = 1;
	if (keycode == 123)
		cub->keypress.lookl = 1;
	if (keycode == 124)
		cub->keypress.lookr = 1;
	if (keycode == 53)
		wipe(cub);
	return (1);
}