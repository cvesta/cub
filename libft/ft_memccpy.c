/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvesta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 15:08:42 by cvesta            #+#    #+#             */
/*   Updated: 2020/11/06 17:49:42 by cvesta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	char	*a;
	char	*b;
	char	d;
	size_t	i;

	a = (char *)dst;
	b = (char *)src;
	d = (char)c;
	i = 0;
	while (i < n)
	{
		a[i] = b[i];
		if (b[i] == d)
			return (a + i + 1);
		i++;
	}
	return (NULL);
}
