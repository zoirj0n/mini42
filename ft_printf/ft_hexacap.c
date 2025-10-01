
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
