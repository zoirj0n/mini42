/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intdec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdheen <mdheen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 19:20:46 by mdheen            #+#    #+#             */
/*   Updated: 2025/10/02 19:20:47 by mdheen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_intdec(int n)
{
	int	len;

	len = 0;
	if (n == -2147483648)
	{
		len += ft_putstr("-2147483648");
		return (len);
	}
	if (n < 0)
	{
		len += ft_putchar('-');
		n = -n;
	}
	if (n > 9)
		len += ft_intdec(n / 10);
	len += ft_putchar((n % 10) + '0');
	return (len);
}
