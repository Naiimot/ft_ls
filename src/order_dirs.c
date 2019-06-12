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

static t_bool	ft_cmpn(long head_time, long new_time, int rev, int cmp)
{
	if (head_time == new_time\
		&& ((rev == 0  && cmp > 0) || (rev == OPT_REV && cmp < 0)))
		return (TRUE);
	else if ((rev == 0 && head_time < new_time)\
		|| (rev == OPT_REV && head_time > new_time))
		return (TRUE);
	else
		return (FALSE);
}

static void		by_lmt(t_list **lst, t_dir dir, const unsigned int options)
{
	t_list		*h;
	int			sdf;

	ft_lstadd(lst, ft_lstnew(NULL, 0));
	h = *lst;
	while (h->next)
	{
		sdf = ((t_dir*)h->next->content)->fstat->st_mtime - dir.fstat->st_mtime;
		if (sdf == 0\
			&& ft_cmpn(((t_dir*)h->next->content)->fstat->st_mtimespec.tv_nsec,\
			dir.fstat->st_mtimespec.tv_nsec, options & OPT_REV,\
			ft_strcmp(((t_dir*)h->next->content)->full, dir.full)) == TRUE)
			break ;
		else if (((options & OPT_REV) == 0 && sdf < 0)\
			|| ((options & OPT_REV) == OPT_REV && sdf > 0))
			break ;
		h = h->next;
	}
	ft_lstinsert(&h, ft_lstnew(&dir, sizeof(t_dir)));
	h = *lst;
	*lst = h->next;
	free(h);
}

static void		by_lat(t_list **lst, t_dir dir, const unsigned int options)
{
	t_list		*h;
	int			sdf;

	ft_lstadd(lst, ft_lstnew(NULL, 0));
	h = *lst;
	while (h->next)
	{
		sdf = ((t_dir*)h->next->content)->fstat->st_atime - dir.fstat->st_atime;
		if (sdf == 0\
			&& ft_cmpn(((t_dir*)h->next->content)->fstat->st_atimespec.tv_nsec,\
			dir.fstat->st_atimespec.tv_nsec, options & OPT_REV,\
			ft_strcmp(((t_dir*)h->next->content)->full, dir.full)) == TRUE)
			break ;
		else if (((options & OPT_REV) == 0 && sdf < 0)\
			|| ((options & OPT_REV) == OPT_REV && sdf > 0))
			break ;
		h = h->next;
	}
	ft_lstinsert(&h, ft_lstnew(&dir, sizeof(t_dir)));
	h = *lst;
	*lst = h->next;
	free(h);
}

static void		by_lct(t_list **lst, t_dir dir, const unsigned int options)
{
	t_list		*h;
	int			sdf;

	ft_lstadd(lst, ft_lstnew(NULL, 0));
	h = *lst;
	while (h->next)
	{
		sdf = ((t_dir*)h->next->content)->fstat->st_ctime - dir.fstat->st_ctime;
		if (sdf == 0\
			&& ft_cmpn(((t_dir*)h->next->content)->fstat->st_ctimespec.tv_nsec,\
			dir.fstat->st_ctimespec.tv_nsec, options & OPT_REV,\
			ft_strcmp(((t_dir*)h->next->content)->full, dir.full)) == TRUE)
			break ;
		else if (((options & OPT_REV) == 0 && sdf < 0)\
			|| ((options & OPT_REV) == OPT_REV && sdf > 0))
			break ;
		h = h->next;
	}
	ft_lstinsert(&h, ft_lstnew(&dir, sizeof(t_dir)));
	h = *lst;
	*lst = h->next;
	free(h);
}

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

	if (*lst == NULL)
		ft_lstadd(lst, ft_lstnew(&dir, sizeof(t_dir)));
	else
	{
		pf[0] = by_alpha;
		pf[1] = by_lat;
		pf[2] = by_lct;
		pf[3] = by_lmt;
		pf[4] = by_size;
		if (options & OPT_NOSORT)
			ft_lstappend(lst, ft_lstnew(&dir, sizeof(t_dir)));
		else if (options & OPT_SIZESORT)
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
