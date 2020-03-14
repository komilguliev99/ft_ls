/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_point.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcapers <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 22:25:45 by dcapers           #+#    #+#             */
/*   Updated: 2020/02/27 22:25:47 by dcapers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void			ft_putarg(t_state *st, int len)
{
	ft_putstr("0x");
	ft_putchar_cnt('0', st->zero_len);
	if (len)
		ft_putstr(st->arg);
}

static int			print_right(t_state *st)
{
	ft_putchar_cnt(' ', st->space_len);
	ft_putarg(st, st->arg_len);
	return (st->space_len + st->zero_len + st->arg_len + 2);
}

static int			print_left(t_state *st)
{
	ft_putarg(st, st->arg_len);
	ft_putchar_cnt(' ', st->space_len);
	return (st->space_len + st->zero_len + st->arg_len + 2);
}

int					handle_point(t_state *st)
{
	int prec;

	prec = st->fm->prec;
	if (st->arg[0] == '0' && st->fm->prec == 0)
		st->arg_len = 0;
	if (prec != -1 && st->arg_len < prec)
		st->zero_len += prec - st->arg_len;
	else if (prec == -1 && st->fm->min_w > st->arg_len && st->fm->flags['0']
			&& !st->fm->flags['-'])
		st->zero_len = st->fm->min_w - st->arg_len - 2;
	if (st->fm->min_w > st->arg_len && st->arg_len >= st->fm->prec
			&& !st->zero_len)
		st->space_len = st->fm->min_w - st->arg_len - 2;
	if (st->fm->min_w > st->arg_len && prec >= st->arg_len)
		st->space_len = st->fm->min_w - prec - 2;
	st->space_len = st->space_len > 0 ? st->space_len : 0;
	st->zero_len = st->zero_len > 0 ? st->zero_len : 0;
	if (st->fm->flags['-'])
		return (print_left(st));
	else
		return (print_right(st));
}
