/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcapers <dcapers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 15:41:10 by dcapers           #+#    #+#             */
/*   Updated: 2020/03/14 18:48:09 by dcapers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_file			*create_file(char *name, char type)
{
	t_file		*file;

	if (!(file = (t_file *)malloc(sizeof(t_file))))
		exit(EXIT_FAILURE);
	if (!(file->date = (t_date *)malloc(sizeof(t_date))))
		exit(EXIT_FAILURE);
	file->name = ft_strdup(name);
	file->type = type;
	file->attr = 0;
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

void			print_files(t_file *file, int rev, int size)
{
	t_file		*first;

	if (!rev)
		while (file)
		{
			ft_printf("%*s  ", size, file->name);
			file = file->next;
		}
	else
	{
		first = file;
		while (file->prev != first)
		{
			ft_printf("%*s  ", size, file->name);
			file = file->prev;
		}
		ft_printf("%*s  ", size, file->name);
	}
	ft_putchar('\n');
}

void			clear_files(t_file **f)
{
	t_file		*del;

	if (!f || !*f)
		return ;
	while (*f)
	{
		del = *f;
		*f = (*f)->next;
		if (del->name)
			free(del->name);
		if (del->u_name)
			free(del->u_name);
		if (del->gr_name)
			free(del->gr_name);
		clear_date(del->date);
		free(del);
	}
}
