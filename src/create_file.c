/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcapers <dcapers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 15:41:10 by dcapers           #+#    #+#             */
/*   Updated: 2020/03/14 21:59:48 by dcapers          ###   ########.fr       */
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
	file->ready = 0;
	return (file);
}

static void		add_item(t_file **f, t_file *new,
		int (*cmp)(t_file *f1, t_file *f2))
{
	t_file		*prev;
	t_file		*file;

	file = *f;
	prev = NULL;
	if (cmp(file, new))
		prev = file;
	while (prev && file->next && cmp(file->next, new))
	{
		prev = file->next;
		file = file->next;
	}
	if (prev)
	{
		new->next = prev->next;
		prev->next = new;
	}
	else
	{
		new->next = file;
		*f = new;
	}
}

void			add_file(t_file **f, t_file *new,
			int (*cmp)(t_file *f1, t_file *f2))
{
	if (!f || !new)
		return ;
	if (!*f)
		*f = new;
	else
		add_item(f, new, cmp);
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
		if (del->ready)
		{
			if (del->u_name)
				free(del->u_name);
			if (del->gr_name)
				free(del->gr_name);
			clear_date(del->date);
		}
		free(del);
	}
}
