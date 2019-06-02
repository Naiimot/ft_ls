/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 15:24:46 by tdelabro          #+#    #+#             */
/*   Updated: 2019/02/22 13:21:27 by tdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_printf.h"

/*
** All these function handle the printing of character before the real output,
** based on field width, precision, flags(#+- 0).
** Each one have a sligthy different functionment but the architecture remains.
** Shared subfunctions can be find in the printing_complement.c file.
*/

int	ft_pre_printing_dec(t_format *format, int len, char *buff,\
		t_bool sign)
{
	int		ret;
	t_bool	mod;
	int		tmp;

	ret = 0;
	FFZERO = (FFZERO == 1 && FFLEFT == 0 && format->flag_prec == 0) ? 1 : 0;
	mod = (sign == 1 || FFSIGN == TRUE || FFSPAC == TRUE) ? 1 : 0;
	tmp = (format->flag_prec == TRUE && FPRECI > len) ? FPRECI : len;
	if (format->flag_zero == TRUE || format->flag_left == TRUE)
	{
		ret += ft_mod(format, buff, sign);
		while (format->flag_zero == TRUE && ret < format->field_width - tmp)
			ret += ft_buff(buff, '0', 0);
	}
	else
	{
		while (FWIDTH > tmp + (int)mod && ret < FWIDTH - tmp - (int)mod)
			ret += ft_buff(buff, ' ', 0);
		if (format->flag_zero == FALSE)
			ret += ft_mod(format, buff, sign);
	}
	ret += ft_endzero(format, len, buff, tmp);
	return (ret);
}

int	ft_pre_printing_float(t_format *format, int len, t_bool sign)
{
	int		ret;
	t_bool	mod;
	int		tmp;
	char	buff[PFBUF];

	ret = 0;
	FFZERO = (FFZERO == 1 && FFLEFT == 0) ? 1 : 0;
	mod = (sign == 1 || FFSIGN == TRUE || FFSPAC == TRUE) ? 1 : 0;
	tmp = (format->flag_prec == TRUE && FPRECI > len) ? FPRECI : len;
	if (format->flag_zero == TRUE || format->flag_left == TRUE)
	{
		ret += ft_mod(format, buff, sign);
		while (format->flag_zero == TRUE && ret < format->field_width - tmp)
			ret += ft_buff(buff, '0', 0);
	}
	else
	{
		while (FWIDTH > tmp + (int)mod && ret < FWIDTH - tmp - (int)mod)
			ret += ft_buff(buff, ' ', 0);
		if (format->flag_zero == FALSE)
			ret += ft_mod(format, buff, sign);
	}
	ret += ft_endzero(format, len, buff, tmp);
	ft_buff(buff, '0', 1);
	return (ret);
}

int	ft_pre_printing_add(t_format *format, int len, char *buff)
{
	int		ret;
	int		tmp;

	ret = 0;
	FFZERO = (FFZERO == 1 && FFLEFT == 0 && format->flag_prec == 0) ? 1 : 0;
	tmp = (format->flag_prec == TRUE && FPRECI > len) ? FPRECI : len;
	if (format->flag_zero == TRUE || format->flag_left == TRUE)
	{
		ret += ft_buff(buff, '0', 0);
		ret += ft_buff(buff, 'x', 0);
		while (format->flag_zero == TRUE && ret < format->field_width - tmp)
			ret += ft_buff(buff, '0', 0);
	}
	else
	{
		while (FWIDTH > tmp + 2 && ret < FWIDTH - tmp - 2)
			ret += ft_buff(buff, ' ', 0);
		ret += ft_buff(buff, '0', 0);
		ret += ft_buff(buff, 'x', 0);
	}
	ret += ft_endzero(format, len, buff, tmp);
	return (ret);
}

int	ft_pre_printing_uhex(t_format *format, int len, char *bf, int tmp)
{
	int	ret;

	ret = 0;
	if (format->flag_zero == TRUE || format->flag_left == TRUE)
	{
		if (format->flag_hash == TRUE)
		{
			ret += ft_buff(bf, '0', 0);
			ret += (FCONV == 'x') ? ft_buff(bf, 'x', 0) : ft_buff(bf, 'X', 0);
		}
		while (format->flag_zero == TRUE && ret < format->field_width - tmp)
			ret += ft_buff(bf, '0', 0);
	}
	else
	{
		while (FWIDTH > tmp + (FFHASH * 2) && ret < FWIDTH - tmp - (FFHASH * 2))
			ret += ft_buff(bf, ' ', 0);
		if (format->flag_hash == TRUE)
		{
			ret += ft_buff(bf, '0', 0);
			ret += (FCONV == 'x') ? ft_buff(bf, 'x', 0) : ft_buff(bf, 'X', 0);
		}
	}
	ret += ft_endzero(format, len, bf, tmp);
	return (ret);
}

int	ft_pre_printing_uoct(t_format *format, int len, char *buff, int tmp)
{
	int ret;

	ret = 0;
	if (format->flag_zero == TRUE || format->flag_left == TRUE)
	{
		if (format->flag_hash == TRUE)
			ret += ft_buff(buff, '0', 0);
		while (format->flag_zero == TRUE && format->field_width > tmp \
				&& ret < format->field_width - tmp)
			ret += ft_buff(buff, '0', 0);
	}
	else
	{
		while (format->field_width > tmp + (int)FFHASH \
			&& ret < format->field_width - tmp - (int)FFHASH)
			ret += ft_buff(buff, ' ', 0);
		if (format->flag_hash == TRUE)
			ret += ft_buff(buff, '0', 0);
	}
	ret += ft_endzero(format, len, buff, tmp);
	return (ret);
}
