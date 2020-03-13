/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_data_for.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcapers <dcapers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 16:40:35 by dcapers           #+#    #+#             */
/*   Updated: 2020/03/13 18:31:09 by dcapers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		settype(t_file *f, size_t mode)
{
	if (S_ISLNK(mode))
		f->type = 'l';
	else if (S_ISDIR(mode))
		f->type = 'd';
	else if (S_ISBLK(mode))
		f->type = 'b';
	else if (S_ISCHR(mode))
		f->type = 'c';
	else if (S_ISFIFO(mode))
		f->type = 'p';
	else if (S_ISSOCK(mode))
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
		if (link)
			free(link);
	}
}

void			set_attr(char *path, t_file *f, size_t mode)
{
	char	attr[512];
	void	*tmp;

	tmp = NULL;
	settype(f, mode);
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

static void	set_mode(size_t mode, char *buff)
{
	buff[0] = (mode & S_IRUSR) != 0 ? 'r' : '-';
	buff[1] = (mode & S_IWUSR) != 0 ? 'w' : '-';
	if ((mode & S_ISUID) != 0)
		buff[2] = (mode & S_IXUSR) != 0 ? 's' : 'S';
	else
		buff[2] = (mode & S_IXUSR) != 0 ? 'x' : '-';
	buff[3] = (mode & S_IRGRP) != 0 ? 'r' : '-';
	buff[4] = (mode & S_IWGRP) != 0 ? 'w' : '-';
	if ((mode & S_ISGID) != 0)
		buff[5] = (mode & S_IXGRP) != 0 ? 's' : 'S';
	else
		buff[5] = (mode & S_IXGRP) != 0 ? 'x' : '-';
	buff[6] = (mode & S_IROTH) != 0 ? 'r' : '-';
	buff[7] = (mode & S_IWOTH) != 0 ? 'w' : '-';
	if ((mode & S_ISVTX) != 0)
		buff[8] = (mode & S_IXOTH) != 0 ? 't' : 'T';
	else
		buff[8] = (mode & S_IXOTH) != 0 ? 'x' : '-';
	buff[9] = '\0';
}

static void		set_date(t_file *f, char *s, t_main *st)
{
	char		**av;
	int			len;

	av = ft_strsplit(s, ' ');
	if (!av)
		return ;
	len = ft_strlen(av[4]) - 1;
	av[4][len] = '\0';
	if (len + 1 > st->fm.year_block)
		st->fm.year_block = len + 1;
	f->date->year = av[4];
	f->date->time = av[3];
	f->date->mon = av[1];
	f->date->date = av[2];
	free(av[0]);
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
		set_date(f, ctime(&st.st_mtime), sm);
		f->last_d = (long long int)st.st_mtime;
		f->byte_size = (long long int)st.st_size;
		f->blocks = (long long int)st.st_blocks;
		set_mode(st.st_mode, f->mode);
		f->nlink = st.st_nlink;
		set_user_group(f, st.st_uid, st.st_gid);
		sm->blocks += st.st_blocks;
		set_attr(buff, f, st.st_mode);
		if (f->type == 'l' && sm->flags['l'])
			reset_name(f, buff);
	}
	else
		ft_printf("ERROR: %s\n", strerror(errno));
}
