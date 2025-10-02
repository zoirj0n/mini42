/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdheen <mdheen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 19:23:22 by mdheen            #+#    #+#             */
/*   Updated: 2025/10/02 19:23:22 by mdheen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	to_find;

	i = ft_strlen(s);
	to_find = (char)c;
	while (i >= 0)
	{
		if (s[i] == to_find)
			return ((char *)&s[i]);
		i--;
	}
	return (NULL);
}
