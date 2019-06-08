#ifndef LDISPLAY_H
# define LDISPLAY_H

# include "ft_ls.h"
# include "ft_printf.h"
# include <sys/types.h> 
# include <sys/stat.h> 
# include <pwd.h>
# include <grp.h>
# include <time.h>
# include <string.h>
# include <limits.h>
# include <unistd.h>

char	ft_xattr_acl(t_dir *dir);

#endif
