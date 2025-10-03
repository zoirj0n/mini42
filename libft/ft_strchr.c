/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdheen <mdheen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 16:53:31 by mdheen            #+#    #+#             */
/*   Updated: 2025/10/03 16:53:31 by mdheen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	char	to_find;

	i = 0;
	if (s == NULL)
		return (NULL);
	to_find = (char)c;
	while (s[i] != '\0')
	{
		if (s[i] == to_find)
			return ((char *)&s[i]);
		i++;
	}
	if (s[i] == to_find)
		return ((char *)&s[i]);
	return (NULL);
}
