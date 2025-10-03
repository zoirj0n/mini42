/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdheen <mdheen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 16:52:11 by mdheen            #+#    #+#             */
/*   Updated: 2025/10/03 16:52:11 by mdheen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*bytes;
	size_t			i;

	if (n == 0)
		return ;
	bytes = s;
	i = 0;
	while (i < n)
	{
		bytes[i] = 0;
		i++;
	}
}
