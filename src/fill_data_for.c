/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_data_for.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcapers <dcapers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 16:40:35 by dcapers           #+#    #+#             */
/*   Updated: 2020/03/11 12:36:42 by dcapers          ###   ########.fr       */
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

void			set_user_group(t_file *f, uid_t uid, gid_t gid)
{
	struct passwd	*usr;
	struct group	*gr;

	if ((usr = getpwuid(uid)) && usr->pw_name)
		f->u_name = ft_strdup(usr->pw_name);
	else
		f->u_name = ft_itoa((long long int)uid);
	if ((gr = getgrgid(gid)) && gr->gr_name)
		f->gr_name = ft_strdup(gr->gr_name);
	else
		f->gr_name = ft_itoa((long long int)gid);
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
		f->ctime = ft_strdup(ctime((const time_t *)&st.st_mtime));
		f->last_d = (long long int)st.st_mtime;
		f->byte_size = (long long int)st.st_size;
		f->blocks = (long long int)st.st_blocks;
		f->mode = (int)st.st_mode;
		f->nlink = st.st_nlink;
		set_user_group(f, st.st_uid, st.st_gid);
		sm->blocks += st.st_blocks;
		set_attr(buff, f);
		if (f->type == 'l' && sm->flags['l'])
			reset_name(f, buff);
	}
	else
		ft_printf("ERROR: %s\n", strerror(errno));
}
