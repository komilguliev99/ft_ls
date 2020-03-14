/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcapers <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 22:24:56 by dcapers           #+#    #+#             */
/*   Updated: 2020/02/27 22:24:57 by dcapers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int					handle_char(t_state *st)
{
	if (st->fm->min_w > 1)
		st->space_len = st->fm->min_w - 1;
	if (st->fm->flags['-'])
	{
		ft_putchar(st->arg[0]);
		ft_putchar_cnt(' ', st->space_len);
		return (st->space_len + 1);
	}
	else
	{
		ft_putchar_cnt(' ', st->space_len);
		ft_putchar(st->arg[0]);
		return (st->space_len + 1);
	}
}
