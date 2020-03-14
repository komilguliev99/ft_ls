/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_argument.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcapers <dcapers@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 22:28:20 by dcapers           #+#    #+#             */
/*   Updated: 2020/03/06 21:50:12 by dcapers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			set_di_arg(t_state *st, char modfr)
{
	if (modfr == 1)
		st->arg = ft_itoa_base(va_arg(st->ap, long int), 10, 0);
	else if (modfr == 2)
		st->arg = ft_itoa_base(va_arg(st->ap, long long int), 10, 0);
	else if (modfr == 3)
		st->arg = ft_itoa_base((short int)va_arg(st->ap, int), 10, 0);
	else if (modfr == 4)
		st->arg = ft_itoa_base((signed char)va_arg(st->ap, int), 10, 0);
	else
		st->arg = ft_itoa_base(va_arg(st->ap, int), 10, 0);
}

void			set_oux_arg(t_state *st, char modfr, char type, int base)
{
	if (modfr == 1)
		st->arg = ft_uitoa_base(va_arg(st->ap, long unsigned int),
				base, type == 'X');
	else if (modfr == 2)
		st->arg = ft_uitoa_base(va_arg(st->ap, long long unsigned int),
				base, type == 'X');
	else if (modfr == 3)
		st->arg = ft_uitoa_base((unsigned short int)va_arg(st->ap,
						unsigned int), base, type == 'X');
	else if (modfr == 4)
		st->arg = ft_uitoa_base((unsigned char)va_arg(st->ap, unsigned int),
				base, type == 'X');
	else
		st->arg = ft_uitoa_base(va_arg(st->ap, unsigned int),
				base, type == 'X');
}

void			set_csp_arg(t_state *st, char type)
{
	unsigned long long int		p;

	if (type == 'c')
		st->arg = ft_ctos(va_arg(st->ap, int));
	else if (type == 's')
	{
		st->arg = va_arg(st->ap, char *);
		if (st->arg == NULL)
			st->arg = ft_strdup("(null)");
		else
			st->arg = ft_strdup(st->arg);
	}
	else
	{
		p = va_arg(st->ap, unsigned long long int);
		st->arg = ft_uitoa_base(p, 16, 0);
	}
}

void			set_f_arg(t_state *st)
{
	long double		f;

	if (st->fm->modfr == 5)
		f = va_arg(st->ap, long double);
	else
		f = va_arg(st->ap, double);
	st->fm->prec = st->fm->prec == -1 ? 6 : st->fm->prec;
	st->sign = (f < 0) ? '-' : '+';
	set_float(st, f);
}

void			set_argument(t_state *st, char type, char modfr)
{
	int			base;
	int			base_in;

	if (type == 'd' || type == 'i')
		set_di_arg(st, modfr);
	else if (type == 'o' || type == 'u' || type == 'x' || type == 'X')
	{
		base_in = (type == 'u' ? 10 : 16);
		base = type == 'o' ? 8 : base_in;
		set_oux_arg(st, modfr, type, base);
	}
	else if (type == 'c' || type == 's' || type == 'p')
		set_csp_arg(st, type);
	else if (type == 'f')
		set_f_arg(st);
	set_arglen(st);
}
