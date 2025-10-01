
#include "libft.h"

int	ft_tolower(int c)
{
	int	uppercase_diff;

	uppercase_diff = 'a' - 'A';
	if (c >= 'A' && c <= 'Z')
		return (c + uppercase_diff);
	return (c);
}
