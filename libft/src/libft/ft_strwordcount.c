/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strwordcount.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 14:45:59 by tdelabro          #+#    #+#             */
/*   Updated: 2019/05/25 22:29:39 by tdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_strwordcount(const char *s, char c)
{
	int i;
	int	bol;
	int	count_word;

	i = 0;
	bol = 0;
	count_word = 0;
	if (!s || !s[i])
		return (0);
	while (s[i])
	{
		if (s[i] != c && bol == 0)
			bol = 1;
		if ((s[i] == c || s[i] == '\0') && bol == 1)
		{
			count_word++;
			bol = 0;
		}
		i++;
	}
	if (s[i - 1] != c)
		count_word++;
	return (count_word);
}
