#ifndef DISPLAY_H
# define DISPLAY_H

# include "ft_ls.h"
# include "t_dir.h"
# include <sys/types.h> 
# include <sys/stat.h> 
# include <pwd.h>
# include <grp.h>
# include <colors.h>

void	ft_ldisplay(t_dir *dir, int *max_len, char *perms,\
			unsigned int options);
void	ft_del_tdir(t_dir *dir);

#endif
