/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcapers <dcapers@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 15:41:10 by dcapers           #+#    #+#             */
/*   Updated: 2020/03/06 21:44:33 by dcapers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_file			*create_file(char *name, char type)
{
	t_file		*file;

	if (!(file = (t_file *)malloc(sizeof(t_file))))
		exit (0);
	file->name = ft_strdup(name);
	file->type = type;
	file->next = NULL;
	file->prev = NULL;
	return (file);
}

void			add_file(t_file **file, t_file *new)
{
	if (*file && (*file)->prev)
	{
		(*file)->prev->next = new;
		new->prev = (*file)->prev;
		(*file)->prev = new;
	}
	else if (*file)
	{
		(*file)->prev = new;
		(*file)->next = new;
		new->prev = (*file);
	}
	else
		*file = new;
}

void			push_file(t_file **file, char *name, char type)
{
	t_file		*new;

	if (!file || !name)
		return ;
	new = create_file(name, type);
	if (*file && (*file)->prev)
	{
		(*file)->prev->next = new;
		new->prev = (*file)->prev;
		(*file)->prev = new;
	}
	else if (*file)
	{
		(*file)->prev = new;
		(*file)->next = new;
		new->prev = (*file);
	}
	else
		*file = new;
}

static void			print_ff(t_file *f, int size)
{
	ft_printf("%-*lld %-*lld ", size, f->blocks, size, f->byte_size);
	ft_printf("%-*o %-*s %-*s ", size, f->mode, size, f->u_name, size, f->gr_name);
	ft_printf("%-*s  ==> ", size, f->name);
	print_time(f->last_d);
}

void			print_files(t_file *file, int rev, int size)
{
	t_file		*first;

	if (!rev)
		while (file)
		{
			print_ff(file, size);
			file = file->next;
		}
	else
	{
		first = file;
		while (file->prev != first)
		{
			print_ff(file, size);
			file = file->prev;
		}
		print_ff(file, size);
	}
	ft_putchar('\n');
}
