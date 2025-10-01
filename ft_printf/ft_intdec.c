
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
