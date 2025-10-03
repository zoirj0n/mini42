/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdheen <mdheen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 16:53:02 by mdheen            #+#    #+#             */
/*   Updated: 2025/10/03 16:53:02 by mdheen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*bytes;

	i = 0;
	bytes = (unsigned char *)s;
	while (i < n)
	{
		if (bytes[i] == (unsigned char)c)
			return (&bytes[i]);
		i++;
	}
	return (NULL);
}
