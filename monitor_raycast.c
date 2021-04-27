/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_raycast.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvesta <cvesta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 14:32:20 by cvesta            #+#    #+#             */
/*   Updated: 2021/04/27 21:56:53 by cvesta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void				monitor_raycast(t_cub *win, int x)
{
	count_draw(win);
	count_wall_pos_t(win);
	depict_raycast(win, x);
}

void				count_wall_pos_t(t_cub *win)
{
	t_image			*tex;

	tex = win->tex.south;
	if (win->ray.side == 1)
		tex = win->tex.north;
	if (win->ray.side == 2)
		tex = win->tex.east;
	if (win->ray.side == 3)
		tex = win->tex.west;
	win->ray.x_tex = (int)(win->ray.x_wall * (double)tex->width);
	if (win->ray.side == 0 && win->ray.x_raydir > 0)
		win->ray.x_tex = tex->width - win->ray.x_tex - 1;
	if (win->ray.side == 1 && win->ray.y_raydir < 0)
		win->ray.x_tex = tex->width + win->ray.x_tex;
	win->ray.step = 1.0 * tex->height / win->ray.height_line;
	win->ray.posit_tex = (win->ray.draw_start - win->height / 2\
	+ win->ray.height_line / 2) * win->ray.step;
}

void				count_draw(t_cub *win)
{
	if (win->ray.side == 0 || win->ray.side == 1)
		win->ray.len_ray = (win->ray.x_map - win->ray.x_posit\
		+ (1 - win->ray.x_step) / 2) / win->ray.x_raydir;
	else
		win->ray.len_ray = (win->ray.y_map - win->ray.y_posit\
		+ (1 - win->ray.y_step) / 2) / win->ray.y_raydir;
	win->ray.height_line = (int)(win->height / win->ray.len_ray);
	win->ray.draw_start = -win->ray.height_line / 2 + win->height / 2;
	if (win->ray.draw_start < 0)
		win->ray.draw_start = 0;
	win->ray.draw_end = win->ray.height_line / 2 + win->height / 2;
	if (win->ray.draw_end >= win->height)
		win->ray.draw_end = win->height - 1;
	if (win->ray.side == 0 || win->ray.side == 1)
		win->ray.x_wall = win->ray.y_posit + win->ray.len_ray\
		* win->ray.y_raydir;
	else
		win->ray.x_wall = win->ray.x_posit + win->ray.len_ray\
		* win->ray.x_raydir;
	win->ray.x_wall -= floor(win->ray.x_wall);
}

void				depict_wall(t_cub *win, int x)
{
	int				y;
	unsigned int	*colour;
	t_image			*tex;

	tex = win->tex.south;
	if (win->ray.side == 1)
		tex = win->tex.north;
	if (win->ray.side == 2)
		tex = win->tex.east;
	if (win->ray.side == 3)
		tex = win->tex.west;
	y = win->ray.draw_start;
	while (y < win->ray.draw_end)
	{
		win->ray.y_tex = (int)win->ray.posit_tex & (tex->height - 1);
		if (win->ray.side == 1 && win->ray.y_raydir < 0)
			win->ray.y_tex -= 1;
		win->ray.posit_tex += win->ray.step;
		colour = (unsigned int*)(tex->addr + (win->ray.y_tex\
		* tex->len_line + win->ray.x_tex * (tex->bpp / 8)));
		pxl_put(&win->image, x, y++, (int)*colour);
	}
}

void				depict_raycast(t_cub *win, int x)
{
	int				floor;
	int				ceiling;
	int				y;

	floor = win->floor;
	ceiling = win->ceiling;
	y = 0;
	while (y < win->ray.draw_start)
		pxl_put(&win->image, x, y++, ceiling);
	while (y < win->height)
		pxl_put(&win->image, x, y++, floor);
	depict_wall(win, x);
}
