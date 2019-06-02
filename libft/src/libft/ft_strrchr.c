/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 14:41:01 by tdelabro          #+#    #+#             */
/*   Updated: 2019/05/25 22:13:10 by tdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	int		pos;

	if (!s)
		return (NULL);
	pos = -1;
	i = 0;
	if ((char)c == '\0')
		return (&((char*)s)[ft_strlen(s)]);
	while (s[i])
	{
		if (s[i] == (char)c)
			pos = i;
		i++;
	}
	if (pos == -1)
		return (NULL);
	else
		return (&((char*)s)[pos]);
}
