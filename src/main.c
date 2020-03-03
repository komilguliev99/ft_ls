/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcapers <dcapers@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 17:04:54 by ds107             #+#    #+#             */
/*   Updated: 2020/03/02 15:38:35 by dcapers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	file_list(char *path)
{
	DIR				*dir;
	struct dirent	*buff;

	if (!(dir = opendir(path)))
	{
		write(1, "Can't open!\n", 12);
		return ;
	}

	while ((buff = readdir(dir)))
	{
		if (buff->d_type == 8)
			ft_printf("%s\n", buff->d_name);	
	}
	closedir(dir);
}

int		main(int ac, char **av)
{
	t_main		*st;

	st = create_main();
	parsing(st, av, ac);
	print_main(st);
	return (0);
}
