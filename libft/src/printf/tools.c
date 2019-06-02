/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 16:33:18 by tdelabro          #+#    #+#             */
/*   Updated: 2019/02/20 16:33:22 by tdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_printf.h"

/*
** Initialise all the t_format strct's flags to zero.
*/

void	ft_formattozero(t_format *format)
{
	format->flag_hash = 0;
	format->flag_zero = 0;
	format->flag_left = 0;
	format->flag_sign = 0;
	format->flag_space = 0;
	format->field_width = 0;
	format->flag_prec = 0;
	format->precision = 0;
	format->len_mod = 0;
	format->conversion = 0;
}

/*
** A custom atoi used to get precison and width values.
*/

int		ft_ptf_atoi(const char *str, t_format *format, t_bool conv)
{
	int i;
	int num;

	i = 0;
	num = 0;
	if (!(str[i] >= '0' && str[i] <= '9'))
		return (0);
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (num > 214748364 || (num == 214748364 && str[i] - '0' > 7))
		{
			if (conv == FALSE)
				return (-1);
			else
				return ((format->conversion == 'f' \
					|| format->conversion == 'e') ? 6 : 0);
		}
		num = num * 10 + (str[i] - '0');
		i++;
	}
	return (num);
}

/*
** Function used in order to calcul the float first digit's power of 10.
*/

int		ft_getfirstdigit_ldbl(long double n)
{
	int	firstdigitexpo;

	((unsigned char*)&n)[9] = 0x7f & ((unsigned char*)&n)[9];
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
** Two small functions attached to the 'e' conversion flag.
*/

void	ft_postround(int *fdigitexp, int *tmp, int *ret)
{
	*fdigitexp += 1;
	*tmp += 2;
	*ret -= 2;
}

void	ft_expo(char *str, int *tab, int *ret)
{
	str[*ret] = 'e';
	str[++*ret] = (tab[3] == 0) ? '-' : '+';
	(tab[0] < 10) ? str[++*ret] = '0' : 1;
	ft_strcpy(&(str[++*ret]), ft_itoa(tab[0]));
	*ret += (int)ft_lenint_base(tab[0], 10);
}
