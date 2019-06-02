/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayguillo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 17:24:01 by ayguillo          #+#    #+#             */
/*   Updated: 2019/05/26 17:38:23 by tdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst)
{
	t_list	*head;
	t_list	*tmp;

	if (lst)
	{
		head = *lst;
		while (head)
		{
			tmp = head;
			head = head->next;
			ft_bzero(tmp->content, tmp->content_size);
			ft_memdel(&(tmp->content));
			free(tmp);
		}
		*lst = NULL;
	}
}
