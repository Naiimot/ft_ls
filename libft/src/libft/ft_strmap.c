/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/10 13:39:38 by tdelabro          #+#    #+#             */
/*   Updated: 2019/05/25 21:58:31 by tdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	int		i;
	char	*str;

	if (s && f)
	{
		if ((str = (char*)malloc(sizeof(char) * ft_strlen(s) + 1)) == NULL)
			return (NULL);
		i = -1;
		while (s[++i])
			str[i] = f(s[i]);
		str[i] = '\0';
		return (str);
	}
	return (NULL);
}
