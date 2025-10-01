
#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*bytes;
	unsigned char	val;
	size_t			i;

	bytes = b;
	val = (unsigned char) c;
	i = 0;
	while (i < len)
	{
		bytes[i] = val;
		i++;
	}
	return (b);
}
