/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvesta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 18:56:36 by cvesta            #+#    #+#             */
/*   Updated: 2020/11/12 17:38:30 by cvesta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	counter1;
	size_t	counter2;
	size_t	results;

	counter1 = 0;
	counter2 = 0;
	results = 0;
	while (dst[counter1])
		counter1++;
	while (src[results])
		results++;
	if (dstsize <= counter1)
		results = results + dstsize;
	else
		results = results + counter1;
	while (src[counter2] && (counter1 + 1) < dstsize)
	{
		dst[counter1] = src[counter2];
		counter1++;
		counter2++;
	}
	dst[counter1] = '\0';
	return (results);
}
