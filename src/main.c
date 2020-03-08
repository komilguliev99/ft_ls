/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcapers <dcapers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 17:04:54 by ds107             #+#    #+#             */
/*   Updated: 2020/03/08 14:33:39 by dcapers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	fill_str(char *s1, char *s2, int i)
{
	if (i < 0)
		i = ft_strlen(s1);
	if (i > 0 && s1[i - 1] != '/')
		s1[i++] = '/';
	while (*s2)
		s1[i++] = *s2++;
	s1[i] = '\0';
}

void	read_last(t_file *f, char *path, t_main *st)
{
	char	buff[2048];
	DIR		*dir;

	buff[0] = '\0';
	dir = NULL;
	while (f)
	{
		dir = NULL;
		if (f->type == 'd' && ft_strcmp(f->name, ".")
				&& ft_strcmp(f->name, ".."))
		{
			if (path)
				fill_str(buff, path, 0);
			fill_str(buff, (char *)f->name, path ? -1 : 0);
			if ((dir = opendir(buff)))
			{
				ft_putchar('\n');
				st->blocks = 0;
				read_dir(dir, buff, st, 1);
			}
		}
		f = f->next;
	}
	clear_files(&f);
}

int		read_dir(DIR *dir, char *path, t_main *st, int flag)
{
	struct dirent	*buff;
	t_file			*file;
	t_file			*new;
	int				block_size;

	file = NULL;
	buff = NULL;
	st->block_sz = 3;
	if (flag)
		ft_printf("%s:\n", path);
	while ((buff = readdir(dir)))
	{
		if (buff->d_name[0] == '.' && !st->flags['a'])
			continue ;
		block_size = ft_strlen(buff->d_name) + 3;
		st->block_sz = (st->block_sz < block_size ? block_size : st->block_sz);
		new = create_file(buff->d_name, buff->d_type);
		fill_data_for(new, path, st);
		add_file(&file, new);
	}
	handle_lsflags(st, &file);
	closedir(dir);
	if (st->flags['R'])
		read_last(file, path, st);
	return (1);
}

void	file_list(t_main *st)
{
	DIR				*dir;
	int				i;
	int				len;
	int				j;

	i = -1;
	j = 0;
	len = st->nreal;
	while (++i < st->arg_cnt || !len)
	{
		errno = 0;
		st->blocks = 0;
		if ((st->nreal && !(dir = opendir(st->args[i])) && errno == ENOENT) ||
			(!st->nreal && !(dir = opendir("./")) && errno == ENOENT))
			continue ;
		else if (errno == ENOTDIR)
			j += print_ff_format(st, !len++ ? "./" : st->args[i]);
		else
			j += read_dir(dir, !len++ ? NULL : st->args[i], st, st->nreal > 1);
		if (j < st->nreal)
			ft_putchar('\n');
	}
}

int		main(int ac, char **av)
{
	t_main			*st;
	struct winsize	wins;
	int				err;

	st = create_main();
	err = ioctl(1, TIOCGWINSZ, &wins);
	st->width = wins.ws_col;
	parsing(st, av, ac);
	file_list(st);
	exit(0);
}
