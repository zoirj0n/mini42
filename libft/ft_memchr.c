
#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*bytes;

	i = 0;
	bytes = (unsigned char *)s;
	while (i < n)
	{
		if (bytes[i] == (unsigned char) c)
			return (&bytes[i]);
		i++;
	}
	return (NULL);
}
