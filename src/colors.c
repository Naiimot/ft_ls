#include "colors.h"

static char	*ft_colorize_2(char c)
{
	if (c == 'c')
		return (C_CPERIPH);
	else if (c == 'b')
		return (C_BPERIPH);
	else if (c == 'l')
		return (C_SLINK);
	else if (c == 'p')
		return (C_PIPE);
	else if (c == 's')
		return (C_SOCKET);
	else
		return (C_REGULAR);
}

char		*ft_colorize(char *perms, unsigned int options)
{
	if (options & OPT_COLOR)
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
		else
			return (ft_colorize_2(perms[0]));
	}
	else
		return (C_REGULAR);
}
