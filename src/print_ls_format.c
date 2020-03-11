/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ls_format.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcapers <dcapers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 21:20:20 by ds107             #+#    #+#             */
/*   Updated: 2020/03/11 16:14:03 by dcapers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int					diff_time(time_t t1, time_t t2)
{
	long long int			res;

	
	res = (long long int)(t1 - t2);
	if (res < 0 || res / 2629743 >= 6)
		return (7);
	return (0);
}

void				time_format(time_t t, char *s)
{
	time_t			rawt;
	char			**av;
	int				i;

	time(&rawt);
	av = ft_strsplit(s, ' ');
	ft_printf("%s %2s ", av[1], av[2], diff_time(rawt, t));
	if (diff_time(rawt, t) >= 6)
		ft_printf("%5.4s ", av[4]);
	else
	{
		i = 0;
		while (i < 5)
			ft_putchar(av[3][i++]);
		ft_putchar(' ');
	}
	i = 0;
	while (i < 6)
		free(av[i++]);
	free(av);
}

static void			print_ff(t_file *f, t_ff_size *fm)
{
	char		*mode;

	mode = ft_strmode(f->mode);
	ft_printf("%c%-.9s%c ", f->type, mode, f->attr);
	ft_printf("%*d %s  %s  ", fm->max_nlink, f->nlink, f->u_name, f->gr_name);
	ft_printf("%*d ", fm->max_size, f->byte_size);
	time_format(f->last_d, f->ctime);
	ft_printf("%s\n", f->name);
	free(mode);
}

void				print_hr_format(t_file *f, int width, int size)
{
	int			col;
	int			i;

	col = width / size;
	i = 0;
	while (f)
	{
		i++;
		ft_printf("%-*s", size, f->name);
		if (i == col)
		{
			ft_putchar('\n');
			i = 0;
		}
		f = f->next;
	}
	if (i != col)
		ft_putchar('\n');
}

void				print_ls_format(t_main *st, t_file *file,
							int flag)
{
	st->fm.max_size = ft_numcount(st->fm.max_size) - 1;
	st->fm.max_nlink = ft_numcount(st->fm.max_nlink) - 1;
	if (st->flags['l'] && !flag && file)
		ft_printf("total %lld\n", st->blocks);
	while (st->flags['l'] && file)
	{
		print_ff(file, &st->fm);
		file = file->next;
	}
	if (!st->flags['l'] && st->flags['1'])
		while (file)
		{
			ft_printf("%s\n", file->name);
			file = file->next;
		}
	else if (!st->flags['l'])
		print_hr_format(file, st->width, st->fm.blocks);
}
