#include "../../include/ft_printf.h"

static int	put_uint(unsigned int n)
{
	int	count;

	count = 0;
	if (n >= 10)
		count += put_uint(n / 10);
	ft_putchar_fd('0' + (n % 10), 1);
	return (count + 1);
}

int	print_uint(t_format *fmt, va_list args)
{
	(void)fmt;
	return (put_uint(va_arg(args, unsigned int)));
}