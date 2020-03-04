/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quicksort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcapers <dcapers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 11:53:39 by dcapers           #+#    #+#             */
/*   Updated: 2020/03/03 15:37:31 by dcapers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void			iterate(int *numbers, int *left, int *right, int pivot)
{
	while (*left < *right)
	{
		while ((numbers[*right] >= pivot) && (*left < *right))
			(*right)--;
		if (*left != *right)
		{
			numbers[*left] = numbers[*right];
			(*left)++;
		}
		while ((numbers[*left] <= pivot) && (*left < *right))
			(*left)++;
		if (*left != *right)
		{
			numbers[*right] = numbers[*left];
			(*right)--;
		}
	}
}

void				ft_quicksort(int *numbers, int left, int right)
{
	int		pivot;
	int		l_hold;
	int		r_hold;

	pivot = numbers[left];
	l_hold = left;
	r_hold = right;
	iterate(numbers, &left, &right, pivot);
	numbers[right] = pivot;
	pivot = left;
	left = l_hold;
	right = r_hold;
	if (left < pivot)
		ft_quicksort(numbers, left, pivot - 1);
	if (right > pivot)
		ft_quicksort(numbers, pivot + 1, right);
}
