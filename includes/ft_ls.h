/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcapers <dcapers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 17:05:59 by ds107             #+#    #+#             */
/*   Updated: 2020/03/14 15:16:58 by dcapers          ###   ########.fr       */
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
# include <sys/acl.h>

typedef struct				s_ff_size
{
	int						blocks;
	int						max_size;
	int						max_nlink;
	int						year_block;
	int						u_blk;
	int						g_blk;

}							t_ff_size;

typedef struct				s_date
{
	char					*year;
	char					*mon;
	char					*time;
	char					*date;
}							t_date;

typedef struct				s_lst
{
	char					*data;
	struct s_lst			*next;
	struct s_lst			*prev;
}							t_lst;

typedef struct				s_file
{
	char					*name;
	char					type;
	long long int			byte_size;
	long long int			blocks;
	char					*u_name;
	char					*gr_name;
	char					mode[10];
	int						nlink;
	char					attr;
	long long int			last_d;
	t_date					*date;
	struct s_file			*next;
	struct s_file			*prev;
}							t_file;

typedef struct				s_main
{
	t_file					*files;
	t_file					*dirs;
	t_lst					*not_exist;
	int						arg_cnt;
	int						nall_arg;
	char					flags[128];
	long long int			blocks;
	int						error;
	int						width;
	t_ff_size				fm;
}							t_main;

char						*ft_strmode(unsigned int mode);
void						parsing(t_main *st, char **av, int ac);
t_main						*create_main(void);
void						handle_lsflags(t_main *st, t_file **f);
void						reset_main(t_main *st);
void						update_main(t_main *st, int blocks,
								int maxsz, int maxl);
void						update_main2(t_main *st, int user, int group);
void						print_main(t_main *st);
void						push_file(t_file **file, char *name, char type);
void						print_files(t_file *file, int rev, int size);
void						ft_strsort(char **args, int ac);
void						add_file(t_file **file, t_file *new);
t_file						*create_file(char *name, char type);
void						clear_files(t_file **f);
int							read_dir(DIR *dir, char *path,
									t_main *st);
void						fill_str(char *s1, char *s2, int i);
void						fill_data_for(t_file *f, char *path, t_main *st);
void						ft_filesort(t_file **f,
								int (*cmp)(t_file *f1, t_file *f2));
int							time_cmp(struct tm *t1, struct tm *t2);
struct tm					*time_cpy(struct tm *t);
void						print_time(struct tm *t);
void						print_res(t_file *file, int lf, int size);
int							sort_asc_name(t_file *f1, t_file *f2);
int							sort_desc_name(t_file *f1, t_file *f2);
int							sort_ascn_time(t_file *f1, t_file *f2);
int							sort_descn_time(t_file *f1, t_file *f2);
void						print_ls_format(t_main *st, t_file *file,
									int file_flag);
int							print_ff_format(t_main *st, char *f);
t_lst						*create_lst(char *content, int allocate);
void						add_lst(t_lst **lst, t_lst *new);
void						push_lst(t_lst **lst, char *data);
void						print_fullpath(char *s);
void						print_err(char *s);
int							is_lsflag(char c);
void						set_flags(t_main *st, char *arg);
void						set_date(t_file *f, char *s, t_main *st);
void						set_mode(size_t mode, char *buff);

#endif
