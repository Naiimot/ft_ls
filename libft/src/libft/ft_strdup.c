/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 13:14:00 by tdelabro          #+#    #+#             */
/*   Updated: 2019/05/25 22:20:52 by tdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strdup(const char *s1)
{
	char	*cpy;
	int		i;

	i = 0;
	if (s1)
	{
		while (s1[i])
			i++;
		if ((cpy = (char*)malloc(sizeof(char) * (i + 1))) == NULL)
			return (NULL);
		i = 0;
		while (s1[i])
		{
			cpy[i] = s1[i];
			i++;
		}
		cpy[i] = '\0';
		return (cpy);
	}
	return (NULL);
}
