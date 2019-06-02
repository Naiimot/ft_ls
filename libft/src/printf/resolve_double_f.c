/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve_double_f.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 16:18:50 by tdelabro          #+#    #+#             */
/*   Updated: 2019/05/25 22:22:40 by tdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../../inc/ft_printf.h"

/*
** Compute the power of 10 value of the first number's digit.
*/

int		ft_getfirstdigit_d(double n)
{
	int	firstdigitexpo;

	firstdigitexpo = 0;
	if (n > 9)
		while (n > 9)
		{
			n = n / 10;
			firstdigitexpo++;
		}
	else if (n < 1)
		while (n < 1)
		{
			n = n * 10;
			firstdigitexpo++;
		}
	else
		firstdigitexpo = 0;
	return (firstdigitexpo);
}

/*
** Initialise the two big integer used by the algorithm.
** value = valmant * 2^valexpo
** valnum / valdenum = the first digit of the num.
*/

void	ft_init_numdenum_d(t_bint *valnum, t_bint *valdenum,\
		double n, int firstdigitexpo)
{
	int16_t		valexpo;
	uint64_t	valmant;

	ft_bint_settozero(valnum);
	ft_bint_settozero(valdenum);
	valexpo = (0x7FF0000000000000 & *(uint64_t*)&n) >> 52;
	valmant = (valexpo == 0) ? 0xFFFFFFFFFFFFF & *(uint64_t*)&n :\
				(0xFFFFFFFFFFFFF & *(uint64_t*)&n) + ft_pwd_uint64(2, 52);
	valexpo = (valexpo == 0) ? -1074 : valexpo - 1075;
	if (valexpo > 0)
	{
		(*valnum)[16] = valmant;
		ft_lshift(valnum, valexpo);
		(*valdenum)[16] = 1;
	}
	else
	{
		(*valnum)[16] = valmant;
		(*valdenum)[16] = 1;
		ft_lshift(valdenum, -valexpo);
	}
	if (n > 9 || n < -9)
		ft_pwd_bint(valdenum, 10, firstdigitexpo);
	else
		ft_pwd_bint(valnum, 10, firstdigitexpo);
}

/*
** Each call extract one digit of the float to be printed.
*/

char	ft_getnextdigit_dbl(t_bint *valnum, t_bint *valdenum)
{
	char	ret;

	ret = ft_div_bint(valnum, valnum, valdenum) + '0';
	ft_mult_binti(valnum, valnum, 10);
	return (ret);
}

/*
** Twin functions printing functions. The first print float whom absolute value
** is superior to 1, the second the others.
*/

int		ft_getstr_supone_d(t_bint *valnum, t_bint *valdenum,\
		int *tab, t_format *format)
{
	int				ret;
	int				tmp;
	char			str[tab[1]];

	ret = 0;
	str[ret] = '0';
	while (str[ret] == '0')
	{
		str[ret] = ft_getnextdigit_dbl(valnum, valdenum);
		(str[ret] == '0') ? tab[0]-- : 1;
		(str[ret] == '0') ? tab[1]-- : 1;
	}
	tmp = ft_pre_printing_float(format, tab[1], tab[2]);
	while (++ret < tab[1])
	{
		if (ret == tab[0] + 1)
			str[ret++] = '.';
		str[ret] = ft_getnextdigit_dbl(valnum, valdenum);
	}
	ret += ft_round(str, tab[1], valnum, valdenum);
	write(g_fd, str, ret);
	ret = ft_post_printing(ret + tmp, format);
	return (ret);
}

int		ft_getstr_minone_d(t_bint *valnum, t_bint *valdenum,\
		int *tab, t_format *format)
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
		str[ret++] = ft_getnextdigit_dbl(valnum, valdenum);
	ret += ft_round(str, tab[1], valnum, valdenum);
	write(g_fd, str, tab[1]);
	ret = ft_post_printing(ret + tmp, format);
	return (ret);
}
