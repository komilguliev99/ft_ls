/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_state.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcapers <dcapers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 14:46:17 by ds107             #+#    #+#             */
/*   Updated: 2020/03/14 17:58:58 by dcapers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			reset_main(t_main *st)
{
	int			i;

	i = 0;
	st->files = NULL;
	st->dirs = NULL;
	st->not_exist = NULL;
	st->arg_cnt = 0;
	st->blocks = 0;
	st->error = 0;
	st->fm.g_blk = 0;
	st->fm.u_blk = 0;
	st->fm.year_block = 0;
	st->fm.max_nlink = 0;
	st->fm.max_size = 0;
	st->fm.blocks = 0;
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

void			update_main2(t_main *st, int user, int group)
{
	if (st->fm.u_blk < user)
		st->fm.u_blk = user;
	else if (user < 0)
		st->fm.u_blk = 0;
	if (st->fm.g_blk < group)
		st->fm.g_blk = group;
	else if (group < 0)
		st->fm.g_blk = 0;
}

t_main			*create_main(void)
{
	t_main		*state;

	if (!(state = (t_main *)malloc(sizeof(t_main))))
		exit(0);
	reset_main(state);
	return (state);
}

void			clear_main(t_main *sm)
{
	if (!sm)
		return ;
	clear_files(&sm->dirs);
	clear_files(&sm->files);
	clear_lst(&sm->not_exist);
	free(sm);
}
