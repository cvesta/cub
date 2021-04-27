/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvesta <cvesta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 14:31:07 by cvesta            #+#    #+#             */
/*   Updated: 2021/04/27 22:24:18 by cvesta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			parse_r(t_cub *cub, char *str)
{
	char	**array;
	int		width;
	int		height;

	if (!(array = ft_split(str, ' ')))
		return (0);
	if (!check_res(array))
	{
		free_array(array);
		return (0);
	}
	width = ft_atoi(array[0]);
	height = ft_atoi(array[1]);
	if (!if_res_empty(width, height, cub) ||
		!check_max_res(width, height, array))
	{
		free_array(array);
		return (0);
	}
	cub->width = width;
	cub->height = height;
	free_array(array);
	return (1);
}

int			check_res(char **array)
{
	int		a;

	a = 0;
	while (array[a])
	{
		if (!check_number(array[a]) ||
			(ft_strlen(array[a]) > 1 && array[a][0] == '0'))
		{
			ft_putstr_fd(":(\next is incorrect for R\n", 1);
			return (0);
		}
		a++;
	}
	if (a != 2)
	{
		ft_putstr_fd(":(\nincorrect number of arguments for res", 1);
		return (0);
	}
	return (1);
}

int			if_res_empty(int width, int height, t_cub *cub)
{
	if (width <= 0 || height <= 0)
	{
		ft_putstr_fd(":(\next is incorrect for R\n", 1);
		return (0);
	}
	if (cub->width != -1 || cub->height != -1)
	{
		ft_putstr_fd(":(\nres is empty\n", 1);
		return (0);
	}
	return (1);
}

int			check_max_res(int width, int height, char **array)
{
	if ((ft_strlen(array[0]) > 10 || ft_strlen(array[1]) > 10) ||
		(ft_strlen(array[0]) > 1 && width < 1) ||
		(ft_strlen(array[1]) > 1 && height < 1))
	{
		ft_putstr_fd("error\nmax int excess\n", 1);
		return (0);
	}
	return (1);
}
