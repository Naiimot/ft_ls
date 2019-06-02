/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hint_opedown.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 19:52:52 by tdelabro          #+#    #+#             */
/*   Updated: 2019/02/20 15:11:08 by tdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_printf.h"

/*
** Store in 'result' the result of the substraction of 'n' and 'm'
*/

void	ft_sub_hint(t_hint *result, t_hint *n, t_hint *m)
{
	t_hint			tmpn;
	t_hint			tmpm;
	t_hint			borrow;
	short			i;

	ft_hintcpy(&tmpn, n);
	ft_hintcpy(&tmpm, m);
	while (ft_hint_difzero(&tmpm))
	{
		i = -1;
		while (++i < 258)
			borrow[i] = (~(tmpn[i])) & tmpm[i];
		i = -1;
		while (++i < 258)
			tmpn[i] = tmpn[i] ^ tmpm[i];
		ft_hintcpy(&tmpm, &borrow);
		ft_hint_lshift(&tmpm, 1);
	}
	ft_hintcpy(result, &tmpn);
}

/*
** Return 1, -1 or 0 depends on n being greater, smaller or equal to m
*/

char	ft_hintcmp(t_hint *n, t_hint *m)
{
	short	i;

	i = 0;
	while (i < 257 && (*n)[i] == (*m)[i])
		i++;
	if ((*n)[i] > (*m)[i])
		return (1);
	else if ((*n)[i] < (*m)[i])
		return (-1);
	else
		return (0);
}

/*
** Return the result of the euclidian division of 'dividend' by 'divisor'
** Remainer is kept in the 'remainer' arg
** Only work if 0 =< quotient =< 9
*/

char	ft_div_hint(t_hint *remainer, const t_hint *dividend,\
										const t_hint *divisor)
{
	unsigned char	quotient;
	t_hint			divid;
	t_hint			divis;

	quotient = 1;
	ft_hintcpy(&divid, dividend);
	ft_hintcpy(&divis, divisor);
	if (ft_hintcmp(&divid, &divis) == 0)
	{
		ft_hint_settozero(remainer);
		return (1);
	}
	else if (ft_hintcmp(&divid, &divis) == -1)
	{
		ft_hintcpy(remainer, &divid);
		return (0);
	}
	while (ft_hintcmp(&divid, &divis) == 1 && (quotient <<= 1))
		ft_hint_lshift(&divis, 1);
	if (ft_hintcmp(&divid, &divis) == -1 && (quotient >>= 1))
		ft_hint_rshift(&divis, 1);
	ft_sub_hint(&divid, &divid, &divis);
	return (quotient + ft_div_hint(remainer, &divid, divisor));
}
