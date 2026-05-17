# include "ft_printf.h"
# include "libft.h"
# include <stdarg.h>

int	dispatch_conversion(t_format *fmt, va_list args)
{
    if (fmt->specifier == SP_CHAR)
        return (print_char(args));
    /*else if (fmt->specifier == SP_STR)
        return (print_str(args));
    else if (fmt->specifier == SP_DEC || fmt->specifier == SP_INT)
        return (print_int(args));
    else if (fmt->specifier == SP_UINT)
        return (print_uint(args));
    else if (fmt->specifier == SP_HEX_LOW || fmt->specifier == SP_HEX_UP)
        return (print_hex(args, fmt->specifier));
    else if (fmt->specifier == SP_PTR)
        return (print_ptr(args));
    else if (fmt->specifier == SP_PERCENT)
        return (print_percent(args));*/
    return (-1);
}