/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvesta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 15:11:19 by cvesta            #+#    #+#             */
/*   Updated: 2020/11/16 19:41:17 by cvesta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	sizeofstring(int n)
{
	size_t	i;

	i = 0;
	if (n < 0 || n == 0)
		i++;
	while (n)
	{
		i++;
		n = n / 10;
	}
	return (i);
}

static char		*conversion(char *str, int n, size_t length)
{
	if (n < 0)
	{
		str[0] = '-';
		n = -n;
	}
	if (n == 0)
		str[0] = '0';
	str[length--] = '\0';
	while (n)
	{
		str[length] = n % 10 + '0';
		n = n / 10;
		length--;
	}
	return (str);
}

char			*ft_itoa(int n)
{
	char	*res;
	size_t	str_s;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	str_s = sizeofstring(n);
	res = (char *)malloc(sizeof(char) * str_s + 1);
	if (res == NULL)
		return (NULL);
	res = conversion(res, n, str_s);
	return (res);
}
