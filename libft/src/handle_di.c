/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_di.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcapers <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 22:26:11 by dcapers           #+#    #+#             */
/*   Updated: 2020/02/27 22:26:12 by dcapers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int			print_right(t_state *st, int len, int sign)
{
	int		space;

	space = st->fm->flags[' '] && !sign;
	st->space_len -= space;
	st->zero_len -= (space && st->fm->flags['0'] && st->fm->prec == -1);
	st->space_len = st->space_len > 0 ? st->space_len : 0;
	st->zero_len = st->zero_len > 0 ? st->zero_len : 0;
	if (space)
		ft_putchar(' ');
	ft_putchar_cnt(' ', st->space_len);
	if (sign)
		ft_putchar(st->sign);
	ft_putchar_cnt('0', st->zero_len);
	if (len)
		ft_putstr(st->arg + (st->sign == '-'));
	return (st->space_len + st->zero_len + sign + len + space);
}

static int			print_left(t_state *st, int len, int sign)
{
	int		space;

	space = st->fm->flags[' '] && !sign;
	st->space_len -= space;
	st->space_len = st->space_len > 0 ? st->space_len : 0;
	st->zero_len = st->zero_len > 0 ? st->zero_len : 0;
	if (space)
		ft_putchar(' ');
	if (sign)
		ft_putchar(st->sign);
	ft_putchar_cnt('0', st->zero_len);
	if (len)
		ft_putstr(st->arg + (st->sign == '-'));
	ft_putchar_cnt(' ', st->space_len);
	return (st->space_len + st->zero_len + sign + len + space);
}

static void			set_params(t_state *st, int *len, int sign)
{
	int		prec;

	prec = st->fm->prec;
	if (prec != -1 && *len < prec)
		st->zero_len += prec - *len;
	else if (prec == -1 && st->fm->min_w > *len &&
			st->fm->flags['0'] && !st->fm->flags['-'])
		st->zero_len = st->fm->min_w - *len - sign;
	if (st->arg[0] == '0' && st->fm->prec == 0)
	{
		st->space_len = st->fm->min_w - sign;
		*len = 0;
	}
	else if (st->fm->min_w > *len && *len >= st->fm->prec && !st->zero_len)
		st->space_len = st->fm->min_w - (*len + sign);
	else if (st->fm->min_w > *len && prec >= *len)
		st->space_len = st->fm->min_w - (prec + sign);
}

int					handle_di(t_state *st)
{
	int		len;
	int		sign;

	sign = (st->fm->flags['+'] || st->arg[0] == '-');
	len = ft_strlen(st->arg) - (st->arg[0] == '-');
	set_params(st, &len, sign);
	if (st->fm->flags['-'])
		return (print_left(st, len, sign));
	else
		return (print_right(st, len, sign));
}
