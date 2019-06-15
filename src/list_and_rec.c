/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_and_rec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 17:26:31 by tdelabro          #+#    #+#             */
/*   Updated: 2019/06/15 15:50:56 by tdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list_and_rec.h"

static void	ft_printdir(DIR *dirp, t_dir *current, const unsigned int options)
{
	struct dirent	*dir;
	t_list			*dir_to_rec;
	t_list			*dir_to_disp;
	t_dir			tmp;

	dir_to_rec = NULL;
	dir_to_disp = NULL;
	while ((dir = readdir(dirp)) != NULL)
	{
		if ((options & OPT_ALL) || dir->d_name[0] != '.')
			if (ft_fill_fstat(&tmp, current->full, dir->d_name) == TRUE)
				ft_insert_dir(&dir_to_disp, tmp, options);
		if ((options & OPT_REC) && dir->d_type == DT_DIR\
			&& ((ft_strequ(dir->d_name, ".") == 0\
			&& ft_strequ(dir->d_name, "..") == 0)\
			&& ((options & OPT_ALL) || dir->d_name[0] != '.')))
			if (ft_fill_fstat(&tmp, current->full, dir->d_name) == TRUE)
				ft_insert_dir(&dir_to_rec, tmp, options);
	}
	closedir(dirp);
	ft_display(dir_to_disp, options, TRUE);
	if (dir_to_rec && ft_printf("\n"))
		ft_list_and_rec(dir_to_rec, options, TRUE);
	ft_del_tdir(current);
}

void		ft_list_and_rec(t_list *lst_dir, unsigned int options,\
				t_bool header)
{
	DIR		*dirp;
	t_list	*head;

	head = lst_dir;
	while (head)
	{
		if (header == TRUE || ft_lstlen(lst_dir) > 1)
			ft_printf("%s:\n", ((t_dir*)head->content)->full);
		dirp = opendir(((t_dir*)head->content)->full);
		if (dirp == NULL)
			ft_dprintf(2, "ls: %s: %s\n", ((t_dir*)head->content)->name,\
				strerror(errno));
		else
			ft_printdir(dirp, head->content, options);
		if (head->next)
			ft_printf("\n");
		head = head->next;
	}
	ft_lstclear(&lst_dir);
}
