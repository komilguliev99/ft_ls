/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstprint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcapers <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 13:40:23 by dcapers           #+#    #+#             */
/*   Updated: 2019/09/17 13:44:35 by dcapers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lstprint(t_list *lst)
{
	char	*content;
	size_t	sz;

	while (lst)
	{
		sz = 0;
		content = (char *)lst->content;
		while (sz < lst->content_size)
		{
			ft_putchar(content[sz]);
			sz++;
		}
		lst = lst->next;
	}
}
