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

void		by_lmt(t_list **lst, t_dir dir, const unsigned int options)
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
		else if ((!(options & OPT_REV) && sdf < 0)\
			|| ((options & OPT_REV) && sdf > 0))
			break ;
		h = h->next;
	}
	ft_lstinsert(&h, ft_lstnew(&dir, sizeof(t_dir)));
	h = *lst;
	*lst = h->next;
	free(h);
}

void		by_lat(t_list **lst, t_dir dir, const unsigned int options)
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
		else if ((!(options & OPT_REV) && sdf < 0)\
			|| ((options & OPT_REV) && sdf > 0))
			break ;
		h = h->next;
	}
	ft_lstinsert(&h, ft_lstnew(&dir, sizeof(t_dir)));
	h = *lst;
	*lst = h->next;
	free(h);
}

void		by_lct(t_list **lst, t_dir dir, const unsigned int options)
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
		else if ((!(options & OPT_REV) && sdf < 0)\
			|| ((options & OPT_REV) && sdf > 0))
			break ;
		h = h->next;
	}
	ft_lstinsert(&h, ft_lstnew(&dir, sizeof(t_dir)));
	h = *lst;
	*lst = h->next;
	free(h);
}
