/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstappend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 17:35:05 by tdelabro          #+#    #+#             */
/*   Updated: 2019/05/25 22:05:57 by tdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstappend(t_list **alst, t_list *new)
{
	t_list *head;

	if (alst && new)
	{
		head = *alst;
		if (head == NULL)
			*alst = new;
		else
		{
			while (head->next)
				head = head->next;
			new->next = NULL;
			head->next = new;
		}
	}
}
