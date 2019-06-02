/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bint_opedown.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 14:43:35 by tdelabro          #+#    #+#             */
/*   Updated: 2019/02/20 15:11:05 by tdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_printf.h"

/*
** Store in 'result' the result of the substraction of 'n' and 'm'
*/

void			ft_sub_bint(t_bint *result, t_bint *n, t_bint *m)
{
	t_bint			tmpn;
	t_bint			tmpm;
	t_bint			borrow;
	unsigned char	i;

	ft_bintcpy(&tmpn, n);
	ft_bintcpy(&tmpm, m);
	while (ft_bint_difzero(&tmpm))
	{
		i = 0;
		while (i < 17)
		{
			borrow[i] = (~(tmpn[i])) & tmpm[i];
			i++;
		}
		i = 0;
		while (i < 17)
		{
			tmpn[i] = tmpn[i] ^ tmpm[i];
			i++;
		}
		ft_bintcpy(&tmpm, &borrow);
		ft_lshift(&tmpm, 1);
	}
	ft_bintcpy(result, &tmpn);
}

/*
** Return 1, -1 or 0 depends on n being greater, smaller or equal to m
*/

char			ft_bintcmp(t_bint *n, t_bint *m)
{
	unsigned char	i;

	i = 0;
	while (i < 16 && (*n)[i] == (*m)[i])
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

unsigned char	ft_div_bint(t_bint *remainer, const t_bint *dividend,\
												const t_bint *divisor)
{
	unsigned char	quotient;
	t_bint			divid;
	t_bint			divis;

	quotient = 1;
	ft_bintcpy(&divid, dividend);
	ft_bintcpy(&divis, divisor);
	if (ft_bintcmp(&divid, &divis) == 0)
	{
		ft_bint_settozero(remainer);
		return (1);
	}
	else if (ft_bintcmp(&divid, &divis) == -1)
	{
		ft_bintcpy(remainer, &divid);
		return (0);
	}
	while (ft_bintcmp(&divid, &divis) == 1 && (quotient <<= 1))
		ft_lshift(&divis, 1);
	if (ft_bintcmp(&divid, &divis) == -1 && (quotient >>= 1))
		ft_rshift(&divis, 1);
	ft_sub_bint(&divid, &divid, &divis);
	return (quotient + ft_div_bint(remainer, &divid, divisor));
}
