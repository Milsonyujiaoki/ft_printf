#include "../../include/ft_printf.h"

static int	put_addr(unsigned long n)
{
	int	count;

	count = 0;
	if (n >= 16)
		count += put_addr(n / 16);
	count += put_char_len("0123456789abcdef"[n % 16]);
	return (count);
}

int	print_ptr(t_format *fmt, va_list args)
{
	unsigned long	addr;

	(void)fmt;
	addr = (unsigned long)va_arg(args, void *);
	if (addr == 0)
		return (put_str_len("(nil)", -1));
	return (
		put_str_len("0x", -1)
		+ put_addr(addr)
	);
}