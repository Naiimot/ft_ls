/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   order_dirs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 16:29:28 by tdelabro          #+#    #+#             */
/*   Updated: 2019/06/16 23:42:56 by tdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "order_dirs.h"

void by_size(t_list **lst, t_list *current, const unsigned int options)
{
	t_list	*head;
	t_list	*prev;
	int		df;

	head = *lst; 
	prev = NULL;
	while (head)
	{
		df = ((t_dir*)head->content)->fstat->st_size\
			- ((t_dir*)current->content)->fstat->st_size;
		if ((!(options & OPT_REV) && df < 0)\
			|| ((options & OPT_REV) && df > 0))
			break ;
		prev = head;
		head = head->next;
	}
	if (prev)
		ft_lstinsert(prev, current);
	else
		ft_lstadd(lst, current);
}

static void	by_alpha(t_list **lst, t_dir dir, const unsigned int options)
{
	t_list	*h;
	t_list	*prev;
	int		df;

	h = *lst;
	prev = NULL;
	while (h)
	{
		df = ft_strcmp(((t_dir*)h->content)->full, dir.full);
		if ((!(options & OPT_REV) && df > 0) || ((options & OPT_REV) && df < 0))
			break ;
		prev = h;
		h = h->next;
	}
	if (prev)
		ft_lstinsert(prev, ft_lstnew(&dir, sizeof(t_dir)));
	else
		ft_lstadd(lst, ft_lstnew(&dir, sizeof(t_dir)));
}

void		ft_initial_list(t_list **lst, t_dir dir,\
				const unsigned int options)
{
	if (*lst == NULL || options & OPT_NOSORT)
		ft_lstappend(lst, ft_lstnew(&dir, sizeof(t_dir)));
	else
		by_alpha(lst, dir, options);
}

void		ft_order_dirs(t_list **lst, const unsigned options)
{
	void (*pf[4])(t_list **lst, t_list *current, const unsigned int options);
	t_list	*head;
	t_list	*tmp;

	if (*lst == NULL || (options & OPT_NOSORT))
		return ;
	pf[0] = by_lat;
	pf[1] = by_lct;
	pf[2] = by_lmt;
	pf[3] = by_size;
	head = (*lst)->next;
	(*lst)->next = NULL;
	while (head)
	{
		tmp = head->next;
		if (options & OPT_SIZESORT)
			(pf[3])(lst, head, options);
		else if (options & OPT_MTIME)
		{
			if (options & OPT_ATIME)
				(pf[0])(lst, head, options);
			else if (options & OPT_CTIME)
				(pf[1])(lst, head, options);
			else
				(pf[2])(lst, head, options);
		}
		else
			ft_lstappend(lst, head);
		head = tmp;
	}
}
