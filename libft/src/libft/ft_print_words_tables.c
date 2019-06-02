/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_words_tables.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 14:09:23 by tdelabro          #+#    #+#             */
/*   Updated: 2019/05/25 22:34:20 by tdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_words_tables(const char **tab)
{
	int i;

	if (tab)
	{
		i = 0;
		while (tab[i])
		{
			ft_putstr(tab[i]);
			ft_putchar('\n');
			i++;
		}
	}
}
