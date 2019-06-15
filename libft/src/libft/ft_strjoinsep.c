/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinsep.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 16:21:40 by tdelabro          #+#    #+#             */
/*   Updated: 2019/06/15 16:21:42 by tdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoinsep(const char *s1, const char *s2, char sep)
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
		str[i++] = sep;
		j = -1;
		while (s2[++j])
			str[i + j] = s2[j];
		str[i + j] = '\0';
		return (str);
	}
	return (NULL);
}
