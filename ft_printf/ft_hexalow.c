/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexalow.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdheen <mdheen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 19:20:43 by mdheen            #+#    #+#             */
/*   Updated: 2025/10/02 19:20:44 by mdheen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_hexalow(unsigned int n)
{
	int		len;
	char	*s;

	len = 0;
	s = "0123456789abcdef";
	if (n > 15)
		len += ft_hexalow(n / 16);
	len += ft_putchar(s[n % 16]);
	return (len);
}
