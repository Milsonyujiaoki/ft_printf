#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include "libft.h"

/* core */
int		ft_printf(const char *fmt, ...);

/* conversions — internal */
int		print_char(va_list args);
int		print_str(va_list args);
int		print_int(va_list args);
int		print_uint(va_list args);
int		print_hex(va_list args, int uppercase);
int		print_ptr(va_list args);
int		print_percent(void);

#endif