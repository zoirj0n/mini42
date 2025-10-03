/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexacap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdheen <mdheen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 16:50:31 by mdheen            #+#    #+#             */
/*   Updated: 2025/10/03 16:50:32 by mdheen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_hexacap(unsigned int n)
{
	int		len;
	char	*s;

	len = 0;
	s = "0123456789ABCDEF";
	if (n > 15)
		len += ft_hexacap(n / 16);
	len += ft_putchar(s[n % 16]);
	return (len);
}
