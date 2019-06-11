#include "colors.h"

char	*ft_colorize(char *perms, unsigned int options)
{
	if ((options & 1 << 7) == 1 << 7)
	{
		if (perms[0] == '-')
		{
			if (perms[3] == 's')
				return (C_USTICKY);
			else if (perms[6] == 's')
				return (C_GSTICKY);
			else if (perms[3] == 'x' || perms[6] == 'x' || perms[9] == 'x' )
				return (C_EXEC);
			else
				return (C_REGULAR);
		}
		else if (perms[0] == 'd')
		{
			if (perms[8] == 'w')
				return ((perms[9] == 't') ? C_DIR_WO_S : C_DIR_WO_NS);
			else
				return (C_DIR);
		}
		else if (perms[0] == 'c')
			return (C_CPERIPH);
		else if (perms[0] == 'b')
			return (C_BPERIPH);
		else if (perms[0] == 'l')
			return (C_SLINK);
		else if (perms[0] == 'p')
			return (C_PIPE);
		else if (perms[0] == 's')
			return (C_SOCKET);
	}
	else
		return (C_REGULAR);
}
