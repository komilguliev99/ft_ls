/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcapers <dcapers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 17:05:59 by ds107             #+#    #+#             */
/*   Updated: 2020/03/04 17:56:05 by dcapers          ###   ########.fr       */
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

typedef struct				s_file
{
	char					*name;
	char					type;
	long long int			byte_size;
	long long int			blocks;
	char					*u_name;
	char					*gr_name;				
	int						mode;
	struct tm				*last_d;
	struct s_file			*next;
	struct s_file			*prev;
}							t_file;

typedef struct				s_main
{
	char					**args;
	int						arg_cnt;
	char					flags[128];
	long long int			blocks;
	int						error;
}							t_main;

char						*ft_strmode(unsigned int mode);
void						parsing(t_main *st, char **av, int ac);
t_main						*create_main(void);
void						reset_main(t_main *st);
void						print_main(t_main *st);
void						push_file(t_file **file, char *name, char type);
void						print_files(t_file *file, int rev);
void						ft_strsort(char **args, int ac);
void						add_file(t_file **file, t_file *new);
t_file						*create_file(char *name, char type);
void						read_dir(DIR *dir, char *path);
void						fill_str(char *s1, char *s2, int i);
void						fill_data_for(t_file *f, char *path);

#endif
