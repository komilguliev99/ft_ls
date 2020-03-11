/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_state.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcapers <dcapers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 14:46:17 by ds107             #+#    #+#             */
/*   Updated: 2020/03/11 10:35:13 by dcapers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			reset_main(t_main *st)
{
	int			i;

	i = 0;
	st->args = NULL;
	st->arg_cnt = 0;
	st->blocks = 0;
	st->error = 0;
	while (i < 125)
		st->flags[i++] = 0;
	st->flags['1'] = 1;
}

void			update_main(t_main *st, int blocks, int maxsz, int maxl)
{
	if (st->fm.blocks < blocks)
		st->fm.blocks = blocks;
	else if (blocks < 0)
		st->fm.blocks = 0;
	if (st->fm.max_size < maxsz)
		st->fm.max_size = maxsz;
	else if (maxsz < 0)
		st->fm.max_size = 0;
	if (st->fm.max_nlink < maxl)
		st->fm.max_nlink = maxl;
	else if (maxl < 0)
		st->fm.max_nlink = 0;
}

t_main			*create_main(void)
{
	t_main		*state;

	if (!(state = (t_main *)malloc(sizeof(t_main))))
		exit(0);
	reset_main(state);
	return (state);
}

void			print_main(t_main *st)
{
	int			i;

	if (!st)
		return ;
	i = 0;
	ft_putchar('[');
	while (i < st->arg_cnt)
		if (i == st->arg_cnt - 1)
			ft_printf("%s", st->args[i++]);
		else
			ft_printf("%s, ", st->args[i++]);
	ft_putstr("]\nFLAGS:\n");
	i = 0;
	while (i < 128)
		if (st->flags[i++])
			ft_printf("%c ", i - 1);
	ft_putchar('\n');
}
