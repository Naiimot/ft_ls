/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 16:30:05 by tdelabro          #+#    #+#             */
/*   Updated: 2019/06/02 23:16:15 by tdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <pwd.h>
#include <grp.h>

static void	ft_get_mandatories(t_list *lst, int *total, int *max_len)
{
	t_list			*h;
	int				tmp;
	struct passwd	*owner;
	struct group	*group;

	h = lst;
	*total = 0;
	ft_bzero(max_len, sizeof(int) * 4);
	while (h)
	{
		owner = getpwuid(((t_dir*)h->content)->fstat->st_uid);
		group = getgrgid(((t_dir*)h->content)->fstat->st_gid);
		*total += ((t_dir*)h->content)->fstat->st_blocks;
		if ((tmp = ft_lenint_base(((t_dir*)h->content)->fstat->st_nlink, 10))\
			> max_len[0])
			max_len[0] = tmp;
		if ((tmp = ft_strlen(owner->pw_name)) > max_len[1])
			max_len[1] = tmp;
		if ((tmp = ft_strlen(group->gr_name)) > max_len[2])
			max_len[2] = tmp;
		if ((tmp = ft_lenint_base(((t_dir*)h->content)->fstat->st_size, 10))\
			> max_len[3])
			max_len[3] = tmp;
		h = h->next;
	}
}

void		ft_display(t_list *lst, unsigned char options)
{
	t_list	*head;
	int		total;
	int		max_len[4];

	ft_get_mandatories(lst, &total, max_len);
	if ((options & 4) == 4)
		ft_printf("total %d\n", total);
	head = lst;
	while (head)
	{
		if ((options & 2) == 2 || ((t_dir*)head->content)->name[0] != '.')
		{
			if ((options & 4) == 4)
				ft_ldisplay(head->content, max_len);
			else
				ft_printf("%s\n", ((t_dir*)head->content)->name);
		}
		ft_del_tdir(head->content);
		head = head->next;
	}
}
