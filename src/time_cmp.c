/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_cmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcapers <dcapers@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 14:40:58 by ds107             #+#    #+#             */
/*   Updated: 2020/03/06 15:33:22 by dcapers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

struct tm	*time_cpy(struct tm *t)
{
	struct tm		*time;

	time = NULL;
	if (!(time = (struct tm *)malloc(sizeof(struct tm))))
		exit (0);
	time->tm_year = t->tm_year;
	time->tm_mon = t->tm_mon;
	time->tm_mday = t->tm_mday;
	time->tm_hour = t->tm_hour;
	time->tm_min = t->tm_min;
	time->tm_sec = t->tm_sec;
	return (time);
}

void		print_time(struct tm *t)
{
	ft_printf("Year: %d, Month: %d, Day: %d ",
				t->tm_year, t->tm_mon, t->tm_mday);
	
	ft_printf("Hour: %d, Min: %d, Sec: %d\n",
				t->tm_hour, t->tm_min, t->tm_sec);
}

int		time_cmp(struct tm *t1, struct tm *t2)
{
	if (t1->tm_year == t2->tm_year)
	{
		if (t1->tm_mon == t2->tm_mon)
		{
			if (t1->tm_mday == t2->tm_mday)
			{
				if (t1->tm_hour == t2->tm_hour)
				{
					return (t1->tm_min - t2->tm_min);
				}
				else
					return (t1->tm_hour - t2->tm_hour);
			}
			else
				return (t1->tm_mday - t2->tm_mday);
		}
		else
			return (t1->tm_mon - t2->tm_mon);
	}
	return (t1->tm_year - t2->tm_year);
}