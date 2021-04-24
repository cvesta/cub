/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvesta <cvesta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 19:04:00 by cvesta            #+#    #+#             */
/*   Updated: 2021/04/08 19:07:10 by cvesta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		main(int argc, char **argv)
{
	t_cub cub;

	if (!check_argc(argc, argv[1], argv[2]))
		return (0);
	setup_arg(&cub);
	if (argc == 3)
		cub.save = 1;
	if (!parser(&cub, argv[1]))
	{
		clear(&cub);
		return (0);
	}
	if (!setup_player(&cub) || !setup_sprite(&cub) || !raycast(&cub))
	{
		ft_putstr_fd("error\nsetting up error\n", 1);
		clear(&cub);
		return (0);
	}
	clear(&cub);
	return (1);
}