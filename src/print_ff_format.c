/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ff_format.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcapers <dcapers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 14:06:52 by dcapers           #+#    #+#             */
/*   Updated: 2020/03/11 14:42:36 by dcapers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		print_ff_format(t_main *st, char *f)
{
	t_file		*file;

	file = create_file(f, '-');
	fill_data_for(file, NULL, st);
	print_ls_format(st, file, 1);
	return (1);
}

void	print_fullpath(char *s)
{
	if (!((s[0] == '.' && s[1] == '/') || s[0] == '/'))
		ft_putstr("./");
	ft_putstr(s);
	ft_putstr(":\n");
}