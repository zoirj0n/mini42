
#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	char	to_find;

	i = 0;
	if (s == NULL)
		return (NULL);
	to_find = (char) c;
	while (s[i] != '\0')
	{
		if (s[i] == to_find)
			return ((char *) &s[i]);
		i++;
	}
	if (s[i] == to_find)
		return ((char *) &s[i]);
	return (NULL);
}
