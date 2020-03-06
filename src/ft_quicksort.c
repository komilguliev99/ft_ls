/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quicksort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcapers <dcapers@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 11:53:39 by dcapers           #+#    #+#             */
/*   Updated: 2020/03/06 21:10:54 by dcapers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void				ft_filesort(t_file **f, int (*cmp)(t_file *f1, t_file *f2))
{
	t_file		*sw;
	t_file		*it;
	int			flag;

	flag = 1;
	while (flag)
	{
		flag = 0;
		it = *f;
		while (it && it->next)
		{
			if (!cmp(it, it->next))
			{
				sw = it->next->next;
				it->next->next = it;
				if (it->prev != it->next)
					it->next->prev = it->prev;
				else
					it->next->prev = it;
				if (it->prev != (*f)->prev)
					it->prev->next = it->next;	
				it->prev = it->next;
				if (it == *f)
					*f = it->next;
				it->next = sw;
				if (sw)
					sw->prev = it;
				flag = 1;
			}
			else
				it = it->next;
		}
	}
}
