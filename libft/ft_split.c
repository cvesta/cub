/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvesta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 15:34:13 by cvesta            #+#    #+#             */
/*   Updated: 2020/11/18 18:39:00 by cvesta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	words_counter(const char *s, char c)
{
	int		i;
	int		ws;

	ws = 0;
	i = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i] != '\0')
			ws++;
		while (s[i] != c && s[i])
			i++;
	}
	return (ws);
}

static int	let_count(const char *s, char c)
{
	int		i;

	i = 0;
	while (s[i] != c && s[i] != '\0')
		i++;
	return (i);
}

static char	**be_free(char **split_w, int wrd)
{
	int		i;

	i = 0;
	while (i < wrd)
	{
		free(split_w[i]);
		i++;
	}
	free(split_w);
	return (split_w);
}

char		**ft_split(char const *s, char c)
{
	char	**split_w;
	int		i;
	int		j;
	int		ws;
	int		wrd;

	if (s == 0)
		return (NULL);
	i = 0;
	wrd = 0;
	ws = words_counter(s, c);
	if ((split_w = malloc((ws + 1) * sizeof(char *))) == NULL)
		return (NULL);
	while (wrd < ws && !(j = 0))
	{
		while (s[i] == c)
			i++;
		if (!(split_w[wrd] = malloc((let_count(&s[i], c) + 1) * sizeof(char))))
			return (be_free(split_w, wrd));
		while (s[i] != '\0' && s[i] != c)
			split_w[wrd][j++] = s[i++];
		split_w[wrd++][j] = '\0';
	}
	split_w[wrd] = NULL;
	return (split_w);
}
