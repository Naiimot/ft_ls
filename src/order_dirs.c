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
#include <sys/types.h> 
#include <sys/stat.h> 

static void by_lmt(t_list **lst, t_dir dir, unsigned char options)
{
	t_list		*head;
	struct stat	stat_h;
	struct stat	stat_n;
	
	ft_lstadd(lst, ft_lstnew(NULL, 0));
	head = *lst;
	stat(dir.full, &stat_n);
	while (head->next)
	{
		stat(((t_dir*)head->next->content)->full, &stat_h);
		if ((stat_h.st_mtime == stat_n.st_mtime) && (((options & 8) == 0\
			&& ft_strcmp(((t_dir*)head->next->content)->name, dir.name) > 0)\
			|| ((options & 8) == 8\
			&& ft_strcmp(((t_dir*)head->next->content)->name, dir.name) < 0)))
				break;
		if (((options & 8) == 0 && stat_h.st_mtime < stat_n.st_mtime)\
			|| ((options & 8) == 8 && stat_h.st_mtime > stat_n.st_mtime))
			break;
		head = head->next;
	}
	ft_lstinsert(&head, ft_lstnew(&dir, sizeof(t_dir)));
	head = *lst;
	*lst = head->next;
	free(head);
}

static void	by_alpha(t_list **lst, t_dir dir, unsigned char options)
{
	t_list		*head;
	
	head = *lst;
	if (((options & 8) == 0\
	&& ft_strcmp(((t_dir*)head->content)->name, dir.name) > 0)\
	|| ((options & 8) == 8\
	&& ft_strcmp(((t_dir*)head->content)->name, dir.name) < 0))
		ft_lstadd(lst, ft_lstnew(&dir, sizeof(t_dir)));
	else
	{
		while (head->next)
		{
			if (((options & 8) == 0\
			&& ft_strcmp(((t_dir*)head->content)->name, dir.name) > 0)\
			|| ((options & 8) == 8\
			&& ft_strcmp(((t_dir*)head->content)->name, dir.name) < 0))
				break;
			head = head->next;
		}
		ft_lstinsert(&head, ft_lstnew(&dir, sizeof(t_dir)));
	}
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
