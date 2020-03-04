/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_data_for.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcapers <dcapers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 16:40:35 by dcapers           #+#    #+#             */
/*   Updated: 2020/03/04 17:55:49 by dcapers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		fill_data_for(t_file *f, char *path)
{
	char			buff[1024];
	struct stat		st;

	fill_str(buff, path, 0);
	fill_str(buff, f->name, -1);
	ft_printf("%s\n", buff);
	errno = 0;
	if (!stat(buff, &st) || !lstat(buff, &st))
	{
		f->last_d = gmtime((const time_t *)&st.st_ctime);
		f->byte_size = (long long int)st.st_size;
		f->blocks = (long long int)st.st_blocks;
		f->mode = (int)st.st_mode;
		f->u_name = ft_strdup(getpwuid(st.st_uid)->pw_name);
		f->gr_name = ft_strdup(getgrgid(st.st_gid)->gr_name);
	}
	else
		ft_printf("ERROR: %s\n", strerror(errno));	
}