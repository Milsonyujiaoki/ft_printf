# include "../include/ft_printf.h"
# include <stdio.h>


int    main(void)
{
    int	ret;
    int ret2;

    ret = ft_printf("Olá, você tem anos");
    ret2 = printf("Olá, você tem anos");
    printf("\nft_printf returned: %d\n", ret);
    printf("printf returned: %d\n", ret2);
    return (0);
}