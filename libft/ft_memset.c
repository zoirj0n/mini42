/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdheen <mdheen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 16:53:13 by mdheen            #+#    #+#             */
/*   Updated: 2025/10/03 16:53:13 by mdheen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*bytes;
	unsigned char	val;
	size_t			i;

	bytes = b;
	val = (unsigned char)c;
	i = 0;
	while (i < len)
	{
		bytes[i] = val;
		i++;
	}
	return (b);
}
