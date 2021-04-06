/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvesta <cvesta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 18:04:11 by cvesta            #+#    #+#             */
/*   Updated: 2021/03/30 18:04:11 by cvesta           ###   ########.fr       */
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

int		turn_hex(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}