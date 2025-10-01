
#include "ft_printf.h"

int	ft_unint(unsigned int n)
{
	int	len;

	len = 0;
	if (n > 9)
		len += ft_unint(n / 10);
	len += ft_putchar((n % 10) + '0');
	return (len);
}
