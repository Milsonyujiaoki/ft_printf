# include "ft_printf.h"
# include "libft.h"
# include <stdarg.h>

int parse_specifier(const char *fmt, t_format *format)
{
    int i = 0;

    if (ft_strchr("cspdiuxX%", fmt[i]))
    {
        format->specifier = (t_specifier)fmt[i];
        i++;
    }
    return (i);
}