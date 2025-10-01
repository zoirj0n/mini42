
#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	to_find;

	i = ft_strlen(s);
	to_find = (char) c;
	while (i >= 0)
	{
		if (s[i] == to_find)
			return ((char *) &s[i]);
		i--;
	}
	return (NULL);
}
