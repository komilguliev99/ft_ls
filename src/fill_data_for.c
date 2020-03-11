/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_data_for.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcapers <dcapers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 16:40:35 by dcapers           #+#    #+#             */
/*   Updated: 2020/03/11 10:35:40 by dcapers          ###   ########.fr       */
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
		name[bytes + 4] = '\0';
		while (--bytes >= 0)
			name[bytes + 4] = name[bytes];
		name[0] = ' ';
		name[1] = '-';
		name[2] = '>';
		name[3] = ' ';
		link = f->name;
		f->name = ft_strjoin(f->name, name);
		free(link);
	}
}

void			set_attr(char *path, t_file *f)
{
	char	attr[512];
	void	*tmp;

	tmp = NULL;
	settype(f);
	if (listxattr(path, attr, 512, XATTR_NOFOLLOW) > 0)
		f->attr = '@';
	else if ((tmp = acl_get_link_np(path, ACL_TYPE_EXTENDED)))
	{
		acl_free(tmp);
		f->attr = '+';
	}
	else
		f->attr = ' ';
}

void			fill_data_for(t_file *f, char *path, t_main *sm)
{
	char			buff[1024];
	struct stat		st;

	buff[0] = '\0';
	if (path)
		fill_str(buff, path, 0);
	fill_str(buff, f->name, -1);
	errno = 0;
	if (!lstat(buff, &st))
	{
		f->ctime = ft_strdup(ctime((const time_t *)&st.st_ctime));
		f->last_d = (long long int)st.st_ctime;
		f->byte_size = (long long int)st.st_size;
		f->blocks = (long long int)st.st_blocks;
		f->mode = (int)st.st_mode;
		f->nlink = st.st_nlink;
		f->u_name = ft_strdup(getpwuid(st.st_uid)->pw_name);
		f->gr_name = ft_strdup(getgrgid(st.st_gid)->gr_name);
		sm->blocks += st.st_blocks;
		set_attr(buff, f);
		if (f->type == 'l' && sm->flags['l'])
			reset_name(f, buff);
	}
	else
		ft_printf("ERROR: %s\n", strerror(errno));
}
