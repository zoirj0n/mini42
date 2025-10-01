
#include "libft.h"

int	ft_toupper(int c)
{
	int	uppercase_diff;

	uppercase_diff = 'a' - 'A';
	if (c >= 'a' && c <= 'z')
		return (c - uppercase_diff);
	return (c);
}
