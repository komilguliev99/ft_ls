/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_format.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcapers <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 22:28:06 by dcapers           #+#    #+#             */
/*   Updated: 2020/02/27 22:28:08 by dcapers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		set_dynamic_w(t_state *st, char **str)
{
	char		*ptr;

	ptr = *str;
	if (ft_isdigit(*ptr))
	{
		st->fm->min_w = ft_atoi(ptr);
		while (ft_isdigit(*ptr))
			ptr++;
	}
	else if (*ptr == '*')
	{
		st->fm->min_w = va_arg(st->ap, int);
		ptr++;
	}
	*str = ptr;
}

static void		set_dynamic_p(t_state *st, char **str)
{
	char		*ptr;

	ptr = *str;
	if (*ptr == '.')
	{
		if (*(++ptr) == '*')
		{
			st->fm->prec = va_arg(st->ap, int);
			ptr++;
		}
		else
		{
			st->fm->prec = ft_atoi(ptr);
			while (ft_isdigit(*ptr))
				ptr++;
		}
	}
	*str = ptr;
}

int				set_format(t_state *st, const char **str)
{
	char		*ptr;

	ptr = (char *)*str + 1;
	while (is_flag(*ptr))
		set_flag(st->fm->flags, *ptr++);
	set_dynamic_w(st, &ptr);
	set_dynamic_p(st, &ptr);
	while (is_modifier(*ptr))
		if (!st->fm->modfr)
			set_modifier(st->fm, ptr);
		else
			ptr++;
	*str = ptr;
	if (!is_type(*ptr))
		return (0);
	st->fm->type = *ptr;
	return (1);
}
