# include "ft_printf.h"
# include "libft.h"
# include <stdarg.h>


int	print_char(va_list args)
{
    char	c;

    c = (char)va_arg(args, int);
    ft_putchar_fd(c, 1);
    return (1);
}