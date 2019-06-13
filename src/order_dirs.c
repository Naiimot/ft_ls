/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   order_dirs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 16:29:28 by tdelabro          #+#    #+#             */
/*   Updated: 2019/05/28 13:11:58 by tdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "order_dirs.h"

static void	by_size(t_list **lst, t_dir dir, const unsigned int options)
{
	t_list	*h;
	int		df;

	ft_lstadd(lst, ft_lstnew(NULL, 0));
	h = *lst;
	while (h->next)
	{
		df = ((t_dir*)h->next->content)->fstat->st_size - dir.fstat->st_size;
		if ((!(options & OPT_REV) && df < 0) || ((options & OPT_REV) && df > 0))
			break;
		h = h->next;
	}
	ft_lstinsert(&h, ft_lstnew(&dir, sizeof(t_dir)));
	h = *lst;
	*lst = h->next;
	free(h);
}

static void	by_alpha(t_list **lst, t_dir dir, const unsigned int options)
{
	t_list	*h;
	int		df;	

	ft_lstadd(lst, ft_lstnew(NULL, 0));
	h = *lst;
	while (h->next)
	{
		df = ft_strcmp(((t_dir*)h->next->content)->full, dir.full);
		if ((!(options & OPT_REV) && df > 0) || ((options & OPT_REV) && df < 0))
			break;
		h = h->next;
	}
	ft_lstinsert(&h, ft_lstnew(&dir, sizeof(t_dir)));
	h = *lst;
	*lst = h->next;
	free(h);
}

void	ft_insert_dir(t_list **lst, t_dir dir, const unsigned int options)
{
	void (*pf[5])(t_list **lst, t_dir dir, const unsigned int options);

	if (*lst == NULL || options & OPT_NOSORT)
		ft_lstappend(lst, ft_lstnew(&dir, sizeof(t_dir)));
	else
	{
		pf[0] = by_alpha;
		pf[1] = by_lat;
		pf[2] = by_lct;
		pf[3] = by_lmt;
		pf[4] = by_size;
		if (options & OPT_SIZESORT)
			(pf[4])(lst, dir, options);
		else if (options & OPT_MTIME)
		{
			if (options & OPT_ATIME)
				(pf[1])(lst, dir, options);
			else if (options & OPT_CTIME)
				(pf[2])(lst, dir, options);
			else
				(pf[3])(lst, dir, options);
		}
		else
			(pf[0])(lst, dir, options);
	}
}
