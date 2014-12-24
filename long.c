/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjensen <gjensen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/17 11:58:11 by gjensen           #+#    #+#             */
/*   Updated: 2014/12/24 14:26:54 by gjensen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	showlinks(t_lsdir *lsdir, t_lsalign *align)
{
	int	space;

	space = align->links;
	while (space > ft_intlen(lsdir->stat->st_nlink))
	{
		ft_putchar(' ');
		space--;
	}
	ft_putnbr(lsdir->stat->st_nlink);
	ft_putchar(' ');
}

void	showbytes(t_lsdir *lsdir, t_lsalign *align)
{
	int space;

	space = align->bytes;
	while (space > ft_intlen(lsdir->stat->st_size))
	{
		ft_putchar(' ');
		space--;
	}
	ft_putnbr(lsdir->stat->st_size);
}
