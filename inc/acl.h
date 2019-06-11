#ifndef ACL_H
# define ACL_H

# include "ft_printf.h"
# include <errno.h>
# include <sys/types.h>
# include <sys/acl.h>
# include <pwd.h>
# include <grp.h>
#include <arpa/inet.h>

# include <membership.h>

# define ID_TYPE_UID_OR_GID 30
#define ID_TYPE_NAME 31
#define ID_TYPE_WINDOWS_FQN 32

int ft_uuid_to_id(const uuid_t uu, uid_t *id, int *id_type);

#endif
