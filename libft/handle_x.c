/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_x.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcapers <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 22:26:22 by dcapers           #+#    #+#             */
/*   Updated: 2020/02/27 22:26:24 by dcapers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int			print_pref(char type)
{
	int		l;

	l = 1;
	ft_putchar('0');
	if (type == 'x' || type == 'X')
	{
		ft_putchar(type);
		l++;
	}
	return (l);
}

static int			print_right(t_state *st, int len, int pref)
{
	int			pref_l;

	pref_l = 0;
	ft_putchar_cnt(' ', st->space_len);
	if (pref)
		pref_l = print_pref(st->fm->type);
	ft_putchar_cnt('0', st->zero_len);
	if (!(st->arg[0] == '0' && st->fm->prec != -1))
		ft_putstr(st->arg);
	return (st->space_len + st->zero_len + len + pref_l);
}

static int			print_left(t_state *st, int len, int pref)
{
	int			pref_l;

	pref_l = 0;
	if (pref)
		pref_l = print_pref(st->fm->type);
	ft_putchar_cnt('0', st->zero_len);
	if (!(st->arg[0] == '0' && st->fm->prec != -1))
		ft_putstr(st->arg);
	ft_putchar_cnt(' ', st->space_len);
	return (st->space_len + st->zero_len + len + pref_l);
}

static void			set_params(t_state *st, int len, int pref)
{
	int		prec;
	int		pref_l;

	prec = st->fm->prec;
	pref_l = 0;
	if (pref && st->fm->type != 'o')
		pref_l = 2;
	else if (pref)
		pref_l = 1;
	if (prec != -1 && len < prec)
		st->zero_len += prec - len;
	else if (prec == -1 && st->fm->min_w > len && st->fm->flags['0']
			&& !st->fm->flags['-'])
		st->zero_len = st->fm->min_w - len - pref_l;
	if (st->fm->min_w > len && len >= st->fm->prec && !st->zero_len)
		st->space_len = st->fm->min_w - len - pref_l;
	if (st->fm->min_w > len && prec >= len)
		st->space_len = st->fm->min_w - prec - pref_l;
	st->space_len = st->space_len > 0 ? st->space_len : 0;
	st->zero_len = st->zero_len > 0 ? st->zero_len : 0;
}

int					handle_x(t_state *st)
{
	int		len;
	int		pref;

	len = ft_strlen(st->arg);
	pref = 0;
	if (st->fm->flags['#'] && st->fm->type != 'u'
			&& (st->arg[0] != '0' || st->fm->type == 'o'))
		pref = 1;
	if (st->arg[0] == '0' && ((st->fm->type != 'o' && st->fm->prec != -1) ||
			(st->fm->type == 'o' && st->fm->prec == 0)))
		len--;
	set_params(st, len, pref);
	if (st->fm->flags['-'])
		return (print_left(st, len, pref));
	else
		return (print_right(st, len, pref));
}
