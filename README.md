# ft_printf

## Description

42 School project — implementação customizada de `printf` construída sobre a
[libft](./libft/README.md).

## Objectives

- Learn systems programming
- Improve C skills
- Develop software engineering practices

## Dependencies

| Dependency | Localização | Compilada automaticamente |
|------------|-------------|--------------------------|
| libft      | `./libft`   | Sim (`make static/shared`) |

## Build

```bash
# Biblioteca estática (padrão)
make

# Biblioteca compartilhada
make shared

# Ambas
make static shared
```

A libft é compilada automaticamente se ainda não estiver em `libft/build/`.

## Linking

### Estática (`libftprintf.a`)

A libft é **embutida** no arquivo. Basta linkar com uma flag:

```bash
cc main.c -Ibuild/static -lftprintf -o programa
```

### Compartilhada (`libftprintf.so`)

A libft é uma **dependência dinâmica**. Ambas as `.so` precisam estar
acessíveis em runtime:

```bash
LD_LIBRARY_PATH=build/shared:libft/build/shared \
  cc main.c -Lbuild/shared -lftprintf -o programa
```

## Testes

```bash
make test
```

## Limpeza

```bash
make clean        # Remove build/ do ft_printf
make fclean       # Remove build/ do ft_printf e da libft
make libft_clean  # Remove build/ somente da libft
make re           # fclean + all
```

## Instalação

```bash
make install              # Instala em /usr/local (padrão)
make install PREFIX=~/local
make uninstall
```

## Structure

```
src/
  conversions/   # Implementações de %c %s %d %i %u %x %X %p %%
  core/          # ft_printf, parser, dispatcher
  utils/         # Helpers internos
include/
  core/          # ft_printf.h
libft/           # Dependência — libft estática e compartilhada
tests/           # Suítes de teste por conversão
docs/
```

