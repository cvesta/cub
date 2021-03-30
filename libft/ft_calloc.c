/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvesta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 18:19:59 by cvesta            #+#    #+#             */
/*   Updated: 2020/11/12 18:43:08 by cvesta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void *massiv;

	if (!(massiv = (char *)malloc(size * count)))
		return (NULL);
	ft_bzero(massiv, size * count);
	return (massiv);
}
