#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdint.h>



typedef struct s_format
{
		char	specifier;
}	t_format;

/* core */
int		ft_printf(const char *format, ...);
int		dispatch_conversion(t_format *fmt, va_list args);

/* parser */
int		parse_flags(const char *fmt, t_format *format);
int		parse_width(const char *fmt, t_format *format);
int		parse_precision(const char *fmt, t_format *format);
int		parse_specifier(const char *fmt, t_format *format);
int		parse_format(const char *fmt, t_format *format);

/* conversions */
int		print_char(va_list args);
/*int		print_str(va_list args);
int		print_int(va_list args);
int		print_uint(va_list args);
int		print_hex(va_list args, char ch);
int		print_ptr(va_list args);
int		print_percent(va_list args);*/

/* io 
int		put_char_len(char c);
int		put_str_len(char *s);
int		putnbr_base(unsigned long n, char *base);*/

#endif