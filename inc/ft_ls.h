/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 16:55:11 by tdelabro          #+#    #+#             */
/*   Updated: 2019/05/27 21:25:56 by tdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H

# define FT_LS_H

# include "libft.h"
# include "ft_printf.h"
# include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>

# define VALID_OPTIONS "Ralrt"

typedef struct	s_dir
{
	char			*name;
	char			*full;
	struct stat		*fstat;
	struct passwd	*owner;
	struct group	*group;
}				t_dir;

void	ft_insert_dir(t_list **lst, t_dir dir, unsigned char options);
void	ft_ls(t_list *list_dir, unsigned char options, t_bool in_rec);
void	ft_display(t_list *lst, unsigned char options);
void	ft_del_tdir(t_dir *dir);
t_dir	ft_gen_tdir(char *path, char* name); 
void	ft_ldisplay(t_dir *dir, int *max_len);

#endif
