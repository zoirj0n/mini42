
#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*bytes1;
	unsigned char	*bytes2;
	size_t			i;

	bytes1 = (unsigned char *) s1;
	bytes2 = (unsigned char *) s2;
	i = 0;
	while (i < n)
	{
		if (bytes1[i] != bytes2[i])
			return (bytes1[i] - bytes2[i]);
		i++;
	}
	return (0);
}
