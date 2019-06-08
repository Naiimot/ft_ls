#ifndef DISPLAY_H
# define DISPLAY_H

# include "ft_ls.h"
# include "t_dir.h"
# include <sys/types.h> 
# include <sys/stat.h> 
# include <pwd.h>
# include <grp.h>

void	ft_ldisplay(t_dir *dir, int *max_len, unsigned char options);
void	ft_del_tdir(t_dir *dir);

#endif
