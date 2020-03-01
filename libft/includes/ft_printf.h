/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcapers <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 22:27:10 by dcapers           #+#    #+#             */
/*   Updated: 2020/02/27 22:27:13 by dcapers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <stdio.h>
# include "libft.h"

typedef struct				s_format
{
	char					flags[128];
	char					modfr;
	char					type;
	int						prec;
	int						min_w;
}							t_format;

typedef struct				s_state
{
	t_format				*fm;
	char					*arg;
	char					fl[61];
	char					sign;
	int						space_len;
	int						zero_len;
	int						right;
	int						arg_len;
	int						mem_alloc;
	va_list					ap;
}							t_state;

int							ft_printf(const char *form, ...);
void						reset_format(t_format *fm);
int							set_format(t_state *st, const char **form);
void						set_argument(t_state *st, char type, char modfr);
void						set_arglen(t_state *st);
void						print_format(t_format *fm);
void						print_state(t_state *st);
t_state						*initialize_state();
void						reset_state(t_state *st, int clear);
void						reset_format(t_format *fm);
void						handle_argument(t_state *st, int *cnt);
int							is_flag(char c);
int							is_type(char c);
int							is_modifier(char c);
void						set_flag(char *flags, char c);
void						set_modifier(t_format *fm, char *mod);
void						set_argument(t_state *st, char type, char modfr);
void						clear_memory(t_state *st);
int							handle_char(t_state *st);
int							handle_di(t_state *st);
int							handle_x(t_state *st);
int							handle_u(t_state *st);
int							handle_o(t_state *st);
int							handle_point(t_state *st);
int							handle_string(t_state *st);
int							handle_float(t_state *st);
void						set_float(t_state *st, long double f);

#endif
