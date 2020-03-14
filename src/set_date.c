/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_date.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcapers <dcapers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/14 15:15:26 by dcapers           #+#    #+#             */
/*   Updated: 2020/03/14 15:20:27 by dcapers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		set_date(t_file *f, char *s, t_main *st)
{
	char		**av;
	int			len;

	av = ft_strsplit(s, ' ');
	if (!av)
		return ;
	len = ft_strlen(av[4]) - 1;
	av[4][len] = '\0';
	if (len + 1 > st->fm.year_block)
		st->fm.year_block = len + 1;
	f->date->year = av[4];
	f->date->time = av[3];
	f->date->mon = av[1];
	f->date->date = av[2];
	free(av[0]);
}
