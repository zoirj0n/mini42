
#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t len)
{
	char			*dst_bytes;
	const char		*src_bytes;
	size_t			i;

	dst_bytes = dst;
	src_bytes = src;
	i = 0;
	while (i < len)
	{
		dst_bytes[i] = src_bytes[i];
		i++;
	}
	return (dst);
}
