/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcapers <dcapers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 15:41:10 by dcapers           #+#    #+#             */
/*   Updated: 2020/03/04 17:56:50 by dcapers          ###   ########.fr       */
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

void			print_ff(t_file *f)
{
	ft_printf("%lld %lld ", f->blocks, f->byte_size);
	ft_printf("%o %s %s ", f->mode, f->u_name, f->gr_name);
	ft_printf("%s\n", f->name);
}

void			print_files(t_file *file, int rev)
{
	t_file		*first;

	if (!rev)
		while (file)
		{
			print_ff(file);
			file = file->next;
		}
	else
	{
		first = file;
		while (file->prev != first)
		{
			print_ff(file);
			file = file->prev;
		}
		print_ff(file);
	}
	ft_putchar('\n');
}
