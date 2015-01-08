/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjensen <gjensen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/24 13:20:22 by gjensen           #+#    #+#             */
/*   Updated: 2015/01/09 00:08:11 by gjensen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void ft_swapstr(char **a, char **b)
{
	char *i;

	i = *b;
	*b = *a;
	*a = i;
}

char		**ft_argsort(char **argv, int start, int end)
{
	int			left;
	int			right;
	const char	*pivot;

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

t_lsalign	*checkaligncut2(t_lsalign *align, t_lsdir *lsdir)
{
	int	minormajorl[2];
	int	bytes;

	if (S_ISCHR(lsdir->stat->st_mode) || S_ISBLK(lsdir->stat->st_mode))
	{
		minormajorl[0] = ft_intlen(MINOR(lsdir->stat->st_rdev));
		if (minormajorl[0] > align->minorl)
			align->minorl = minormajorl[0];
		minormajorl[1] = ft_intlen(MAJOR(lsdir->stat->st_rdev));
		if (minormajorl[1] > align->majorl)
			align->majorl = minormajorl[1];
	}
	bytes = ft_intlen(lsdir->stat->st_size);
	if (bytes > align->bytes)
		align->bytes = bytes;
	return (align);
}
