/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcapers <dcapers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 17:04:54 by ds107             #+#    #+#             */
/*   Updated: 2020/03/11 15:15:14 by dcapers          ###   ########.fr       */
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
			ft_putchar('\n');
			print_fullpath(buff);
			if ((dir = opendir(buff)))
			{
				st->blocks = 0;
				read_dir(dir, buff, st);
			}
			else if (errno == EACCES)
				ft_printf("ls: %s: %s\n", f->name, strerror(errno));
		}
		f = f->next;
	}
	clear_files(&f);
}

int		read_dir(DIR *dir, char *path, t_main *st)
{
	struct dirent	*buff;
	t_file			*file;
	t_file			*new;

	file = NULL;
	buff = NULL;
	update_main(st, -1, -1, -1);
	while ((buff = readdir(dir)))
	{
		if (buff->d_name[0] == '.' && !st->flags['a'])
			continue ;
		new = create_file(buff->d_name, buff->d_type);
		fill_data_for(new, path, st);
		update_main(st, ft_strlen(buff->d_name) + 3, new->byte_size, new->nlink);
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
	t_lst			*lst;
	int				i;

	i = 0;
	lst = st->files;
	while (lst && ++i)
	{
		print_ff_format(st, lst->data);
		lst = lst->next;
	}
	lst = st->dirs;
	while (lst)
	{
		errno = 0;
		if (i)
			ft_putchar('\n');
		if (st->arg_cnt > 1)
			ft_printf("%s:\n", lst->data);
		if ((dir = opendir(lst->data)) && errno == 0)
			read_dir(dir, lst->data, st);
		else if (errno == EACCES)
			ft_printf("ls: %s: %s", lst->data, strerror(errno));
		lst = lst->next;
		i++;
	}
	if (!st->arg_cnt && (dir = opendir("./")))
		read_dir(dir, NULL, st);
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
