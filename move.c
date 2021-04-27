/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvesta <cvesta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 22:38:36 by cvesta            #+#    #+#             */
/*   Updated: 2021/04/27 22:18:39 by cvesta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	back(t_cub *win)
{
	if (win->keypress.up == 1)
	{
		if (ft_strchr("0SWEN", win->map[(int)(win->ray.x_posit +\
		win->ray.x_dir * win->ray.mvspeed)][(int)win->ray.y_posit]))
			win->ray.x_posit += win->ray.x_dir * win->ray.mvspeed;
		if (ft_strchr("0SWEN", win->map[(int)(win->ray.x_posit)]\
		[(int)(win->ray.y_posit + win->ray.y_dir * win->ray.mvspeed)]))
			win->ray.y_posit += win->ray.y_dir * win->ray.mvspeed;
	}
	if (win->keypress.down == 1)
	{
		if (ft_strchr("0SWEN", win->map[(int)(win->ray.x_posit -\
		win->ray.x_dir * win->ray.mvspeed)][(int)(win->ray.y_posit)]))
			win->ray.x_posit -= win->ray.x_dir * win->ray.mvspeed;
		if (ft_strchr("0SWEN", win->map[(int)(win->ray.x_posit)]\
		[(int)(win->ray.y_posit - win->ray.y_dir * win->ray.mvspeed)]))
			win->ray.y_posit -= win->ray.y_dir * win->ray.mvspeed;
	}
}

void	sidelong(t_cub *win)
{
	if (win->keypress.left == 1)
	{
		if (ft_strchr("0SWEN", win->map[(int)(win->ray.x_posit)]\
		[(int)(win->ray.y_posit + win->ray.x_dir * win->ray.mvspeed)]))
			win->ray.y_posit -= -win->ray.x_dir * win->ray.mvspeed;
		if (ft_strchr("0SWEN", win->map[(int)(win->ray.x_posit -\
		win->ray.y_dir * win->ray.mvspeed)][(int)(win->ray.y_posit)]))
			win->ray.x_posit -= win->ray.y_dir * win->ray.mvspeed;
	}
	if (win->keypress.right == 1)
	{
		if (ft_strchr("0SWEN", win->map[(int)(win->ray.x_posit)]\
		[(int)(win->ray.y_posit - win->ray.x_dir * win->ray.mvspeed)]))
			win->ray.y_posit += -win->ray.x_dir * win->ray.mvspeed;
		if (ft_strchr("0SWEN", win->map[(int)(win->ray.x_posit +\
		win->ray.y_dir * win->ray.mvspeed)][(int)(win->ray.y_posit)]))
			win->ray.x_posit += win->ray.y_dir * win->ray.mvspeed;
	}
}

void	revolve(t_cub *win, int a)
{
	double	dir_oldx;
	double	flat_old_x;

	dir_oldx = win->ray.x_dir;
	win->ray.x_dir = win->ray.x_dir * cos(a * win->ray.mvspeed)\
			- win->ray.y_dir * sin(a * win->ray.mvspeed);
	win->ray.y_dir = dir_oldx * sin(a * win->ray.mvspeed) + win->ray.y_dir\
			* cos(a * win->ray.mvspeed);
	flat_old_x = win->ray.x_flat;
	win->ray.x_flat = win->ray.x_flat * cos(a * win->ray.mvspeed)\
			- win->ray.y_flat * sin(a * win->ray.mvspeed);
	win->ray.y_flat = flat_old_x * sin(a * win->ray.mvspeed)\
			+ win->ray.y_flat * cos(a * win->ray.mvspeed);
}
