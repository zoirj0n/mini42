
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
