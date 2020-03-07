/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcapers <dcapers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 17:04:54 by ds107             #+#    #+#             */
/*   Updated: 2020/03/07 16:18:15 by dcapers          ###   ########.fr       */
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
		if (f->type == 'd')
		{
			fill_str(buff, path, 0);
			fill_str(buff, (char *)f->name, -1);
			if ((dir = opendir(buff)))
				read_dir(dir, buff, st);
		}
		f = f->next;
	}
}

void	read_dir(DIR *dir, char *path, t_main *st)
{
	struct dirent	*buff;
	t_file			*file;
	t_file			*new;
	int				block_size;

	file = NULL;
	buff = NULL;
	st->block_sz = 1;
	ft_printf("%s:\n", path);
	while ((buff = readdir(dir)))
	{
		if (buff->d_name[0] == '.' && !st->flags['a'])
			continue ;
		block_size = ft_strlen(buff->d_name) + 1;
		st->block_sz = (st->block_sz < block_size ? block_size : st->block_sz);
		new = create_file(buff->d_name, buff->d_type);
		fill_data_for(new, path);
		add_file(&file, new);
	}
	handle_lsflags(st, &file);
	long_format(file, st->flags['l'], st->block_sz);
	closedir(dir);
	if (st->flags['R'])
		read_last(file, path, st);
	clear_files(&file);
}

void	file_list(t_main *st)
{
	DIR				*dir;
	int				i;

	i = 0;
	while (i < st->arg_cnt)
	{
		errno = 0;
		if (!(dir = opendir(st->args[i])) && errno == ENOENT)
		{
			write(1, "Can't open!\n", 12);
			return ;
		}
		else if (errno == ENOTDIR)
			ft_printf("%s\n", st->args[i]);
		else
			read_dir(dir, st->args[i], st);
		i++;
	}
}

int		main(int ac, char **av)
{
	t_main		*st;

	st = create_main();
	parsing(st, av, ac);
	ft_strsort(st->args, st->arg_cnt);
	file_list(st);
	exit(0);
}
