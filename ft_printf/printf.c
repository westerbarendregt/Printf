/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   printf.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: wbarendr <wbarendr@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/25 15:31:42 by wbarendr       #+#    #+#                */
/*   Updated: 2019/12/04 20:01:45 by wbarendr      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

void	found_type(const char **s, va_list *args, t_flags *flags, int *co)
{
	if (flags->dot == 1)
		flags->zero = ' ';
	if ((*s)[0] == 'c')
		ft_char(args, flags, co);
	else if ((*s)[0] == 's')
		ft_string(args, flags, co);
	else if ((*s)[0] == 'd')
		ft_digit(args, flags, co);
	else if ((*s[0] == '%'))
		ft_percentage(flags, co);
	else if ((*s)[0] == 'i')
		ft_digit(args, flags, co);
	else if ((*s)[0] == 'u')
		ft_unsigned(args, flags, co);
	else if ((*s)[0] == 'x')
		ft_hexa(args, flags, co);
	else if ((*s)[0] == 'X')
		ft_hexa_cap(args, flags, co);
	else if ((*s)[0] == 'p')
		ft_pointer(args, flags, co);
	(*s)++;
}

void	find_flags(const char **s, t_flags *flags)
{
	if ((*s)[0] == '0')
		flags->zero = '0';
	else if ((*s)[0] == '-')
		flags->minus = 1;
	else if ((*s)[0] == ' ')
		flags->space = 1;
	else if ((*s)[0] == '+')
		flags->plus = 1;
	if ((*s)[0] == 'l' && (*s)[1] != 'l')
		flags->l = 1;
	if ((*s)[0] == 'l' && (*s)[1] == 'l')
		flags->ll = 1;
	else if ((*s)[0] == 'h' && (*s)[1] != 'h')
		flags->h = 1;
	else if ((*s)[0] == 'h' && (*s)[1] == 'h')
		flags->hh = 1;
	if ((**s == 'h' && (*s)[1] == 'h') || (**s == 'l' && (*s)[1] == 'l'))
		(*s)++;
	if ((*s)[0] == '*')
		flags->star = 1;
	else if ((*s)[0] == '#')
		flags->hash = 1;
}

void	get_star(const char **s, va_list *args, t_flags *flags, int *co)
{
	if (**s == 0)
		return ;
	if (flags->star == 1)
	{
		flags->num = va_arg(*args, int);
		if (flags->num < 0)
		{
			flags->minus = 1;
			flags->num = flags->num * -1;
		}
	}
	if (flags->stardot == 1)
		flags->dotnum = va_arg(*args, int);
	found_type(s, args, flags, co);
}

void	found_percentage(const char **s, va_list *args, t_flags *flags, int *co)
{
	while (find_type((*s)[0]))
	{
		find_flags(s, flags);
		if ((*s)[0] >= '0' && (*s)[0] <= '9')
		{
			flags->num = ft_atoi(*s);
			while ((*s)[1] >= '0' && (*s)[1] <= '9')
				(*s)++;
		}
		else if (*s[0] == '.')
		{
			flags->dot = 1;
			if ((*s)[1] == '*' || ((*s)[1] >= '0' && (*s)[1] <= '9'))
				(*s)++;
			if ((*s)[0] == '*')
				flags->stardot = 1;
			else if ((*s)[0] >= '0' && (*s)[0] <= '9')
				flags->dotnum = ft_atoi(*s);
			while ((*s)[1] >= '0' && (*s)[1] <= '9')
				(*s)++;
		}
		(*s)++;
	}
	get_star(s, args, flags, co);
}

int		ft_printf(const char *s, ...)
{
	va_list		args;
	t_flags		flags;
	int			co;

	va_start(args, s);
	co = 0;
	flags = ft_flags();
	va_start(args, s);
	while (*s)
	{
		if (*s == '%')
		{
			s++;
			found_percentage(&s, &args, &flags, &co);
		}
		else
		{
			ft_putchar((char)s[0]);
			co++;
			s++;
		}
		flags = ft_flags();
	}
	va_end(args);
	return (co);
}
