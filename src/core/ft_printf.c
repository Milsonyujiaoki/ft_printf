#include "ft_printf.h"
# include "libft.h"
#include <stdarg.h>

/* ft_printf("Olá %s, você tem %d anos", "João", 30)
         ↓
percorre char a char a string fmt
  - se não é '%' → escreve o char diretamente, conta +1
  - se é '%' → avança para o próximo char (o especificador)
    - lê o especificador ('s', 'd', etc.)
    - chama a função certa passando va_arg
    - conta os chars escritos
retorna o total de chars escritos */


int	ft_printf(const char *fmt, ...)
{
    va_list	args;
    int		result;
    int     i;

    result = 0;

    va_start(args, fmt);
    for(i=0; fmt[i] != '\0'; i++)
    {
        if (fmt[i] != '%')
        {
            ft_putchar_fd(fmt[i], 1);
            result++;
            
        }else
        {
            i++;
            t_format format;
            parse_format(fmt + i, &format);
            int conv_len = dispatch_conversion(&format, args);
            if (conv_len < 0)
                return (-1);
            result += conv_len;
            // Avança i para pular o formato completo
            while (fmt[i] && !ft_strchr("cspdiuxX%", fmt[i]))
                i++;
        }
    }
    va_end(args);
    return (result);
}