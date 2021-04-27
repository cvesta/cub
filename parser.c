/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvesta <cvesta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 15:09:29 by cvesta            #+#    #+#             */
/*   Updated: 2021/04/27 22:21:47 by cvesta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int				insert_line_to_map(t_cub *cub, char *line)
{
	char		**array;
	int			i;

	array = ft_calloc(cub->line_size + 2, sizeof(char *));
	if (!array)
		return (0);
	i = -1;
	while (++i < cub->line_size)
		array[i] = cub->map[i];
	free(cub->map);
	array[cub->line_size] = ft_strdup(line);
	array[cub->line_size + 1] = NULL;
	cub->line_size++;
	cub->map = array;
	return (1);
}

int				check_line_map(char *str)
{
	int			i;

	i = 0;
	if (str[i] == '\n' || str[i] == '\0')
		return (0);
	while (str[i] && make_space(str[i]))
		i++;
	if (ft_strchr("1", str[i]))
		return (1);
	if (i > 0)
		return (1);
	return (0);
}

int				read_map(int fd, t_cub *cub)
{
	char		*line;
	int			a;

	a = 1;
	while (get_next_line(fd, &line))
	{
		if (!(parse_arg(cub, line)))
		{
			free(line);
			return (0);
		}
		if (if_arg_empty(cub, 0) && check_line_map(line) &&
			!insert_line_to_map(cub, line))
			return (0);
		a++;
		free(line);
	}
	if (if_arg_empty(cub, 0) && check_line_map(line) &&
		!insert_line_to_map(cub, line))
		return (0);
	free(line);
	return (1);
}

int				parser(t_cub *cub, char *map)
{
	int			fd;

	fd = open(map, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd(":(\nno such file or dir\n", 1);
		return (0);
	}
	if (!read_map(fd, cub) || !if_arg_empty(cub, 1))
		return (0);
	if (!check_map(cub->map))
	{
		ft_putstr_fd(":(\ninvalid map\n", 1);
		return (0);
	}
	return (1);
}
