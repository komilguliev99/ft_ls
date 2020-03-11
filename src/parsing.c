/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcapers <dcapers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 14:41:55 by dcapers           #+#    #+#             */
/*   Updated: 2020/03/11 16:06:16 by dcapers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int			is_lsflag(char c)
{
	if (c == 'l' || c == 'R' || c == 'a' || c == 'r' || c == 't' || c == '1'
		|| c == '-')
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
	int				j;
	t_lst			*lst;
	t_file			*file;
	struct stat		buff;

	j = 1;
	while (j < ac && av[j][0] == '-')
	{
		set_flags(st, av[j] + 1);
		j++;
		if (av[j - 1][1] == '-')
			break ;
	}
	st->arg_cnt = 0;
	ft_strsort(av + j, ac - j);
	while (j < ac)
	{
		if (!lstat(av[j], &buff))
		{
			file = create_file(av[j], S_ISDIR(buff.st_mode) ? 'd' : '-');
			file->name = av[j];
			fill_data_for(file, NULL, st);
			if (S_ISDIR(buff.st_mode))
				add_file(&st->dirs, file);
			else
				add_file(&st->files, file);
			st->arg_cnt++;
		}
		else
			add_lst(&st->not_exist, create_lst(av[j], 0));
		j++;
	}
	handle_lsflags(st, &st->dirs);
	handle_lsflags(st, &st->files);
	lst = st->not_exist;
	while (lst)
	{
		ft_printf("ls: %s: %s\n", lst->data, strerror(errno));
		lst = lst->next;
	}
}
