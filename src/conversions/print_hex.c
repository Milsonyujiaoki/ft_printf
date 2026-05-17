#include "ft_printf.h"

static int	put_hex(unsigned int n, const char *base)
{
	int	count;

	count = 0;
	if (n >= 16)
		count += put_hex(n / 16, base);
	ft_putchar_fd(base[n % 16], 1);
	return (count + 1);
}

int	print_hex(va_list args, int uppercase)
{
	unsigned int	n;
	const char		*base;

	n = va_arg(args, unsigned int);
	base = uppercase ? "0123456789ABCDEF" : "0123456789abcdef";
	return (put_hex(n, base));
}