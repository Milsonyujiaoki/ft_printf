#include "../../include/ft_printf.h"

static int	put_hex(unsigned int n, const char *base)
{
	int	count;

	count = 0;
	if (n >= 16)
		count += put_hex(n / 16, base);
	ft_putchar_fd(base[n % 16], 1);
	return (count + 1);
}

int	print_hex(t_format *fmt, va_list args)
{
	unsigned int	n;
	const char		*base;

	n = va_arg(args, unsigned int);
	base = (fmt->specifier == SP_HEX_UP) ? "0123456789ABCDEF" : "0123456789abcdef";
	(void)fmt;
	return (put_hex(n, base));
}