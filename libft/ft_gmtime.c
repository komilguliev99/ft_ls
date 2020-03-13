/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gmtime.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcapers <dcapers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 07:45:13 by dcapers           #+#    #+#             */
/*   Updated: 2020/03/13 17:44:11 by dcapers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_time		*ft_gmtime(time_t sec, int zone)
{
	t_time			*t;
	long long int	days;
	long long int	seconds;

	if (!(t = (t_time *)malloc(sizeof(t_time))))
		return (NULL);
	t->time_zone = zone;
	t->timestemp = (long long int)sec;
	days = t->timestemp / 86400;
	seconds = t->timestemp - days * 86400;
	t->tm.tm_year = days / 365.24;
	days -= t->tm.tm_year * 365.24;
	t->tm.tm_mon = days / 30.44;
	days -= (int)(t->tm.tm_mon * 30.44);
	if (days)
		t->tm.tm_mon++;
	t->tm.tm_mday = days;
	if (seconds)
		t->tm.tm_mday++;
	t->tm.tm_hour = seconds / 3600;
	seconds -= t->tm.tm_hour * 3600;
	t->tm.tm_min = seconds / 60;
	t->tm.tm_sec = seconds - t->tm.tm_min * 60;
	t->tm.tm_hour += t->time_zone;
	return (t);
}
