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

#include "display.h"

static void	ft_len_fields(t_dir *dir, int *field_sizes, struct passwd *owner,\
				struct group *group)
{
	int	tmp;

	owner = getpwuid(dir->fstat->st_uid);
	group = getgrgid(dir->fstat->st_gid);
	field_sizes[4] += dir->fstat->st_blocks;
	if ((tmp = ft_lenint_base(dir->fstat->st_nlink, 10)) > field_sizes[0])
		field_sizes[0] = tmp;
	if ((tmp = ft_strlen(owner->pw_name)) > field_sizes[1])
		field_sizes[1] = tmp;
	if ((tmp = ft_strlen(group->gr_name)) > field_sizes[2])
		field_sizes[2] = tmp;
	if ((tmp = ft_lenint_base(dir->fstat->st_size, 10))\
		> field_sizes[3])
		field_sizes[3] = tmp;
}

static void	ft_get_field_sizes(t_list *lst, int *field_sizes)
{
	t_list			*h;
	struct passwd	*owner;
	struct group	*group;

	h = lst;
	ft_bzero(field_sizes, sizeof(int) * 5);
	owner = NULL;
	group = NULL;
	while (h)
	{
		ft_len_fields(h->content, field_sizes, owner, group);
		h = h->next;
	}
}

void		ft_display(t_list *lst, unsigned char options, t_bool dirs)
{
	t_list	*head;
	int		field_sizes[5];

	ft_get_field_sizes(lst, field_sizes);
	if ((options & 4) == 4 && dirs == TRUE)
		ft_printf("total %d\n", field_sizes[4]);
	head = lst;
	while (head)
	{
		if ((options & 2) == 2 || ((t_dir*)head->content)->name[0] != '.')
		{
			if ((options & 4) == 4)
				ft_ldisplay(head->content, field_sizes, options);
			else
				ft_printf("%s\n", ((t_dir*)head->content)->name);
		}
		ft_del_tdir(head->content);
		head = head->next;
	}
	ft_lstclear(&lst);
}
