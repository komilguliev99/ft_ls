/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_flags.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcapers <dcapers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/14 14:58:39 by dcapers           #+#    #+#             */
/*   Updated: 2020/03/14 17:05:04 by dcapers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			is_lsflag(char c)
{
	if (c == 'l' || c == 'R' || c == 'a' || c == 'r' || c == 't' || c == '1'
	|| c == 'd' || c == 'u' || c == 'U' || c == 'S')
		return (1);
	return (0);
}

void		set_flags(t_main *st, char *arg)
{
	while (*arg)
		if (is_lsflag(*arg))
			st->flags[(int)*arg++] = 1;
		else
		{
			ft_putstr_fd("/bin/ls: illegal option -- ", 2);
			ft_putchar_fd(*arg, 2);
			ft_putstr_fd("\nusage: ls [-ABCFGHLOPRSTUWab", 2);
			ft_putstr_fd("cdefghiklmnopqrstuwx1] [file ...]\n", 2);
			exit(EXIT_FAILURE);
		}
}
