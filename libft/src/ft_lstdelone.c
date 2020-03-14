/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcapers <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 18:42:36 by dcapers           #+#    #+#             */
/*   Updated: 2019/09/17 13:00:37 by dcapers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list **alst, void (*del)(void *,
			size_t))
{
	t_list	*lst;

	lst = *alst;
	if (!alst || *alst == NULL || !del)
		return ;
	del(lst->content, lst->content_size);
	free(*alst);
	*alst = NULL;
}
