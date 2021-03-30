/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvesta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 22:42:18 by cvesta            #+#    #+#             */
/*   Updated: 2021/01/11 19:29:37 by cvesta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

size_t	ft_strlen(const char *str)
{
	size_t			counter;

	counter = 0;
	while (str[counter])
		counter++;
	return (counter);
}

char	*ft_strdup(const char *s1)
{
	char			*dup;
	int				length;
	int				ind;

	length = 0;
	ind = 0;
	while (s1[length] != '\0')
		length++;
	dup = (char*)malloc(sizeof(*s1) * (length + 1));
	if (!dup)
		return (NULL);
	while (s1[ind] != '\0')
	{
		dup[ind] = s1[ind];
		ind++;
	}
	dup[ind] = '\0';
	return (dup);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	unsigned int	cont;
	char			*s_res;

	cont = ft_strlen(s1) + ft_strlen(s2);
	s_res = ((char *)malloc(sizeof(char) * (cont + 1)));
	if (!s_res)
		return (NULL);
	while (*s1 != '\0')
		*s_res++ = *s1++;
	while (*s2 != '\0')
		*s_res++ = *s2++;
	*s_res++ = '\0';
	return (s_res - (cont + 1));
}

char	*ft_strcpy(char *dest, char *src)
{
	int				a;

	a = 0;
	while (src[a] != '\0')
	{
		dest[a] = src[a];
		a++;
	}
	dest[a] = '\0';
	return (dest);
}

char	*ft_strchr(const char *s, int c)
{
	char *s1;

	s1 = (char *)s;
	while (*s1 != '\0' && *s1 != (char)c)
		s1++;
	if (*s1 != (char)c)
		return (NULL);
	else
		return (s1);
}
