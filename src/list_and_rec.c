/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_and_rec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 17:26:31 by tdelabro          #+#    #+#             */
/*   Updated: 2019/06/17 17:53:21 by tdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list_and_rec.h"

static void	ft_disp_and_rec(t_list *dir_to_rec, t_list *dir_to_disp,\
				const unsigned int options)
{
	ft_get_args_stat(&dir_to_disp);
	ft_get_args_stat(&dir_to_rec);
	ft_order_dirs(&dir_to_disp, options);
	ft_order_dirs(&dir_to_rec, options);
	ft_display(dir_to_disp, options, TRUE);
	if (dir_to_rec && ft_printf("\n"))
		ft_list_and_rec(dir_to_rec, options, TRUE);
}

static void	ft_make_tdir(t_list **lst, char *path, char *name,\
				const unsigned int options)
{
	t_dir			tmp;

	ft_gen_tdir(&tmp, path, name);
	ft_initial_list(lst, tmp, options);
}

static void	ft_readdir(DIR *dirp, t_dir *current, const unsigned int options)
{
	struct dirent	*dir;
	t_list			*dir_to_rec;
	t_list			*dir_to_disp;

	dir_to_rec = NULL;
	dir_to_disp = NULL;
	while ((dir = readdir(dirp)) != NULL)
	{
		if ((options & OPT_ALL) || dir->d_name[0] != '.')
			ft_make_tdir(&dir_to_disp, current->full, dir->d_name, options);
		if ((options & OPT_REC) && dir->d_type == DT_DIR\
			&& ((ft_strequ(dir->d_name, ".") == 0\
			&& ft_strequ(dir->d_name, "..") == 0)\
			&& ((options & OPT_ALL) || dir->d_name[0] != '.')))
			ft_make_tdir(&dir_to_rec, current->full, dir->d_name, options);
	}
	closedir(dirp);
	ft_disp_and_rec(dir_to_rec, dir_to_disp, options);
	ft_del_tdir(current);
}

void		ft_list_and_rec(t_list *lst_dir, const unsigned int options,\
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
			ft_readdir(dirp, head->content, options);
		if (head->next)
			ft_printf("\n");
		head = head->next;
	}
	ft_lstclear(&lst_dir);
}
