/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_address.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 15:13:43 by tdelabro          #+#    #+#             */
/*   Updated: 2019/02/28 14:44:51 by tdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_printf.h"

/*
** Itoa-like function, the string is kept in the stack buffer.
*/

static int	ft_getadd(uintmax_t n, char *buff, int len)
{
	int		ret;
	int		tmp;
	int		lenbis;
	char	rev[len];

	ret = 0;
	if (n == 0)
		ret += ft_buff(buff, '0', 0);
	else
	{
		lenbis = len;
		while (n != 0)
		{
			tmp = n % 16;
			rev[--lenbis] = (tmp < 10) ? tmp + '0' : tmp - 10 + 'a';
			n = n / 16;
		}
		while (lenbis < len)
			ret += ft_buff(buff, rev[lenbis++], 0);
	}
	return (ret);
}

/*
** Calcul of the number of digit after hexa conversion.
*/

int			ft_get_len_uhex(uintmax_t num, t_format *format)
{
	int			len;

	if (num == 0 && !(format->flag_prec == TRUE && format->precision == 0))
		return (1);
	len = 0;
	while ((num != 0) && (++len))
		num = num / 16;
	return (len);
}

/*
** This function allow us to print the "p" conversion variable.
*/

int			ft_sub_address(t_format *format, va_list args, char *buff)
{
	uintmax_t	add;
	int			ret;
	int			len;

	add = (uintmax_t)va_arg(args, void*);
	ret = 0;
	len = ft_get_len_uhex(add, format);
	ret = ft_pre_printing_add(format, len, buff);
	if (add == 0 && format->flag_prec == TRUE && format->precision == 0)
		return (ret);
	ret += ft_getadd(add, buff, len);
	if (format->flag_left == TRUE)
		while (ret < format->field_width)
			ret += ft_buff(buff, ' ', 0);
	return (ret);
}
