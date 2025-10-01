
#include "ft_printf.h"

int	ft_hexadec(unsigned long n)
{
	int		len;
	char	*s;

	s = "0123456789abcdef";
	len = 0;
	if (n > 15)
		len += ft_hexadec(n / 16);
	len += ft_putchar(s[n % 16]);
	return (len);
}

int	ft_hexaddr(unsigned long n)
{
	int	len;

	len = ft_putstr("0x");
	if (n == 0)
		len += ft_putchar('0');
	else
		len += ft_hexadec(n);
	return (len);
}
