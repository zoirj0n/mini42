
#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*dst_bytes;
	const char	*src_bytes;
	int			i;

	if (len == 0)
		return (dst);
	dst_bytes = dst;
	src_bytes = src;
	if (src_bytes < dst_bytes && src_bytes + len >= dst_bytes)
	{
		i = len - 1;
		while (i >= 0)
		{
			dst_bytes[i] = src_bytes[i];
			i--;
		}
	}
	else
		ft_memcpy(dst, src, len);
	return (dst);
}
