/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_lists.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 19:15:24 by tdelabro          #+#    #+#             */
/*   Updated: 2019/06/17 19:30:23 by tdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "manage_lists.h"

void	ft_split_args(t_list *tab_lst[2], const unsigned int options)
{
	t_list	*prev;
	t_list	*head;
	t_list	*next;

	ft_order_dirs(&tab_lst[0], options);
	head = tab_lst[0];
	prev = NULL;
	while (head)
	{
		next = head->next;
		if (!(options & OPT_NORECDIR)\
			&& ((t_dir*)head->content)->fstat
			&& S_ISDIR(((t_dir*)head->content)->fstat->st_mode))
		{
			if (prev)
				prev->next = head->next;
			else
				tab_lst[0] = tab_lst[0]->next;
			ft_lstappend(&tab_lst[1], head);
		}
		else
			prev = head;
		head = next;
	}
}

t_bool	ft_get_args_stat(t_list **lst)
{
	t_list	*head;
	t_list	*prev;
	t_bool	printed;

	printed = (ft_lstlen(*lst)) > 1 ? TRUE : FALSE;
	head = *lst;
	prev = NULL;
	while (head)
	{
		if (!ft_gen_fstat(head->content))
		{
			if (prev)
				prev->next = head->next;
			else
				*lst = head->next;
			free(head->content);
			free(head);
		}
		else
			prev = head;
		head = head->next;
	}
	return (printed);
}
