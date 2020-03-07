/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_data_for.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcapers <dcapers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 16:40:35 by dcapers           #+#    #+#             */
/*   Updated: 2020/03/07 15:59:24 by dcapers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		settype(t_file *f)
{
	if (S_ISLNK(f->mode))
		f->type = 'l';
	else if (S_ISDIR(f->mode))
		f->type = 'd';
	else if (S_ISBLK(f->mode))
		f->type = 'b';
	else if (S_ISCHR(f->mode))
		f->type = 'c';
	else if (S_ISFIFO(f->mode))
		f->type = 'p';
	else if (S_ISSOCK(f->mode))
		f->type = 's';
	else
		f->type = '-';
}

static void		reset_name(t_file *f, char *path)
{
	char		name[1029];
	char		*link;
	int			bytes;

	if ((bytes = readlink(path, name, 1024)) > 0)
	{
		name[bytes + 5] = '\0';
		while (bytes >= 0)
		{
			name[bytes + 4] = name[bytes];
			bytes--;
		}
		name[0] = ' ';
		name[1] = '-';
		name[2] = '>';
		name[3] = ' ';
		link = f->name;
		f->name = ft_strjoin(f->name, name);
		free(link);
	}
}

void			fill_data_for(t_file *f, char *path)
{
	char			buff[1024];
	struct stat		st;

	fill_str(buff, path, 0);
	fill_str(buff, f->name, -1);
	errno = 0;
	if (!lstat(buff, &st))
	{
		f->ctime = ctime((const time_t *)&st.st_ctime);
		f->last_d = (long long int)st.st_ctime;
		f->byte_size = (long long int)st.st_size;
		f->blocks = (long long int)st.st_blocks;
		f->mode = (int)st.st_mode;
		f->nlink = st.st_nlink;
		f->u_name = ft_strdup(getpwuid(st.st_uid)->pw_name);
		f->gr_name = ft_strdup(getgrgid(st.st_gid)->gr_name);
		settype(f);
		if (f->type == 'l')
			reset_name(f, buff);
	}
	else
		ft_printf("ERROR: %s\n", strerror(errno));
}
