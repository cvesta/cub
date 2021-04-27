/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvesta <cvesta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 18:04:11 by cvesta            #+#    #+#             */
/*   Updated: 2021/04/27 21:33:37 by cvesta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		make_space(char c)
{
	return (c == ' ');
}

void	free_array(char **array)
{
	int		i;

	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
}

void	free_all(t_cub *cub)
{
	char	**map;

	map = cub->map;
	if (map)
		free_array(map);
	free(cub->texture.north);
	free(cub->texture.south);
	free(cub->texture.west);
	free(cub->texture.east);
	free(cub->texture.s);
}

int		turn_hex(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int		wipe(t_cub *cub)
{
	free_all(cub);
	wipe_image(cub);
	wipe_textures(cub);
	mlx_destroy_window(cub->mlx, cub->cub);
	if (cub->ray.zbuffer)
		free(cub->ray.zbuffer);
	ft_putstr_fd("the end!", 1);
	exit(0);
	return (1);
}
