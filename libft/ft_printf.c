/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcapers <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 22:24:12 by dcapers           #+#    #+#             */
/*   Updated: 2020/02/27 22:24:13 by dcapers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			handle_types(t_state *st, char type)
{
	if (type == 'd' || type == 'i')
		return (handle_di(st));
	else if (type == 'x' || type == 'X')
		return (handle_x(st));
	else if (type == 'u')
		return (handle_u(st));
	else if (type == 'o')
		return (handle_o(st));
	else if (type == 's')
		return (handle_string(st));
	else if (type == 'c')
		return (handle_char(st));
	else
		return (handle_point(st));
}

int			handle_percent(t_state *st)
{
	if (st->fm->min_w > 1 && (!st->fm->flags['0'] || st->fm->flags['-']))
		st->space_len = st->fm->min_w - 1;
	else if (st->fm->min_w > 1)
		st->zero_len = st->fm->min_w - 1;
	if (!st->fm->flags['-'])
		ft_putchar_cnt(' ', st->space_len);
	ft_putchar_cnt('0', st->zero_len);
	ft_putchar('%');
	if (st->fm->flags['-'])
		ft_putchar_cnt(' ', st->space_len);
	return (st->fm->min_w > 1 ? st->fm->min_w : 1);
}

void		handle_argument(t_state *st, int *cnt)
{
	if (st->fm->type == '%')
		*cnt += handle_percent(st);
	else
	{
		set_argument(st, st->fm->type, st->fm->modfr);
		if (st->fm->type == 'f')
			*cnt += handle_float(st);
		else
			*cnt += handle_types(st, st->fm->type);
	}
	reset_state(st, 1);
}

int			ft_printf(const char *form, ...)
{
	t_state		*st;
	int			cnt;

	cnt = 0;
	if (!(st = initialize_state()))
		return (-1);
	va_start(st->ap, form);
	while (*form)
	{
		if (*form == '%' && set_format(st, &form))
			handle_argument(st, &cnt);
		else
		{
			cnt += (*form != '\0');
			ft_putchar(*form);
		}
		form += (*form != '\0');
	}
	va_end(st->ap);
	clear_memory(st);
	return (cnt);
}
