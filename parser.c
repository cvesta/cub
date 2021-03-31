/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvesta <cvesta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 15:09:29 by cvesta            #+#    #+#             */
/*   Updated: 2021/03/31 20:04:33 by cvesta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		new_line_map(t_cub *cub, char line)
{
	char	**arr;
	int 	i;

	arr = ft_calloc(cub->sizemapline + 2, sizeof(char *));
	if (!arr)
		return (0);
	i = -1;
	while (++i < cub->sizemapline)
		arr[i] = cub->map[i];
	free(cub->map);
	arr[cub->sizemapline] = ft_strdup(line);
	arr[cub->sizemapline + 1] = NULL;
	cub->sizemapline++;
	cub->map = arr;
	return (1);
}

int		check_line_map(char *str)
{
	int		i;

	i = 0;
	if (str[i] == '\n' || str[i] == '\0')
		return (0);
	while (str[i] && make_space((str[i])))
		i++;
	if (ft_strchr("1", str[i]))
		return (1);
	if (i > 0)
		return (1);
	return (0);
}

int		read_map(int fd, t_cub *cub)
{
	char	*line;
	int		i;

	i = 1;
	while (get_next_line(fd, &line))
	{
		if (!(parse_arg(cub, line)))
		{
			free(line);
			return (0);
		}
		if (check_empty_arg(cub, 0) && check_line_map(line) &&
			!new_line_map(cub, line))
			return (0);
		i++;
		free(line);
	}
	if (check_empty_arg(cub, 0) && check_line_map(line) &&
	!new_line_map(cub, line))
		return (0);
	free(line);
	return (1);
}

int		parser(t_cub *cub, char *map)
{
	int		fd;

	fd = open(file, O_RDONLY);
	if (!read_map(fd, cub) || !check_empty_arg(cub, 1))
		return (0);
	if (fd == -1)
	{
		ft_putstr_fd("error\nno such file or directory\n", 1);
		return (0);
	}
	if (!check_map(cub->map))
	{
		ft_putstr_fd("error\ninvalid map\n", 1);
		return (0);
	}
	return (1);
}