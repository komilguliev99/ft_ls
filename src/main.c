/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcapers <dcapers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 17:04:54 by ds107             #+#    #+#             */
/*   Updated: 2020/03/04 17:50:22 by dcapers          ###   ########.fr       */
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

void	read_last(t_file *last, char *path)
{
	char	buff[2048];
	DIR		*dir;

	buff[0] = '\0';
	while (last)
	{
		fill_str(buff, path, 0);
		fill_str(buff, last->name, -1);
		if ((dir = opendir(last->name)) || (dir = opendir(buff)))
			read_dir(dir, buff);
		last = last->next;
	}
}

void	read_dir(DIR *dir, char *path)
{
	struct dirent	*buff;
	t_file			*file;
	t_file			*last;
	t_file			*new;

	last = NULL;
	ft_printf("%s:\n", path);
	while ((buff = readdir(dir)))
	{
		if (buff->d_name[0] != '.')
		{
			new = create_file(buff->d_name, buff->d_type);
			fill_data_for(new, path);
			add_file(&file, new);
			if (buff->d_type == 4)
				add_file(&last, new);
			buff = NULL;
		}
	}
	print_files(file, 0);
	ft_putstr("\n");
	if (last)
		read_last(last, path);
	closedir(dir);
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
			read_dir(dir, st->args[i]);
		i++;
	}
}

int		main(int ac, char **av)
{
	t_main		*st;

	st = create_main();
	parsing(st, av, ac);
	// print_files(st->f, 0);
	ft_strsort(st->args, st->arg_cnt);
	file_list(st);
	return (0);
}
