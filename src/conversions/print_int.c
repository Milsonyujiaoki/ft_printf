#include "../../include/ft_printf.h"

static int	put_chars(char c, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		put_char_len(c);
		i++;
	}
	return (count);
}

// Função auxiliar para calcular o valor absoluto e descobrir o número de dígitos puros
static unsigned int	get_abs_and_digits(int n, int *digits)
{
	unsigned int	num;

	if (n < 0)
		num = (unsigned int)-n;
	else
		num = (unsigned int)n;
	*digits = 0;
	if (num == 0)
		*digits = 1;
	else
	{
		unsigned int temp = num;
		while (temp > 0)
		{
			(*digits)++;
			temp /= 10;
		}
	}
	return (num);
}

// Função recursiva simples para imprimir o número puro sem itoa (evita lixo de sinal)
static void	put_nbr_pure(unsigned int n)
{
	if (n >= 10)
		put_nbr_pure(n / 10);
	put_char_len((n % 10) + '0');
}

int	print_int(t_format *fmt, va_list args)
{
	int				n;
	unsigned int	num;
	int				digits;
	int				zeros;
	int				total_len;
	int				count;

	n = va_arg(args, int);
	num = get_abs_and_digits(n, &digits);
	
	// 1. Caso especial de precisão 0 com valor 0: não exibe dígitos
	if (fmt->precision == 0 && n == 0)
		digits = 0;

	// 2. Calcula quantos zeros a precisão vai exigir
	zeros = 0;
	if (fmt->precision > digits)
		zeros = fmt->precision - digits;

	// 3. Calcula o tamanho total final que o bloco numérico vai ocupar na tela
	total_len = digits + zeros;
	if (n < 0)
		total_len++; // Adiciona o espaço do sinal '-'

	count = 0;
	// 4. Largura (Width) à direita: Adiciona espaços ANTES se não houver alinhamento à esquerda
	if (!fmt->left_align && fmt->width > total_len)
		count += put_chars(' ', fmt->width - total_len);

	// 5. Imprime o sinal de menos (se for negativo)
	if (n < 0)
		put_char_len('-');

	// 6. Imprime os zeros exigidos pela precisão
	if (zeros > 0)
		put_chars('0', zeros);

	// 7. Imprime os dígitos do número (se não foi cancelado pelo caso especial do zero)
	if (digits > 0)
		put_nbr_pure(num);

	// 8. Largura (Width) à esquerda: Adiciona espaços DEPOIS se a flag '-' estiver ativa
	if (fmt->left_align && fmt->width > total_len)
		count += put_chars(' ', fmt->width - total_len);

	return (count + total_len);
}