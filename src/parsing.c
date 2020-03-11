/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcapers <dcapers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 14:41:55 by dcapers           #+#    #+#             */
/*   Updated: 2020/03/11 10:32:56 by dcapers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int			is_lsflag(char c)
{
	if (c == 'l' || c == 'R' || c == 'a' || c == 'r' || c == 't' || c == '1')
		return (1);
	return (0);
}

static void			set_flags(t_main *st, char *arg)
{
	while (*arg)
		if (is_lsflag(*arg))
			st->flags[(int)*arg++] = 1;
		else
		{
			ft_putstr_fd("./ft_ls: illegal option -- ", 2);
			ft_putchar_fd(*arg, 2);
			ft_putstr_fd("\nusage: ./ft_ls [-alRrt] [file ...]\n", 2);
			exit(EXIT_FAILURE);
		}
}

void				parsing(t_main *st, char **av, int ac)
{
	int				i;
	int				j;
	struct stat		buff;

	j = 1;
	while (j < ac && av[j][0] == '-')
	{
		set_flags(st, av[j] + 1);
		j++;
	}
	st->arg_cnt = ac - j;
	if (!(st->args = (char **)malloc(sizeof(char *) * (st->arg_cnt + 1))))
		exit(EXIT_FAILURE);
	i = 0;
	while (st->arg_cnt && j < ac)
		st->args[i++] = av[j++];
	i = 0;
	ft_strsort(st->args, st->arg_cnt);
	st->nreal = st->arg_cnt;
	while (i < st->arg_cnt)
		if (stat(st->args[i++], &buff) && st->nreal--)
			ft_printf("%s: %s: %s\n", av[0], st->args[i - 1], strerror(errno));
	st->args[st->arg_cnt] = NULL;
}
