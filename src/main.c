/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcapers <dcapers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 17:04:54 by ds107             #+#    #+#             */
/*   Updated: 2020/03/14 19:29:03 by dcapers          ###   ########.fr       */
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
	while (f)
	{
		dir = NULL;
		if (f->type == 'd' && ft_strcmp(f->name, ".")
				&& ft_strcmp(f->name, ".."))
		{
			if (path)
				fill_str(buff, path, 0);
			fill_str(buff, (char *)f->name, path ? -1 : 0);
			ft_putchar('\n');
			print_fullpath(buff);
			if ((dir = opendir(buff)))
			{
				st->blocks = 0;
				read_dir(dir, buff, st);
			}
			else if (errno == EACCES)
				print_err(f->name);
		}
		f = f->next;
	}
}

int		read_dir(DIR *dir, char *path, t_main *st)
{
	struct dirent	*buff;
	t_file			*file;
	t_file			*new;

	file = NULL;
	buff = NULL;
	update_main(st, -1, -1, -1);
	update_main2(st, -1, -1);
	while ((buff = readdir(dir)))
	{
		if (buff->d_name[0] == '.' && !st->flags['a'])
			continue ;
		new = create_file(buff->d_name, buff->d_type);
		fill_data_for(new, path, st);
		add_file(&file, new, st->cmp);
	}
	print_ls_format(st, file, 0);
	closedir(dir);
	if (st->flags['R'])
		read_last(file, path, st);
	clear_files(&file);
	return (1);
}

void	file_list(t_main *st)
{
	DIR				*dir;
	t_file			*f;
	int				i;

	if (st->files)
		i = 1;
	print_ls_format(st, st->files, 1);
	f = st->dirs;
	while (f)
	{
		errno = 0;
		if (i)
			ft_putchar('\n');
		if (st->nall_arg > 1)
			ft_printf("%s:\n", f->name);
		if ((dir = opendir(f->name)) && errno == 0)
			read_dir(dir, f->name, st);
		else if (errno == EACCES)
			print_err(f->name);
		f = f->next;
		i++;
	}
	if (!st->nall_arg && (dir = opendir("./")))
		read_dir(dir, NULL, st);
}

int		main(int ac, char **av)
{
	t_main			*st;

	st = create_main();
	parsing(st, av, ac);
	file_list(st);
	clear_main(st);
	exit(EXIT_SUCCESS);
}
