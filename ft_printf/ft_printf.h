
#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdio.h>
# include <unistd.h>

int	ft_stderr(const char *str, ...);
int	ft_putchar(int c);
int	ft_putstr(char *str);
int	ft_hexaddr(unsigned long n);
int	ft_intdec(int n);
int	ft_unint(unsigned int n);
int	ft_hexalow(unsigned int n);
int	ft_hexacap(unsigned int n);

#endif
