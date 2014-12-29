/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjensen <gjensen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/17 11:58:11 by gjensen           #+#    #+#             */
/*   Updated: 2014/12/29 16:30:09 by gjensen          ###   ########.fr       */
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

void    show_id(t_lsdir *lsdir, t_lsalign *align)
{	
	size_t space;

	space = align->user;
	ft_putstr(lsdir->id->pw_name);
	{
		ft_putchar(' ');
		space--;
	}
	ft_putstr("  ");
	space = align->grp;
	ft_putstr(lsdir->grp->gr_name);
	while (space > ft_strlen(lsdir->grp->gr_name))
	{
		ft_putchar(' ');
		space--;
	}
	ft_putstr("  ");
}


void    showtime(time_t *clock)
{
	char    *str;
	time_t  ct;
	char    *date;
	char    *year;
	char    *hours;

	ct = time(NULL);
	if ((str = ctime(clock)) == NULL)
		return ;
	date = ft_strsub(str, 3, 7);
	ft_putstr(date);
	if (*clock > ct || *clock + 15768000 < ct)
	{
		year = ft_strsub(str, 19, 5);
		ft_putchar(' ');
		ft_putstr(year);
		ft_putchar(' ');
	}
	else
	{
		hours = ft_strsub(str, 10, 6);
		ft_putstr(hours);
		ft_putchar(' ');
	}
}
