/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcapers <dcapers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 12:57:10 by dcapers           #+#    #+#             */
/*   Updated: 2020/03/14 16:31:48 by dcapers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_lst			*create_lst(char *content, int allocate)
{
	t_lst		*lst;

	if (!(lst = (t_lst *)malloc(sizeof(t_lst))))
		exit(0);
	if (allocate)
		lst->data = ft_strdup(content);
	else
		lst->data = content;
	lst->allocate = allocate;
	lst->next = NULL;
	lst->prev = NULL;
	return (lst);
}

void			add_lst(t_lst **lst, t_lst *new)
{
	if (*lst && (*lst)->prev)
	{
		(*lst)->prev->next = new;
		new->prev = (*lst)->prev;
		(*lst)->prev = new;
	}
	else if (*lst)
	{
		(*lst)->prev = new;
		(*lst)->next = new;
		new->prev = (*lst);
	}
	else
		*lst = new;
}

void			push_lst(t_lst **lst, char *data)
{
	t_lst		*new;

	if (!lst || !data)
		return ;
	new = create_lst(data, 1);
	if (*lst && (*lst)->prev)
	{
		(*lst)->prev->next = new;
		new->prev = (*lst)->prev;
		(*lst)->prev = new;
	}
	else if (*lst)
	{
		(*lst)->prev = new;
		(*lst)->next = new;
		new->prev = (*lst);
	}
	else
		*lst = new;
}

void			clear_lst(t_lst **lst)
{
	t_lst		*del;

	if (!lst || !*lst)
		return ;
	while (*lst)
	{
		del = *lst;
		*lst = (*lst)->next;
		if (del->allocate && del->data)
			free(del->data);
		free(del);
	}
}
