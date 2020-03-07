/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_lsflags.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcapers <dcapers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 11:46:47 by ds107             #+#    #+#             */
/*   Updated: 2020/03/07 19:54:46 by dcapers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		handle_lsflags(t_main *st, t_file **f)
{
	int		(*cmp)(t_file *f1, t_file *f2);

	if (st->flags['r'] && st->flags['t'])
		cmp = &sort_descn_time;
	else if (st->flags['t'])
		cmp = &sort_ascn_time;
	else if (st->flags['r'])
		cmp = &sort_desc_name;
	else
		cmp = &sort_asc_name;
	ft_filesort(f, cmp);
	long_format(st->blocks, *f, st->flags['l'], st->block_sz);
}
