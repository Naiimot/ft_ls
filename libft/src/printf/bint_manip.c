/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bint_manip.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 22:10:41 by tdelabro          #+#    #+#             */
/*   Updated: 2019/02/20 15:01:05 by tdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_printf.h"

/*
** Shift all bits of the t_bint struct on the left
*/

void	ft_lshift(t_bint *map, int shift)
{
	short		i;
	uint64_t	last;
	uint64_t	first;

	while (shift >= 1)
	{
		last = 0;
		first = 0;
		i = 16;
		while (i >= 0)
		{
			first = (*map)[i] & 0x8000000000000000;
			(*map)[i] = ((*map)[i] << 1) | last;
			last = first >> 63;
			i--;
		}
		shift--;
	}
}

/*
** Shift all bits of the t_bint struct on the right
*/

void	ft_rshift(t_bint *map, int shift)
{
	unsigned char	i;
	uint64_t		last;
	uint64_t		first;

	while (shift >= 1)
	{
		last = 0;
		first = 0;
		i = 0;
		while (i < 17)
		{
			last = (*map)[i] & 0x1;
			(*map)[i] = ((*map)[i] >> 1) | first;
			first = last << 63;
			i++;
		}
		shift--;
	}
}

/*
** If the struct have the zero value return FALSE, otherwise TRUE
*/

t_bool	ft_bint_difzero(t_bint const *n)
{
	unsigned char	i;

	i = 0;
	while (i < 17)
	{
		if ((*n)[i++] != 0x0)
			return (TRUE);
	}
	return (FALSE);
}

/*
** Set every bits int the struct to 0
*/

void	ft_bint_settozero(t_bint *n)
{
	unsigned char	i;

	i = 0;
	while (i < 17)
	{
		(*n)[i] = 0x0;
		i++;
	}
}

/*
** Copy a t_bint struct into an other
*/

void	ft_bintcpy(t_bint *dest, t_bint const *src)
{
	unsigned char	i;

	i = 0;
	while (i < 17)
	{
		(*dest)[i] = (*src)[i];
		i++;
	}
}
