/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_filesort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcapers <dcapers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 11:53:39 by dcapers           #+#    #+#             */
/*   Updated: 2020/03/07 19:50:33 by dcapers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void			swap_file(t_file **it, t_file **head)
{
	t_file		*sw;

	sw = (*it)->next->next;
	(*it)->next->next = (*it);
	if ((*it)->prev != (*it)->next)
		(*it)->next->prev = (*it)->prev;
	else
		(*it)->next->prev = (*it);
	if ((*it)->prev != (*head)->prev)
		(*it)->prev->next = (*it)->next;
	(*it)->prev = (*it)->next;
	if (*it == *head)
		*head = (*it)->next;
	(*it)->next = sw;
	if (sw)
		sw->prev = (*it);
}

void				ft_filesort(t_file **f, int (*cmp)(t_file *f1, t_file *f2))
{
	t_file		*it;
	int			flag;

	flag = 1;
	while (flag)
	{
		flag = 0;
		it = *f;
		while (it && it->next)
			if (!cmp(it, it->next))
			{
				swap_file(&it, f);
				flag = 1;
			}
			else
				it = it->next;
	}
}
