/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvesta <cvesta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 14:29:35 by cvesta            #+#    #+#             */
/*   Updated: 2021/04/27 22:28:11 by cvesta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			keep_colour(t_cub *cub, char *str, char **array)
{
	char	*tr;
	char	*tg;
	char	*tb;

	tr = ft_strtrim(array[0], " ");
	tg = ft_strtrim(array[1], " ");
	tb = ft_strtrim(array[2], " ");
	if (!check_colour_max_min(tr) ||
	!check_colour_max_min(tg) ||
	!check_colour_max_min(tb))
		return (0);
	if (ft_strncmp(str, "F", 1) == 0)
		cub->floor = turn_hex(0, ft_atoi(tr), ft_atoi(tg), ft_atoi(tb));
	if (ft_strncmp(str, "C", 1) == 0)
		cub->ceiling = turn_hex(0, ft_atoi(tr), ft_atoi(tg), ft_atoi(tb));
	free(tr);
	free(tg);
	free(tb);
	return (1);
}

int			check_colour_max_min(char *rgb)
{
	int		i;

	i = ft_atoi(rgb);
	if (!(i >= 0 && i <= 255))
	{
		ft_putstr_fd(":(\nwrong color range\n", 1);
		return (0);
	}
	if (ft_strlen(rgb) > 1 && i < 1)
	{
		ft_putstr_fd(":(\ncolor value exceeds maximum int value\n", 1);
		return (0);
	}
	if (ft_strlen(rgb) > 10)
	{
		ft_putstr_fd(":(\ncolor value exceeds maximum int value\n", 1);
		return (0);
	}
	return (1);
}

int			if_color_empty(t_cub *cub, char *str)
{
	if (((ft_strncmp(str, "F", 1) == 0) && (cub->floor != -1)) ||
		((ft_strncmp(str, "C", 1) == 0) && (cub->ceiling != -1)))
	{
		ft_putstr_fd(":(\ncolor is empty\n", 1);
		return (0);
	}
	return (1);
}

int			check_colour(char **array)
{
	int		i;
	char	*str;

	i = 0;
	while (array[i])
	{
		if (!(str = ft_strtrim(array[i++], " ")))
			return (0);
		if (!ft_strlen(str) ||
			!check_number(str) ||
			(str[0] == '0' && ft_strlen(str) > 1))
		{
			ft_putstr_fd(":(\nextension specified incorrectly for color\n", 1);
			free(str);
			return (0);
		}
		free(str);
	}
	if (i != 3)
	{
		ft_putstr_fd(":(\nincorrect number of arguments for color\n", 1);
		return (0);
	}
	return (1);
}

int			parse_colour(t_cub *cub, char *str)
{
	char	**array;
	int		i;
	int		counter;

	i = 0;
	counter = 0;
	while (str[i])
		if (str[i++] == ',')
			counter++;
	if (counter > 2)
	{
		ft_putstr_fd(":(\nincorrect number of arguments for color\n", 1);
		return (0);
	}
	if (!(array = ft_split(str + 1, ',')))
		return (0);
	if (!check_colour(array) || !if_color_empty(cub, str) ||
		!keep_colour(cub, str, array))
	{
		free_array(array);
		return (0);
	}
	free_array(array);
	return (1);
}
