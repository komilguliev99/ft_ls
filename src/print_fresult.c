/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_fresult.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcapers <dcapers@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 21:20:20 by ds107             #+#    #+#             */
/*   Updated: 2020/03/06 22:57:26 by dcapers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void			time_format(struct tm *t)
{
	time_t			rawt;
	struct tm		*now;

	time (&rawt);
	now = localtime(&rawt);
	print_time(now);
	print_time(t);
}

static void			print_ff(t_file *f, int size)
{
	ft_printf("%c%-*s %d %-*s %-*s ", f->type, size, ft_strmode(f->mode),
		f->nlink, size, f->u_name, size, f->gr_name);
	ft_printf("%8d ", f->byte_size);
	time_format(f->last_d);
	ft_printf("%-*s  ==> ", size, f->name);
	print_time(f->last_d);
}

void			long_format(t_file *file, int lf, int size)
{
		while (file)
		{
			if (lf)
				print_ff(file, size);
			else
				ft_printf("%s ", file->name);
			file = file->next;
		}
}
