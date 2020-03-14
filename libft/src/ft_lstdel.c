/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcapers <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 18:47:02 by dcapers           #+#    #+#             */
/*   Updated: 2019/09/17 13:00:08 by dcapers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *,
			size_t))
{
	t_list	*cur;
	t_list	*lst;

	if (!del)
		return ;
	lst = *alst;
	while (lst)
	{
		cur = lst;
		lst = lst->next;
		del(cur->content, cur->content_size);
		free(cur);
	}
	*alst = NULL;
}
