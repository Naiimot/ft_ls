/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_float.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 17:34:29 by tdelabro          #+#    #+#             */
/*   Updated: 2019/05/25 22:27:08 by tdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "../../inc/ft_printf.h"

/*
** Printing of nan is hadled apart because it's not influenced by precision or
** flags.
*/

static int	ft_nan(char *buff, t_format *format)
{
	int ret;

	ret = 0;
	if (FFLEFT == FALSE)
		while (FWIDTH > 3 && ret < format->field_width - 3)
			ret += ft_buff(buff, ' ', 0);
	ret += ft_buff(buff, 'n', 0);
	ret += ft_buff(buff, 'a', 0);
	ret += ft_buff(buff, 'n', 0);
	if (FFLEFT == TRUE)
		while (ret < format->field_width)
			ret += ft_buff(buff, ' ', 0);
	return (ret);
}

/*
** Printint infinity and zero value (for f and e conversion)
*/

static int	ft_getparse(const short n, char *buff, t_format *format)
{
	int	ret;

	ret = 0;
	if (n == 1 || n == -1)
	{
		ret += ft_buff(buff, '0', 0);
		if (!(format->precision == 0 && format->flag_hash == FALSE))
			ret += ft_buff(buff, '.', 0);
		while (format->precision-- > 0)
			ret += ft_buff(buff, '0', 0);
		if (format->conversion == 'e')
		{
			ret += ft_buff(buff, 'e', 0);
			ret += ft_buff(buff, '+', 0);
			ret += ft_buff(buff, '0', 0);
			ret += ft_buff(buff, '0', 0);
		}
	}
	if (n == 2 || n == -2)
	{
		ret += ft_buff(buff, 'i', 0);
		ret += ft_buff(buff, 'n', 0);
		ret += ft_buff(buff, 'f', 0);
	}
	return (ret);
}

/*
** For Infinity and zero value.
** Take care of everything to be printed before and after the real value, due to
** field width and display flags (+- 0)
*/

static int	ft_fillparse(const short n, int len, char *buff, t_format *format)
{
	int		ret;
	t_bool	mod;

	ret = 0;
	mod = (n < 0 || FFSIGN == TRUE || FFSPAC == TRUE) ? 1 : 0;
	(format->conversion == 'e') ? mod += 4 : 1;
	FFZERO = (format->flag_zero == TRUE && format->flag_left == FALSE) ? 1 : 0;
	if (format->flag_left == TRUE || (n * n == 1 && format->flag_zero == TRUE))
	{
		ret += ft_mod(format, buff, (n < 0) ? 1 : 0);
		if (n * n == 1 && format->flag_zero == TRUE)
			while (format->field_width > len && ret < format->field_width - len)
				ret += ft_buff(buff, '0', 0);
	}
	else
	{
		while (FWIDTH > len + (int)mod && ret < FWIDTH - len - (int)mod)
			ret += ft_buff(buff, ' ', 0);
		ret += ft_mod(format, buff, (n < 0) ? 1 : 0);
	}
	ret += ft_getparse(n, buff, format);
	if (format->flag_left == TRUE)
		while (ret < format->field_width)
			ret += ft_buff(buff, ' ', 0);
	return (ret);
}

/*
** Twins double/long double funtions that check for the three float values that
** will be printed without processing the Dragon4 algorithm :
** · +/- zero
** · +/- infinity
** · not a number
*/

int			ft_parse_ldbl(const long double n, t_format *format, char *buff)
{
	int	len;
	int	ret;

	ret = 0;
	len = (FPRECI == 0 && FFHASH == FALSE) ? 1 : 2 + FPRECI;
	if (n == 0 && ((unsigned char*)&n)[9] & 0x80)
		ret = ft_fillparse(-1, len, buff, format);
	else if (n == 0 && !(((unsigned char*)&n)[9] & 0x80))
		ret = ft_fillparse(1, len, buff, format);
	else if (n == INFINITY)
		ret = ft_fillparse(2, 3, buff, format);
	else if (n == -INFINITY)
		ret = ft_fillparse(-2, 3, buff, format);
	else if ((UCN[9] & 0x7f) == 0x7f && (UCN[8] & 0xff) == 0xff)
		ret = ft_nan(buff, format);
	else
		return (0);
	return (ret);
}

int			ft_parse_dbl(const double n, t_format *format, char *buff)
{
	int	len;
	int	ret;

	ret = 0;
	len = (FPRECI == 0 && FFHASH == FALSE) ? 1 : 2 + FPRECI;
	if (n == 0 && (0x8000000000000000 & *(uint64_t*)&n))
		ret = ft_fillparse(-1, len, buff, format);
	else if (n == 0 && !((0x8000000000000000 & *(uint64_t*)&n)))
		ret = ft_fillparse(1, len, buff, format);
	else if (n == INFINITY)
		ret = ft_fillparse(2, 3, buff, format);
	else if (n == -INFINITY)
		ret = ft_fillparse(-2, 3, buff, format);
	else if ((0x7ff0000000000000 & *(uint64_t*)&n) == 0x7ff0000000000000)
		ret = ft_nan(buff, format);
	else
		return (0);
	return (ret);
}
