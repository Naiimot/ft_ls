/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/18 20:33:49 by tdelabro          #+#    #+#             */
/*   Updated: 2019/05/25 21:47:28 by tdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	ft_convert_to_10(char *nbr, const char *base)
{
	int tab[5];

	if ((tab[3] = 1) && (nbr[0] == '-' || nbr[0] == '+'))
	{
		(nbr[0] == '-') ? (tab[3] = -1) : 0;
		nbr++;
	}
	tab[0] = -1;
	while (nbr[++tab[0]])
	{
		tab[1] = -1;
		while (base[++tab[1]])
			if (base[tab[1]] == nbr[tab[0]])
				nbr[tab[0]] = tab[1] + '0';
	}
	tab[4] = tab[1];
	nbr[tab[0]] = '\0';
	tab[2] = 0;
	tab[0] = -1;
	while ((nbr[tab[2]]) && (tab[1] = 0))
		tab[2]++;
	while (nbr[++tab[0]])
		(tab[0] != tab[2]) ? (tab[1] = (tab[1] * tab[4]) + nbr[tab[0]] - '0') :
			(tab[1] = tab[1] + (nbr[tab[0]]) - '0');
	return (tab[1] * tab[3]);
}

static void	ft_rec_conv(char *nbr, const char *base, int n_10, int size_base_to)
{
	static int	i = -1;

	i++;
	if (n_10 == -2147483648)
	{
		nbr[i] = '-';
		nbr[i + 1] = (-2147483648 % size_base_to) + '0';
		i++;
		ft_rec_conv(nbr, base, -(n_10 / size_base_to), size_base_to);
	}
	else if (n_10 < 0)
	{
		nbr[i] = '-';
		ft_rec_conv(nbr, base, -(n_10), size_base_to);
	}
	else if (n_10 >= size_base_to)
	{
		nbr[i] = ((n_10 % size_base_to) + '0');
		ft_rec_conv(nbr, base, n_10 / size_base_to, size_base_to);
	}
	else
		nbr[i] = (n_10 + '0');
	nbr[i + 1] = '\0';
}

static void	ft_trad_nbr(char *nbr, const char *base)
{
	int i;
	int j;
	int boll;

	j = 0;
	while (nbr[j])
	{
		i = 0;
		boll = 0;
		while (base[i])
		{
			if ((nbr[j] - 48) == i && boll == 0)
			{
				nbr[j] = base[i];
				boll = 1;
			}
			i++;
		}
		j++;
	}
}

static void	ft_rev_nbr(char *nbr, const char *base, int size)
{
	int		i;
	char	tmpc;

	i = -1;
	if (nbr[0] == '-')
	{
		i++;
		size++;
	}
	while (++i < size / 2)
	{
		tmpc = nbr[size - 1 - i];
		nbr[size - 1 - i] = nbr[i];
		nbr[i] = tmpc;
	}
	ft_trad_nbr(nbr, base);
}

char		*ft_convert_base(char *nbr, const char *base_from, \
		const char *base_to)
{
	int		size_base_to;
	int		c;
	int		x;
	int		n_10;

	if (!nbr || !base_from || !base_to)
		return (NULL);
	n_10 = ft_convert_to_10(nbr, base_from);
	c = 0;
	(nbr[0] == '-') ? (c = 1) : 0;
	size_base_to = 0;
	while (base_to[size_base_to])
		size_base_to++;
	x = n_10;
	while (x != 0)
	{
		x = x / size_base_to;
		c++;
	}
	if ((nbr = (char*)malloc(sizeof(char) * (c + 1))) == NULL)
		return (NULL);
	ft_rec_conv(nbr, base_to, n_10, size_base_to);
	ft_rev_nbr(nbr, base_to, c);
	return (nbr);
}
