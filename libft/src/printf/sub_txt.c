/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_txt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 23:28:50 by tdelabro          #+#    #+#             */
/*   Updated: 2019/02/28 18:39:57 by tdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_printf.h"

/*
** Function to be use if the conversion instruction does not contain any valid
** conversion symbol.
*/

int			ft_sub_unknown(t_format *format, va_list args, char *buff)
{
	int		ret;
	char	padd;

	if (args || !args)
		ret = 0;
	padd = (FFZERO == TRUE && FFLEFT == FALSE) ? '0' : ' ';
	if (format->flag_left == FALSE)
	{
		if (format->field_width > 1)
			while (ret < format->field_width - 1)
				ret += ft_buff(buff, padd, 0);
	}
	ret += ft_buff(buff, format->conversion, 0);
	while (ret < format->field_width)
		ret += ft_buff(buff, ' ', 0);
	return (ret);
}

/*
** Handle the '%' conversion.
*/

int			ft_sub_percent(t_format *format, va_list args, char *buff)
{
	char	padd;
	int		ret;

	if (args || !args)
		ret = 0;
	padd = (FFZERO == TRUE && FFLEFT == FALSE) ? '0' : ' ';
	if (format->flag_left == FALSE)
	{
		if (format->field_width > 1)
			while (ret < format->field_width - 1)
				ret += ft_buff(buff, padd, 0);
	}
	ret += ft_buff(buff, '%', 0);
	while (ret < format->field_width)
		ret += ft_buff(buff, ' ', 0);
	return (ret);
}

/*
** Handle the 'c' conversion, character printing.
*/

int			ft_sub_char(t_format *format, va_list args, char *buff)
{
	char	c;
	int		ret;
	char	padd;

	c = va_arg(args, int);
	ret = 0;
	padd = (format->flag_zero == TRUE && FFLEFT == FALSE) ? '0' : ' ';
	if (format->flag_left == FALSE)
		if (format->field_width > 1)
			while (ret < format->field_width - 1)
				ret += ft_buff(buff, padd, 0);
	ret += ft_buff(buff, c, 0);
	if (format->flag_left == TRUE)
		while (ret < format->field_width)
			ret += ft_buff(buff, ' ', 0);
	return (ret);
}

/*
** Handle the 's' conversion, string printing.
*/

static	int	ft_getstr(char *buff, char *str, t_bool prec, int precision)
{
	int	i;

	i = 0;
	while (str[i] && (prec == FALSE || (prec == TRUE && i < precision)))
	{
		ft_buff(buff, str[i], 0);
		i++;
	}
	return (i);
}

int			ft_sub_string(t_format *format, va_list args, char *buff)
{
	char	*str;
	char	padd;
	int		ret;
	int		tmp;

	str = va_arg(args, char*);
	ret = 0;
	if (str)
		!(str[0]) ? format->flag_prec = 0 : 1;
	padd = (format->flag_zero == TRUE && FFLEFT == FALSE) ? '0' : ' ';
	tmp = (str == NULL) ? 6 : ft_strlen(str);
	if (format->flag_left == FALSE)
	{
		tmp = (format->flag_prec == TRUE && FPRECI < tmp) ? FPRECI : tmp;
		while (tmp++ < format->field_width)
			ret += ft_buff(buff, padd, 0);
	}
	ret += ft_getstr(buff, (str == NULL) ? "(null)" : str,\
											format->flag_prec, FPRECI);
	if (format->flag_left == TRUE)
		while (ret < format->field_width)
			ret += ft_buff(buff, ' ', 0);
	return (ret);
}
