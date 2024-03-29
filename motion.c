/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   motion.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvesta <cvesta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 17:08:36 by cvesta            #+#    #+#             */
/*   Updated: 2021/04/27 22:11:04 by cvesta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move(t_cub *cub)
{
	if (cub->keypress.up == 1 ||
		cub->keypress.down == 1)
		back(cub);
	if (cub->keypress.left == 1 ||
		cub->keypress.right == 1)
		sidelong(cub);
	if (cub->keypress.lookl == 1)
		revolve(cub, 1);
	if (cub->keypress.lookr == 1)
		revolve(cub, -1);
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
	if (keycode == 123 &&
		cub->keypress.lookl == 1)
		cub->keypress.lookl = 0;
	if (keycode == 124 &&
		cub->keypress.lookr == 1)
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
