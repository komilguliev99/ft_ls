/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcapers <dcapers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 14:41:55 by dcapers           #+#    #+#             */
/*   Updated: 2020/03/14 15:19:11 by dcapers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void				print_err(char *s)
{
	ft_putstr_fd("ls: ", 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putchar_fd('\n', 2);
}

static void			parse_flags(t_main *st, char **av, int ac, int *j)
{
	while (*j < ac && av[*j][0] == '-')
	{
		*j += 1;
		if (!ft_strcmp(av[*j - 1], "--"))
			break ;
		else if (!ft_strcmp(av[*j - 1], "-"))
		{
			*j -= 1;
			break ;
		}
		set_flags(st, av[*j - 1] + 1);
	}
	st->arg_cnt = 0;
	if (ac - *j > 1)
		ft_strsort(av + *j, ac - *j);
}

static void			parse_args(t_main *st, char *s, struct stat buff)
{
	t_file		*file;

	file = create_file(s, S_ISDIR(buff.st_mode) ? 'd' : '-');
	fill_data_for(file, NULL, st);
	if (st->flags['d'] || (file->type != 'd'
			&& !S_ISDIR(buff.st_mode)) ||
		(file->type == 'l' && st->flags['l']))
		add_file(&st->files, file);
	else
		add_file(&st->dirs, file);
	st->arg_cnt++;
}

static void			handle_ls_errors(t_lst *lst, t_main *st)
{
	st->nall_arg = st->arg_cnt;
	while (lst)
	{
		st->nall_arg++;
		print_err(lst->data);
		lst = lst->next;
	}
}

void				parsing(t_main *st, char **av, int ac)
{
	int				j;
	t_lst			*lst;
	struct stat		buff;

	j = 1;
	lst = NULL;
	parse_flags(st, av, ac, &j);
	while (j < ac)
	{
		if (!stat(av[j], &buff) || !lstat(av[j], &buff))
			parse_args(st, av[j], buff);
		else
		{
			if (av[j][0] == '\0')
			{
				print_err("fts_open");
				exit(EXIT_FAILURE);
			}
			add_lst(&st->not_exist, create_lst(av[j], 0));
		}
		j++;
	}
	handle_lsflags(st, &st->dirs);
	handle_lsflags(st, &st->files);
	handle_ls_errors(st->not_exist, st);
}
