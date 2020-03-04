/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcapers <dcapers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 14:41:55 by dcapers           #+#    #+#             */
/*   Updated: 2020/03/03 17:15:28 by dcapers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int			is_lsflag(char c)
{
	if (c == 'l' || c == 'R' || c == 'a' || c == 'r' || c == 't')
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
			ft_printf("Wrong flag: -%c\n", *arg);
			exit (0);
		}
		
}

void			parsing(t_main *st, char **av, int ac)
{
	int				i;
	struct stat		buff;

	i = 1;
	while (i < ac)
		if (av[i++][0] == '-')
			set_flags(st, av[i - 1] + 1);
		else
			st->arg_cnt++;
	if (!(st->args = (char **)malloc(sizeof(char *) * (st->arg_cnt + 1))))
		exit (0);
	i = 0;
	while (st->arg_cnt && ac-- > 1)
	{
		if (av[ac][0] != '-')
			st->args[i] = av[ac];
		if (av[ac][0] != '-' && stat(st->args[i++], &buff))
		{
			st->error = 1;
			ft_printf("%s: %s: - %s", av[0], st->args[i - 1], strerror(errno));
		}
	}
	st->args[st->arg_cnt] = NULL;
	if (st->error)
		exit (0);
}