
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dest_len;
	size_t	src_len;
	size_t	i;

	dest_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	i = 0;
	while (i < src_len && dstsize > i + dest_len + 1)
	{
		dst[dest_len + i] = src[i];
		i++;
	}
	if (dstsize != 0)
		dst[dest_len + i] = '\0';
	if (dstsize < dest_len)
		dest_len = dstsize;
	return (dest_len + src_len);
}
