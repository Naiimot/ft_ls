/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/11 10:44:10 by tdelabro          #+#    #+#             */
/*   Updated: 2019/05/25 22:13:45 by tdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		ft_size_word(const char *s, char c, int pos)
{
	int i;

	i = 0;
	while (s[pos + i] && s[pos + i] != c)
		i++;
	return (i);
}

char			**ft_strsplit(const char *s, char c)
{
	int		i;
	int		j;
	int		k;
	char	**tab;

	if (!s || !c || (tab = (char**)malloc(sizeof(char*) \
					* (ft_strwordcount(s, c) + 1))) == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && !(k = 0))
		{
			if (!(tab[j] = (char*)malloc(sizeof(char) \
							* (ft_size_word(s, c, i) + 1))))
				return (NULL);
			while (s[i] != c && s[i])
				tab[j][k++] = s[i++];
			tab[j++][k] = '\0';
		}
	}
	return (tab[j] = 0) ? NULL : tab;
}
