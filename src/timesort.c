/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timesort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 16:11:58 by tdelabro          #+#    #+#             */
/*   Updated: 2019/06/17 17:50:49 by tdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "order_dirs.h"

static t_bool	ft_cmpn(long head_time, long new_time, int rev)
{
	if ((rev == 0 && head_time < new_time)\
		|| (rev == OPT_REV && head_time > new_time))
		return (TRUE);
	else
		return (FALSE);
}

void by_lmt(t_list **lst, t_list *new, const unsigned int options)
{
	t_list	*head;
	t_list	*prev;
	int		df;

	head = *lst; 
	prev = NULL;
	while (head)
	{
			if (!(df = ((t_dir*)head->content)->fstat->st_mtime\
			- ((t_dir*)new->content)->fstat->st_mtime)\
			&& ft_cmpn(((t_dir*)head->content)->fstat->st_mtimespec.tv_nsec,\
			((t_dir*)new->content)->fstat->st_mtimespec.tv_nsec,\
			options & OPT_REV) == TRUE)
			break ;
		else if (((options & OPT_REV) && df > 0)\
			|| (!(options & OPT_REV) && df < 0))
			break ;
		prev = head;
		head = head->next;
	}
	if (prev)
		ft_lstinsert(prev, new);
	else
		ft_lstadd(lst, new);
}

void by_lat(t_list **lst, t_list *new, const unsigned int options)
{
	t_list	*head;
	t_list	*prev;
	int		df;

	head = *lst; 
	prev = NULL;
	while (head)
	{
			if (!(df = ((t_dir*)head->content)->fstat->st_atime\
			- ((t_dir*)new->content)->fstat->st_atime)\
			&& ft_cmpn(((t_dir*)head->content)->fstat->st_atimespec.tv_nsec,\
			((t_dir*)new->content)->fstat->st_atimespec.tv_nsec,\
			options & OPT_REV) == TRUE)
			break ;
		else if (((options & OPT_REV) && df > 0)\
			|| (!(options & OPT_REV) && df < 0))
			break ;
		prev = head;
		head = head->next;
	}
	if (prev)
		ft_lstinsert(prev, new);
	else
		ft_lstadd(lst, new);
}

void by_lct(t_list **lst, t_list *new, const unsigned int options)
{
	t_list	*head;
	t_list	*prev;
	int		df;

	head = *lst; 
	prev = NULL;
	while (head)
	{
			if (!(df = ((t_dir*)head->content)->fstat->st_ctime\
			- ((t_dir*)new->content)->fstat->st_ctime)\
			&& ft_cmpn(((t_dir*)head->content)->fstat->st_ctimespec.tv_nsec,\
			((t_dir*)new->content)->fstat->st_ctimespec.tv_nsec,\
			options & OPT_REV) == TRUE)
			break ;
		else if (((options & OPT_REV) && df > 0)\
			|| (!(options & OPT_REV) && df < 0))
			break ;
		prev = head;
		head = head->next;
	}
	if (prev)
		ft_lstinsert(prev, new);
	else
		ft_lstadd(lst, new);
}
