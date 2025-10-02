/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdheen <mdheen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 19:22:30 by mdheen            #+#    #+#             */
/*   Updated: 2025/10/02 19:22:31 by mdheen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t len)
{
	char		*dst_bytes;
	const char	*src_bytes;
	size_t		i;

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
