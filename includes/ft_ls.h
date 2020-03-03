/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcapers <dcapers@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 17:05:59 by ds107             #+#    #+#             */
/*   Updated: 2020/03/02 19:26:19 by dcapers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H
# include "unistd.h"
# include "libft.h"
# include "ft_printf.h"
# include <dirent.h>
# include <sys/stat.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>
# include <sys/types.h>
# include <sys/xattr.h>
# include <limits.h>
# include <sys/ioctl.h>
# include <errno.h>


typedef struct				s_main
{
	char					**args;
	int						arg_cnt;
	char					flags[128];
	long long int			blocks;
	int						error;
}							t_main;

typedef struct				s_file
{
	char					*name;
	char					type;
	size_t					byte_size;
	size_t					blocks;
	char					*u_name;
	char					*gr_name;				
	unsigned int			mode;
	struct tm				last_d;
	struct tm				create_d;
}							t_file;

char						*ft_strmode(unsigned int mode);
void						parsing(t_main *st, char **av, int ac);
t_main						*create_main(void);
void						reset_main(t_main *st);
void						print_main(t_main *st);

#endif
