/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcapers <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 18:57:22 by dcapers           #+#    #+#             */
/*   Updated: 2019/09/17 13:03:32 by dcapers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *el))
{
	t_list	*cur;
	t_list	*prev;
	t_list	*head;

	prev = NULL;
	head = NULL;
	cur = lst;
	while (lst != NULL && f)
	{
		if (!(cur = (t_list *)malloc(sizeof(t_list))))
			return (NULL);
		cur = f(lst);
		if (!prev)
		{
			head = cur;
			prev = cur;
		}
		else
		{
			prev->next = cur;
			prev = prev->next;
		}
		lst = lst->next;
	}
	return (head);
}
