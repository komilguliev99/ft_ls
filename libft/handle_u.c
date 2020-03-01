/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_u.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcapers <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 22:27:22 by dcapers           #+#    #+#             */
/*   Updated: 2020/02/27 22:27:27 by dcapers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int			print_right(t_state *st, int len)
{
	ft_putchar_cnt(' ', st->space_len);
	ft_putchar_cnt('0', st->zero_len);
	if (len)
		ft_putstr(st->arg);
	return (st->space_len + st->zero_len + len);
}

static int			print_left(t_state *st, int len)
{
	ft_putchar_cnt('0', st->zero_len);
	if (len)
		ft_putstr(st->arg);
	ft_putchar_cnt(' ', st->space_len);
	return (st->space_len + st->zero_len + len);
}

static void			set_params(t_state *st, int *len)
{
	int		prec;

	prec = st->fm->prec;
	if (prec != -1 && *len < prec)
		st->zero_len += prec - *len;
	else if (prec == -1 && st->fm->min_w > *len && st->fm->flags['0']
			&& !st->fm->flags['-'])
		st->zero_len = st->fm->min_w - *len;
	if (st->arg[0] == '0' && st->fm->prec == 0)
	{
		*len -= 1;
		st->space_len = st->fm->min_w;
	}
	if (st->fm->min_w > *len && *len >= st->fm->prec && !st->zero_len)
		st->space_len = st->fm->min_w - *len;
	if (st->fm->min_w > *len && prec >= *len)
		st->space_len = st->fm->min_w - prec;
	st->space_len = st->space_len > 0 ? st->space_len : 0;
	st->zero_len = st->zero_len > 0 ? st->zero_len : 0;
}

int					handle_u(t_state *st)
{
	int		len;

	len = ft_strlen(st->arg);
	set_params(st, &len);
	if (st->fm->flags['-'])
		return (print_left(st, len));
	else
		return (print_right(st, len));
}
