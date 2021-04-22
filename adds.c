/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvesta <cvesta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 18:04:11 by cvesta            #+#    #+#             */
/*   Updated: 2021/04/22 19:02:38 by cvesta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		make_space(char c)
{
	return (c == ' ');
}

void	clear_arr(char **arr)
{
	int 	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

void	clear(t_cub *cub)
{
	char	**map;

	map = cub->map;
	if (map)
		clear_arr(map);
	free(cub->textures.north);
	free(cub->textures.south)
	free(cub->textures.west)
	free(cub->textures.east)
	free(cub->textures.sprite)
}

int		turn_hex(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int 	wipe(t_cub *cub)
{
	clear(cub);
	wipe_image(cub);

}
