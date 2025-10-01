
#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*bytes;
	size_t			i;

	if (n == 0)
		return ;
	bytes = s;
	i = 0;
	while (i < n)
	{
		bytes[i] = 0;
		i++;
	}
}
