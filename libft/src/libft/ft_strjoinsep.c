/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinsep.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 21:39:17 by tdelabro          #+#    #+#             */
/*   Updated: 2019/05/27 21:42:34 by tdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoinsep(const char *s1, const char *s2, const char c)
{
	int		i;
	int		j;
	char	*str;

	if (s1 && s2)
	{
		if ((str = (char*)malloc(sizeof(char) * \
						(ft_strlen(s1) + ft_strlen(s2) + 2))) == NULL)
			return (NULL);
		i = -1;
		while (s1[++i])
			str[i] = s1[i];
		str[i++] = c;
		j = -1;
		while (s2[++j])
			str[i + j] = s2[j];
		str[i + j] = '\0';
		return (str);
	}
	return (NULL);
}
