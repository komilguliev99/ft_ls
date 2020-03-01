/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcapers <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 22:28:50 by dcapers           #+#    #+#             */
/*   Updated: 2020/02/27 22:28:52 by dcapers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int			print_right(t_state *st, int len)
{
	ft_putchar_cnt(' ', st->space_len);
	ft_putstr(st->arg);
	return (st->space_len + len);
}

static int			print_left(t_state *st, int len)
{
	ft_putstr(st->arg);
	ft_putchar_cnt(' ', st->space_len);
	return (st->space_len + len);
}

static void			set_params(t_state *st, int len)
{
	if (st->fm->min_w > len)
		st->space_len = st->fm->min_w - len;
}

int					handle_string(t_state *st)
{
	int		len;

	if (st->fm->prec > -1 && st->fm->prec < st->arg_len)
		st->arg[st->fm->prec] = '\0';
	len = ft_strlen(st->arg);
	set_params(st, len);
	if (st->fm->flags['-'])
		return (print_left(st, len));
	else
		return (print_right(st, len));
}
