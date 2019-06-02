/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/11 13:20:17 by tdelabro          #+#    #+#             */
/*   Updated: 2019/05/25 22:03:46 by tdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <limits.h>

static int	ft_get_size(int n)
{
	int	size;

	size = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		size++;
	while (n != 0)
	{
		n = n / 10;
		size++;
	}
	return (size);
}

static void	ft_fill(int n, int size, char *nbr)
{
	int i;

	if (n < 0)
	{
		nbr[0] = '-';
		if (n == INT_MIN)
		{
			nbr[1] = '2';
			n = 147483648;
		}
		else
			n = -1 * n;
	}
	else if (n == 0)
		nbr[0] = 48;
	nbr[size] = '\0';
	i = 0;
	while (n != 0)
	{
		nbr[size - i++ - 1] = (n % 10 + 48);
		n = n / 10;
	}
}

char		*ft_itoa(int n)
{
	char	*nbr;
	int		size;

	size = ft_get_size(n);
	if ((nbr = (char*)malloc(sizeof(char) * (size + 1))) == NULL)
		return (NULL);
	ft_fill(n, size, nbr);
	return (nbr);
}
