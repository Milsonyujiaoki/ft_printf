#include "ft_printf.h"
#include <stdarg.h>

static int	dispatch(char spec, va_list args)
{
    switch (spec)
    {
    case 'c':
        return print_char(args);
    case 's':
        return print_str(args);
    case 'd':
        return print_int(args);
    case 'i':
        return print_int(args);
    case 'u':
        return print_uint(args);
    case 'x':
        return print_hex(args, 0);
    case 'X':
        return print_hex(args, 1);
    case 'p':
        return print_ptr(args);
    case '%':
        return print_percent();
    default:
        return (0);
    }
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
