/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/10 14:49:53 by tdelabro          #+#    #+#             */
/*   Updated: 2019/05/25 22:17:16 by tdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	ft_get_start(const char *s)
{
	int	i;

	i = 0;
	while (s[i] && (s[i] == ' ' || s[i] == '\n' || s[i] == '\t'))
		i++;
	if (s[i] == '\0')
		i = 0;
	return (i);
}

static int	ft_get_end(const char *s)
{
	int	i;

	i = 0;
	while (s[i] && (s[i] == ' ' || s[i] == '\n' || s[i] == '\t'))
		i++;
	if (s[i] == '\0')
		i = 0;
	else
	{
		while (s[i])
			i++;
		while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t' || s[i] == '\0')
			i--;
		i++;
	}
	return (i);
}

char		*ft_strtrim(const char *s)
{
	int		i;
	int		start;
	int		end;
	char	*str;

	if (s)
	{
		start = ft_get_start(s);
		end = ft_get_end(s);
		if ((str = (char*)malloc(sizeof(char) * (end - start + 1))) == NULL)
			return (NULL);
		i = -1;
		while (++i + start < end)
			str[i] = s[i + start];
		str[i] = '\0';
		return (str);
	}
	return (NULL);
}
