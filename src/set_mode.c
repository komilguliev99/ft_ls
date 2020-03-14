/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_mode.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcapers <dcapers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/14 15:15:46 by dcapers           #+#    #+#             */
/*   Updated: 2020/03/14 15:16:49 by dcapers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			set_mode(size_t mode, char *buff)
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
