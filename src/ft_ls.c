/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 17:26:31 by tdelabro          #+#    #+#             */
/*   Updated: 2019/05/28 13:11:37 by tdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <errno.h>
#include <string.h>

static void			ft_printdir(DIR *dirp, char *path,  unsigned char options)
{
	struct	dirent	*dir;
	t_list			*dir_to_rec;
	t_list			*dir_to_disp;

	dir_to_rec = NULL;
	dir_to_disp = NULL;
	while ((dir = readdir(dirp)) != NULL)
	{
		if ((options & 2) == 2 || dir->d_name[0] != '.')
			ft_insert_dir(&dir_to_disp, ft_gen_tdir(path, dir->d_name), options);
		if ((options & 1) == 1 && dir->d_type == DT_DIR\
			&& ((ft_strequ(dir->d_name, ".") == 0\
			&& ft_strequ(dir->d_name, "..") == 0)\
			&& ((options & 2) == 2 || dir->d_name[0] != '.')))
			ft_insert_dir(&dir_to_rec, ft_gen_tdir(path, dir->d_name), options);
	}
	closedir(dirp);
	ft_display(dir_to_disp, options);
	ft_lstclear(&dir_to_disp);
	if (dir_to_rec && ft_printf("\n"))
		ft_ls(dir_to_rec, options, TRUE);
}

void			ft_ls(t_list *lst_dir, unsigned char options, t_bool in_rec)
{
	DIR		*dirp;
	t_list	*head;
	int		dir_count;

	dir_count = ft_lstlen(lst_dir);
	head = lst_dir;
	while (head)
	{
		dirp = opendir(((t_dir*)head->content)->full);
		if (dirp == NULL)
			ft_dprintf(2, "ls: %s: %s\n", ((t_dir*)head->content)->full,\
				strerror(errno));
		else
		{
			if (in_rec == TRUE || dir_count > 1)
				ft_printf("%s:\n", ((t_dir*)head->content)->full);
			ft_printdir(dirp, ((t_dir*)head->content)->full, options);
			if (head->next)
				ft_printf("\n");
		}
		ft_del_tdir(head->content);
		head = head->next;
	}
	ft_lstclear(&lst_dir);
}
