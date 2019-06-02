/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/10 14:42:19 by tdelabro          #+#    #+#             */
/*   Updated: 2019/05/25 22:32:17 by tdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	int		i;
	int		j;
	char	*str;

	if (s1 && s2)
	{
		if ((str = (char*)malloc(sizeof(char) * \
						(ft_strlen(s1) + ft_strlen(s2) + 1))) == NULL)
			return (NULL);
		i = -1;
		while (s1[++i])
			str[i] = s1[i];
		j = -1;
		while (s2[++j])
			str[i + j] = s2[j];
		str[i + j] = '\0';
		return (str);
	}
	return (NULL);
}
