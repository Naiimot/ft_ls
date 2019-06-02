/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/11 21:06:00 by tdelabro          #+#    #+#             */
/*   Updated: 2019/05/25 22:07:28 by tdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(f)(t_list *elem))
{
	t_list	*tmp;
	t_list	*new;
	t_list	*head;
	t_list	*start;

	if (!lst || !f)
		return (NULL);
	head = lst;
	tmp = f(lst);
	if (!(new = ft_lstnew(tmp->content, tmp->content_size)))
		return (NULL);
	head = head->next;
	start = new;
	while (head)
	{
		tmp = f(head);
		if (!(new->next = ft_lstnew(tmp->content, tmp->content_size)))
			return (NULL);
		head = head->next;
		new = new->next;
	}
	new->next = NULL;
	return (start);
}
