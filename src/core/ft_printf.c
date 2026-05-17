#include "ft_printf.h"
#include <stdarg.h>

static int	dispatch(char spec, va_list args)
{
	if (spec == 'c')
		return print_char(args);
	if (spec == 's')
		return print_str(args);
	if (spec == 'd' || spec == 'i')
		return print_int(args);
	if (spec == 'u')
		return print_uint(args);
	if (spec == 'x')
		return print_hex(args, 0);
	if (spec == 'X')
		return print_hex(args, 1);
	if (spec == 'p')
		return print_ptr(args);
	if (spec == '%')
		return print_percent();
	return (0);
}

int	ft_printf(const char *fmt, ...)
{
	va_list	args;
	int		count;
	int		i;

	count = 0;
	i = 0;
	va_start(args, fmt);
	while (fmt[i])
	{
		if (fmt[i] != '%')
		{
			ft_putchar_fd(fmt[i], 1);
			count++;
		}
		else
		{
			i++;
			if (!fmt[i])
				break ;
			count += dispatch(fmt[i], args);
		}
		i++;
	}
	va_end(args);
	return (count);
}
