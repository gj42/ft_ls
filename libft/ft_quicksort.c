/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjensen <gjensen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/24 13:20:22 by gjensen           #+#    #+#             */
/*   Updated: 2015/01/11 22:18:48 by gjensen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_quicksort(void *base, int start, int end)
{
	int			left;
	int			right;
	const char	*pivot;

	left = start - 1;
	end = right - 1;
	pivot = base[start];
	if (start >= end)
		return (base);
	while (left < right)
	{
		while (base[right] > pivot)
			right--;
		while (argv[left] < pivot)
			left++;
		if (left < right)
			ft_swap(left, right);
	}
	base = ft_quicksort(base, start, right);
	base = ft_quicksort(base, right + 1, end);
	return (base);
}
