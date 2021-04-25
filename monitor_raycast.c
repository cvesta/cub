/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_raycast.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvesta <cvesta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 14:32:20 by cvesta            #+#    #+#             */
/*   Updated: 2021/04/25 17:14:14 by cvesta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	monitor_raycast(t_cub *cub, int a)
{
	count_draw(cub);
	count_wall_pos_t(cub);
	depict_raycast(cub, a);
}

void	count_wall_pos_t(t_cub *cub)
{
	t_image			*tex;

	tex = cub->texs.south;
	if (cub->raycast.side == 1)
		tex = cub->texs.north;
	if (cub->raycast.side == 2)
		tex = cub->texs.east;
	if (cub->raycast.side == 3)
		tex = cub->texs.west;
	cub->raycast.texture_x = (int)(cub->raycast.wall_x * (double)tex->width);
	if (cub->raycast.side == 0 && cub->raycast.raydir_x > 0)
		cub->raycast.texture_x = tex->width - cub->raycast.texture_x - 1;
	if (cub->raycast.side == 1 && cub->raycast.raydir_y < 0)
		cub->raycast.texture_x = tex->width + cub->raycast.texture_x;
	cub->raycast.step = 1.0 * tex->height / cub->raycast.height_line;
	cub->raycast.texpos = (cub->raycast.draw_start - cub->height / 2\
		+ cub->raycast.height_line / 2) * cub->raycast.step;
}

void	count_draw(t_cub *cub)
{
	if (cub->raycast.side == 0 || cub->raycast.side == 1)
		cub->raycast.perpwalldist = (cub->raycast.map_x - cub->raycast.pos_x\
		+ (1 - cub->raycast.step_x) / 2) / cub->raycast.raydir_x;
	else
		cub->raycast.perpwalldist = (cub->raycast.map_y - cub->raycast.pos_y\
		+ (1 - cub->raycast.step_y) / 2) / cub->raycast.raydir_y;
	cub->raycast.height_line = (int)(cub->height / cub->raycast.perpwalldist);
	cub->raycast.draw_start = -cub->raycast.height_line / 2 + cub->height / 2;
	if (cub->raycast.draw_start < 0)
		cub->raycast.draw_start = 0;
	cub->raycast.draw_end = cub->raycast.height_line / 2 + cub->height / 2;
	if (cub->raycast.draw_end >= cub->height)
		cub->raycast.draw_end = cub->height - 1;
	if (cub->raycast.side == 0 || cub->raycast.side == 1)
		cub->raycast.wall_x = cub->raycast.pos_y + cub->raycast.perpwalldist\
		* cub->raycast.raydir_y;
	else
		cub->raycast.wall_x = cub->raycast.pos_x + cub->raycast.perpwalldist\
		* cub->raycast.raydir_x;
	cub->raycast.wall_x -= floor(cub->raycast.wall_x);
}

void	depict_wall(t_cub *cub, int x)
{
	int				y;
	unsigned int	*colour;
	t_image 		*tex;

	tex = cub->texs.south;
	if (cub->raycast.side == 1)
		tex = cub->texs.north;
	if (cub->raycast.side == 2)
		tex = cub->texs.east;
	if (cub->raycast.side == 3)
		tex = cub->texs.west;
	y = cub->raycast.draw_start;
	while (y < cub->raycast.draw_end)
	{
		cub->raycast.texture_y = (int)cub->raycast.texpos & (tex->height - 1);
		if (cub->raycast.side == 1 && cub->raycast.raydir_y < 0)
			cub->raycast.texture_y -= 1;
		cub->raycast.texpos += cub->raycast.step;
		colour = (unsigned int*)(tex->addr + (cub->raycast.texture_y\
		* tex->len_line + cub->raycast.texture_x * (tex->bpp / 8)));
		mlx_pixel_put_(&cub->img, x, y++, (int)*colour);
	}
}

void	depict_raycast(t_cub *cub, int x)
{
	int				down;
	int				up;
	int				y;

	down = cub->down;
	up = cub->up;
	y = 0;
	while (y < cub->raycast.draw_start)
		mlx_pixel_put_(&cub->img, x, y++, up);
	while (y < cub->height)
		mlx_pixel_put_(&cub->img, x, y++, down);
	depict_wall(cub, x);
}


