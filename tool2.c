/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjensen <gjensen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/24 13:20:22 by gjensen           #+#    #+#             */
/*   Updated: 2014/12/28 19:35:19 by gjensen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void ft_swapstr(char **a, char **b)
{
	char *i;

	i = *b;
	*b = *a;
	*a = i;
}

char	**ft_argsort(char **argv, int start, int end)
{
	int left;
	int right;
	const char *pivot;

	left = start - 1;
	right = end;
	pivot = argv[start];

	if (start >= end)
		return (argv);
	while (left < right)
	{
		while (ft_strcmp(argv[right], pivot) > 0)	
			right--;
		while (ft_strcmp(argv[left], pivot) < 0)
			left++;
		if (left < right)
			ft_swapstr(&argv[left], &argv[right]);
	}
	argv = ft_argsort(argv, start, right);
	argv = ft_argsort(argv, right + 1, end);
	return (argv);
}
