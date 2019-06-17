/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstappend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 17:35:05 by tdelabro          #+#    #+#             */
/*   Updated: 2019/06/16 20:02:48 by tdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstappend(t_list **alst, t_list *new)
{
	t_list *head;

	if (alst && new)
	{
		new->next = NULL;
		head = *alst;
		if (head == NULL)
			*alst = new;
		else
		{
			while (head->next)
				head = head->next;
			head->next = new;
		}
	}
}
