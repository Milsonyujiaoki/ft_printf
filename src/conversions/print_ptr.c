#include "ft_printf.h"

static int	put_addr(unsigned long n)
{
	int	count;

	count = 0;
	if (n >= 16)
		count += put_addr(n / 16);
	ft_putchar_fd("0123456789abcdef"[n % 16], 1);
	return (count + 1);
}

int	print_ptr(va_list args)
{
	unsigned long	addr;

	addr = (unsigned long)va_arg(args, void *);
	ft_putstr_fd("0x", 1);
	if (addr == 0)
	{
		ft_putchar_fd('0', 1);
		return (3);
	}
	return (2 + put_addr(addr));
}