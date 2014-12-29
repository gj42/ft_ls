/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjensen <gjensen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/26 10:02:20 by gjensen           #+#    #+#             */
/*   Updated: 2014/12/29 18:06:59 by gjensen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_addlsdir(t_lsdir **tlsdir, t_lsdir *new, char *name, char *path)
{
	t_lsdir	*temp;
	char	*pathfile;

	if (*tlsdir == NULL)
		*tlsdir = new;
	else
	{
		temp = *tlsdir;
		while (temp->next)
			temp = temp->next;
		new->previous = temp;
		temp->next = new;
	}
	ft_strcpy(new->name, name);
	if (path)
	{
		pathfile = ft_strjoin(path, ft_strjoin("/", name));
		new->path = pathfile;
		lstat(pathfile, new->stat);
	}
	else
	{
		lstat(name, new->stat);
		new->path = ft_strjoin("./", name);
	}
	new->id = getpwuid(new->stat->st_uid);
	new->grp = getgrgid(new->stat->st_gid);
}

t_lsdir	*ft_ls_sortascii(t_lsdir *lsdir)
{
	t_lsdir	*tmp;
	int		exchange;

	exchange = 1;
	tmp = lsdir;
	while (exchange)
	{
		exchange = 0;
		lsdir = tmp;
		while (lsdir && lsdir->next)
		{
			if (ft_strcmp(lsdir->name, lsdir->next->name) > 0)
			{
				swaplist(lsdir, lsdir->next);
				if (lsdir->next != NULL)
					lsdir->next->previous = lsdir;
				exchange = 1;
			}
			lsdir = lsdir->next;
		}
	}
	lsdir = tmp;
	while (lsdir->previous)
		lsdir = lsdir->previous;
	return (lsdir);
}

void	checkmode(t_lsdir *lsdir)
{
	if (S_ISDIR(lsdir->stat->st_mode))
		ft_putchar('d');
	else if (S_ISLNK(lsdir->stat->st_mode))
		ft_putchar('l');
	else if (S_ISCHR(lsdir->stat->st_mode))
		ft_putchar('c');
	else if (S_ISBLK(lsdir->stat->st_mode))
		ft_putchar('b');
	else if (S_ISFIFO(lsdir->stat->st_mode))
		ft_putchar('p');
	else if (S_ISSOCK(lsdir->stat->st_mode))
		ft_putchar('s');
	else
		ft_putchar('-');
	(lsdir->stat->st_mode & S_IRUSR) ? ft_putchar('r') : ft_putchar('-');
	(lsdir->stat->st_mode & S_IWUSR) ? ft_putchar('w') : ft_putchar('-');
	(lsdir->stat->st_mode & S_IXUSR) ? ft_putchar('x') : ft_putchar('-');
	(lsdir->stat->st_mode & S_IRGRP) ? ft_putchar('r') : ft_putchar('-');
	(lsdir->stat->st_mode & S_IWGRP) ? ft_putchar('w') : ft_putchar('-');
	(lsdir->stat->st_mode & S_IXGRP) ? ft_putchar('x') : ft_putchar('-');
	(lsdir->stat->st_mode & S_IROTH) ? ft_putchar('r') : ft_putchar('-');
	(lsdir->stat->st_mode & S_IWOTH) ? ft_putchar('w') : ft_putchar('-');
	(lsdir->stat->st_mode & S_IXOTH) ? ft_putchar('x') : ft_putchar('-');
	ft_putstr("  ");
}

t_lsdir	*ft_ls_sorttime(t_lsdir *lsdir)
{
	t_lsdir	*tmp;
	int		exchange;

	exchange = 1;
	tmp = lsdir;
	while (exchange)
	{
		exchange = 0;
		lsdir = tmp;
		while (lsdir && lsdir->next)
		{	
			if (lsdir->stat->st_mtimespec.tv_sec < lsdir->next->stat->st_mtimespec.tv_sec)
			{
				swaplist(lsdir, lsdir->next);
				if (lsdir->next != NULL)
					lsdir->next->previous = lsdir;
				exchange = 1;
			}
			lsdir = lsdir->next;
		}
	}
	lsdir = tmp;
	while (lsdir->previous)
		lsdir = lsdir->previous;
	return (lsdir);
}
