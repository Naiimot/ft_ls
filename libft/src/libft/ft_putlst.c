/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putlst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 21:51:57 by tdelabro          #+#    #+#             */
/*   Updated: 2019/05/26 17:23:09 by tdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putlst(t_list *lst)
{
	t_list	*head;

	head = lst;
	while (head)
	{
		ft_putstr(head->content);
		ft_putchar('\n');
		head = head->next;
	}
}
