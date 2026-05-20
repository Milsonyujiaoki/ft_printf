#include "../../include/ft_printf.h"

int	print_char(t_format *fmt, va_list args)
{
	char	c;

	c = (char)va_arg(args, int);
	ft_putchar_fd(c, 1);
	(void)fmt;
	return (1);
}