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

#include "ft_ls.h"
#include <errno.h>  
#include <strings.h>

static void by_lmt(t_list **lst, t_dir dir, unsigned char options)
{
	t_list		*h;
	
	ft_lstadd(lst, ft_lstnew(NULL, 0));
	h = *lst;
	while (h->next)
	{
		if ((((t_dir*)h->next->content)->fstat->st_mtime\
		== dir.fstat->st_mtime) && (((options & 8) == 0\
		&& ft_strcmp(((t_dir*)h->next->content)->name, dir.name) > 0)\
		|| ((options & 8) == 8\
		&& ft_strcmp(((t_dir*)h->next->content)->name, dir.name) < 0)))
				break;
		if (((options & 8) == 0\
		&& ((t_dir*)h->next->content)->fstat->st_mtime < dir.fstat->st_mtime)\
		|| ((options & 8) == 8\
		&& ((t_dir*)h->next->content)->fstat->st_mtime > dir.fstat->st_mtime))
			break;
		h = h->next;
	}
	ft_lstinsert(&h, ft_lstnew(&dir, sizeof(t_dir)));
	h = *lst;
	*lst = h->next;
	free(h);
}

static void	by_alpha(t_list **lst, t_dir dir, unsigned char options)
{
	t_list		*h;
	
	ft_lstadd(lst, ft_lstnew(NULL, 0));
	h = *lst;
	while (h->next)
	{
		if (((options & 8) == 0\
			&& ft_strcmp(((t_dir*)h->next->content)->name, dir.name) > 0)\
			|| ((options & 8) == 8\
			&& ft_strcmp(((t_dir*)h->next->content)->name, dir.name) < 0))
				break;
			h = h->next;
	}
	ft_lstinsert(&h, ft_lstnew(&dir, sizeof(t_dir)));
	h = *lst;
	*lst = h->next;
	free(h);
}

void	ft_insert_dir(t_list **lst, t_dir dir, unsigned char options)
{
	void (*pf[2])(t_list **lst, t_dir dir, unsigned char options);

	if (*lst == NULL)
		ft_lstadd(lst, ft_lstnew(&dir, sizeof(t_dir)));
	else
	{
		pf[0] = by_alpha;
		pf[1] = by_lmt;
		if ((options & 16) == 16)
			(pf[1])(lst, dir, options);
		else
			(pf[0])(lst, dir, options);
	}
}
