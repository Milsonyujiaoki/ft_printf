#include "../../include/ft_printf.h"

int	print_percent(t_format *fmt, va_list args)
{
	(void)fmt;
	(void)args;
	ft_putchar_fd('%', 1);
	return (1);
}