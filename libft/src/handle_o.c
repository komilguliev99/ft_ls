/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_o.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcapers <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 22:26:01 by dcapers           #+#    #+#             */
/*   Updated: 2020/02/27 22:26:02 by dcapers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int			print_right(t_state *st, int len)
{
	int		flag;

	flag = (st->fm->flags['#'] && st->fm->prec <= len && !st->zero_len);
	ft_putchar_cnt(' ', st->space_len);
	if (flag)
		ft_putchar('0');
	ft_putchar_cnt('0', st->zero_len);
	if (len)
		ft_putstr(st->arg);
	return (st->space_len + st->zero_len + len + flag);
}

static int			print_left(t_state *st, int len)
{
	int		flag;

	flag = (st->fm->flags['#'] && st->fm->prec <= len && !st->zero_len);
	if (flag)
		ft_putchar('0');
	ft_putchar_cnt('0', st->zero_len);
	if (len)
		ft_putstr(st->arg);
	ft_putchar_cnt(' ', st->space_len);
	return (st->space_len + st->zero_len + len + flag);
}

static void			set_params(t_state *st, int *len, int flag)
{
	int		prec;
	int		width;

	prec = st->fm->prec;
	width = st->fm->min_w;
	if (st->arg[0] == '0' && (st->fm->flags['#'] || st->fm->prec == 0))
		*len = 0;
	if (width > *len && st->fm->flags['0'] && !st->fm->flags['-'] && prec == -1)
		st->zero_len = width - *len;
	else if (prec > *len)
		st->zero_len = prec - *len;
	if (width > *len && *len > prec && !st->zero_len)
		st->space_len = width - *len - (flag && !st->zero_len);
	else if (width > *len && *len <= prec)
		st->space_len = width - prec - (flag && !st->zero_len);
	st->space_len = st->space_len > 0 ? st->space_len : 0;
	st->zero_len = st->zero_len > 0 ? st->zero_len : 0;
}

int					handle_o(t_state *st)
{
	int		len;
	int		flag;

	len = ft_strlen(st->arg);
	flag = (st->fm->flags['#'] && st->fm->prec <= len);
	set_params(st, &len, flag);
	if (st->fm->flags['-'])
		return (print_left(st, len));
	else
		return (print_right(st, len));
}
