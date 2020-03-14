/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_float.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcapers <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 22:26:45 by dcapers           #+#    #+#             */
/*   Updated: 2020/02/27 22:26:46 by dcapers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void			set_params(t_state *st, int *len, int sign, int *space)
{
	int		minus;
	int		width;

	width = st->fm->min_w;
	minus = st->fm->flags['-'];
	if (width > *len && st->fm->flags['0'] && !minus)
		st->zero_len = width - *len - sign;
	else if (width > *len && st->fm->flags['0'] &&
		!st->fm->flags[' '] && !minus)
		st->zero_len = width - *len;
	else if (width > *len && sign)
		st->space_len = width - *len - sign;
	else if (width > *len && !sign)
		st->space_len = width - *len;
	if (st->fm->flags[' '] && !sign)
		*space = 1;
	if (st->zero_len)
		st->zero_len -= *space;
	if (st->space_len)
		st->space_len -= *space;
}

static void			print_farg(t_state *st)
{
	ft_putstr(st->arg + (st->sign == '-' && st->arg[0] != '0'));
	if (st->fm->prec == 0 && st->fm->flags['#'])
		ft_putchar('.');
	if (st->fm->prec > 0)
	{
		ft_putchar('.');
		ft_putstr(st->fl);
	}
}

static int			print_right(t_state *st, int len, int sign)
{
	int		space;

	space = 0;
	set_params(st, &len, sign, &space);
	ft_putchar_cnt(' ', st->space_len);
	if (sign)
		ft_putchar(st->sign);
	if (space)
		ft_putchar(' ');
	ft_putchar_cnt('0', st->zero_len);
	print_farg(st);
	return (st->space_len + st->zero_len + sign + len + space);
}

static int			print_left(t_state *st, int len, int sign)
{
	int		space;

	space = 0;
	set_params(st, &len, sign, &space);
	if (sign)
		ft_putchar(st->sign);
	if (space)
		ft_putchar(' ');
	ft_putchar_cnt('0', st->zero_len);
	print_farg(st);
	ft_putchar_cnt(' ', st->space_len);
	return (st->space_len + st->zero_len + sign + len + space);
}

int					handle_float(t_state *st)
{
	int		len;
	int		sign;

	sign = (st->sign == '-' || st->fm->flags['+']);
	len = ft_strlen(st->arg) - (st->arg[0] == '-') +
		((st->fm->prec == 0 && st->fm->flags['#']) || st->fm->prec > 0);
	if (st->fm->prec > 0)
		len += ft_strlen(st->fl);
	if (st->fm->flags['-'])
		return (print_left(st, len, sign));
	else
		return (print_right(st, len, sign));
}
