/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hint_manip.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 19:41:58 by tdelabro          #+#    #+#             */
/*   Updated: 2019/02/20 15:01:04 by tdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_printf.h"

/*
** Shift all bits of the t_hint struct on the left
*/

void	ft_hint_lshift(t_hint *map, int shift)
{
	short		i;
	uint64_t	last;
	uint64_t	first;

	while (shift >= 1)
	{
		last = 0;
		first = 0;
		i = 257;
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
** Shift all bits of the t_hint struct on the right
*/

void	ft_hint_rshift(t_hint *map, int shift)
{
	short		i;
	uint64_t	last;
	uint64_t	first;

	while (shift >= 1)
	{
		last = 0;
		first = 0;
		i = 0;
		while (i < 258)
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

t_bool	ft_hint_difzero(const t_hint *n)
{
	short	i;

	i = -1;
	while (++i < 258)
	{
		if ((*n)[i] != 0x0)
			return (TRUE);
	}
	return (FALSE);
}

/*
** Set every bits int the struct to 0
*/

void	ft_hint_settozero(t_hint *n)
{
	short	i;

	i = 0;
	while (i < 258)
	{
		(*n)[i] = 0x0;
		i++;
	}
}

/*
** Copy a t_hint struct into an other
*/

void	ft_hintcpy(t_hint *dest, const t_hint *src)
{
	short	i;

	i = 0;
	while (i < 258)
	{
		(*dest)[i] = (*src)[i];
		i++;
	}
}
