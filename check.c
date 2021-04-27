/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvesta <cvesta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 16:28:30 by cvesta            #+#    #+#             */
/*   Updated: 2021/04/27 21:47:49 by cvesta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			check_argc(int argc, char *map, char *save)
{
	char	*mistake;

	mistake = NULL;
	if (argc == 1)
		mistake = ":(\ntoo few arguments\n";
	if (argc == 2)
	{
		if (ft_strncmp(map + ft_strlen(map) - 4, ".cub", 4) != 0)
			mistake = ":(\nincorrect extension\n";
	}
	if (argc == 3)
	{
		if (ft_strncmp(save, "--save", 6) != 0)
			mistake = ":(\ninvalid value for '--save'\n";
	}
	if (argc > 3)
		mistake = ":(\ntoo many arguments";
	if (mistake)
	{
		ft_putstr_fd(mistake, 1);
		return (0);
	}
	return (1);
}

int			if_arg_empty(t_cub *cub, int check_map)
{
	if ((cub->width == -1) || (cub->height == -1) ||
		(cub->floor == -1) || (cub->ceiling == -1) ||
		(cub->texture.north == NULL) || (cub->texture.south == NULL) ||
		(cub->texture.west == NULL) || (cub->texture.east == NULL) ||
		(cub->texture.s == NULL))
	{
		if (check_map && (cub->map == NULL))
			ft_putstr_fd(":(\ntoo few arguments for map\n", 1);
		return (0);
	}
	return (1);
}

int			check_number(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}
