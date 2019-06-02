/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve_ldouble_f.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 16:19:16 by tdelabro          #+#    #+#             */
/*   Updated: 2019/05/25 22:23:07 by tdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../../inc/ft_printf.h"

/*
** Extract, compute and set the value of mantissa and exponent in order to get
** value = valman * 2^valexpo.
*/

static void	ft_init_expmant_ld(long double n, int16_t *valexpo, \
				uint64_t *valmant)
{
	((unsigned char*)valexpo)[0] = ((unsigned char*)&n)[8];
	((unsigned char*)valexpo)[1] = ((unsigned char*)&n)[9];
	*valexpo = *valexpo & 0x7fff;
	((unsigned char*)valmant)[0] = ((unsigned char*)&n)[0];
	((unsigned char*)valmant)[1] = ((unsigned char*)&n)[1];
	((unsigned char*)valmant)[2] = ((unsigned char*)&n)[2];
	((unsigned char*)valmant)[3] = ((unsigned char*)&n)[3];
	((unsigned char*)valmant)[4] = ((unsigned char*)&n)[4];
	((unsigned char*)valmant)[5] = ((unsigned char*)&n)[5];
	((unsigned char*)valmant)[6] = ((unsigned char*)&n)[6];
	((unsigned char*)valmant)[7] = ((unsigned char*)&n)[7];
	*valexpo = (*valexpo == 0) ? *valexpo - 16445 : *valexpo - 16446;
}

/*
** Initialise the two big integer used by the algorithm.
** value = valmant * 2^valexpo
** valnum / valdenum = the first digit of the num.
*/

void		ft_init_numdenum_ld(t_hint *valnum, t_hint *valdenum, \
				long double n, int firstdigitexpo)
{
	int16_t		valexpo;
	uint64_t	valmant;

	ft_hint_settozero(valnum);
	ft_hint_settozero(valdenum);
	ft_init_expmant_ld(n, &valexpo, &valmant);
	if (valexpo > 0)
	{
		(*valnum)[257] = valmant;
		ft_hint_lshift(valnum, valexpo);
		(*valdenum)[257] = 1;
	}
	else
	{
		(*valnum)[257] = valmant;
		(*valdenum)[257] = 1;
		ft_hint_lshift(valdenum, -valexpo);
	}
	if (n > 9 || n < -9)
		ft_pwd_hint(valdenum, 10, firstdigitexpo);
	else
		ft_pwd_hint(valnum, 10, firstdigitexpo);
}

/*
** Each call extract one digit of the float to be printed.
*/

char		ft_getnextdigit_ldbl(t_hint *valnum, t_hint *valdenum)
{
	char	ret;

	ret = ft_div_hint(valnum, valnum, valdenum) + '0';
	ft_mult_hinti(valnum, valnum, 10);
	return (ret);
}

/*
** Twin functions printing functions. The first print float whom absolute value
** is superior to 1, the second the others.
*/

int			ft_getstr_supone_ld(t_hint *valnum, t_hint *valdenum, int *tab,\
														t_format *format)
{
	int		ret;
	int		tmp;
	char	str[tab[1]];

	ret = 0;
	str[ret] = '0';
	while (str[ret] == '0')
	{
		str[ret] = ft_getnextdigit_ldbl(valnum, valdenum);
		(str[ret] == '0') ? tab[0]-- : 1;
		(str[ret] == '0') ? tab[1]-- : 1;
	}
	tmp = ft_pre_printing_float(format, tab[1], tab[2]);
	while (++ret < tab[1])
	{
		if (ret == tab[0] + 1)
			str[ret++] = '.';
		str[ret] = ft_getnextdigit_ldbl(valnum, valdenum);
	}
	ret += ft_round_ld(str, tab[1], valnum, valdenum);
	write(g_fd, str, tab[1]);
	ret = ft_post_printing(ret + tmp, format);
	return (ret);
}

int			ft_getstr_minone_ld(t_hint *valnum, t_hint *valdenum, int *tab,\
														t_format *format)
{
	int		ret;
	int		tmp;
	char	str[tab[1]];

	ret = 0;
	tmp = ft_pre_printing_float(format, tab[1], tab[2]);
	str[ret++] = '0';
	if (format->precision != 0 || format->flag_hash == TRUE)
		str[ret++] = '.';
	while (ret < tab[1] && ret < tab[0] + 1)
		str[ret++] = '0';
	while (ret < tab[1])
		str[ret++] = ft_getnextdigit_ldbl(valnum, valdenum);
	ret += ft_round_ld(str, tab[1], valnum, valdenum);
	write(g_fd, str, tab[1]);
	ret = ft_post_printing(ret + tmp, format);
	return (ret);
}
