#include "ft_printf.h"
#include "libft.h"
#include <stdarg.h>

int	parse_flags(const char *fmt, t_format *format)
{
    int i = 0;

    while (fmt[i] && ft_strchr("-0# +", fmt[i]))
    {
        if (fmt[i] == '-')
            format->left_align = 1;
        else if (fmt[i] == '0')
            format->zero = 1;
        else if (fmt[i] == '#')
            format->hash = 1;
        else if (fmt[i] == '+')
            format->plus = 1;
        else if (fmt[i] == ' ')
            format->space = 1;
        i++;
    }
    return (i);
}