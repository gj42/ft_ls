/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjensen <gjensen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/27 18:31:10 by gjensen           #+#    #+#             */
/*   Updated: 2015/01/02 23:28:52 by gjensen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_lsdir				*ft_newlst(void)
{
	t_lsdir	*ret;

	if ((ret = (t_lsdir*)malloc(sizeof(t_lsdir))) == NULL)
		return (NULL);
	if ((ret->stat = (struct stat*)malloc(sizeof(t_lsdir))) == NULL)
		return (NULL);
	ret->next = NULL;
	ret->previous = NULL;
	return (ret);
}

void				swaplist(t_lsdir *lsdir, t_lsdir *lsdirnext)
{
	t_lsdir	*tmp;
	t_lsdir *tmp_lsdir;
	t_lsdir	*tmp_lsdirprevious;

	tmp = lsdir->next;
	tmp_lsdir = lsdir;
	tmp_lsdirprevious = lsdir->previous;
	if (lsdir->previous != NULL)
		lsdir->previous->next = lsdirnext;
	lsdir->previous = lsdirnext;
	lsdir->next = lsdirnext->next;
	lsdir = tmp;
	lsdir->next = tmp_lsdir;
	lsdir->previous = tmp_lsdirprevious;
}

void				printls(t_lsdir *lsdir,
		t_lsalign *align, t_lsoption *option)
{
	char buf[1024];

	if (option->optionl)
	{
		checkmode(lsdir);
		showlinks(lsdir, align);
		show_id(lsdir, align);
		showbytes(lsdir, align);
		showtime(&lsdir->stat->st_mtime);
		ft_putstr(lsdir->name);
		ft_bzero(buf, sizeof(buf));
		readlink(lsdir->path, buf, sizeof(buf));
		if (buf[0])
		{
			ft_putstr(" -> ");
			ft_putstr(buf);
		}
		ft_putchar('\n');
	}
	else
		ft_putendl(lsdir->name);
}

static t_lsalign	*checkaligncut(t_lsalign *align, t_lsdir *lsdir)
{
	int links;
	int	user;
	int grp;
	int	bytes;
	int minormajorl[2];

	links = ft_intlen(lsdir->stat->st_nlink);
	if (links > align->links)
		align->links = links;
	if (lsdir->id)
		user = ft_strlen(lsdir->id->pw_name);
	else
		user = ft_strlen(ft_itoa(lsdir->stat->st_uid));
	if (user > align->user)
		align->user = user;
	if (lsdir->grp)
		grp = ft_strlen(lsdir->grp->gr_name);
	else
		grp = ft_strlen(ft_itoa(lsdir->stat->st_gid));
	if (grp > align->grp)
		align->grp = grp;
	if (S_ISCHR(lsdir->stat->st_mode) || S_ISBLK(lsdir->stat->st_mode))
	{
		minormajorl[0] = ft_intlen(MINOR(lsdir->stat->st_rdev));
		if (minormajorl[0] > align->minorl)
			align->minorl = minormajorl[0];
		minormajorl[1] = ft_intlen(MAJOR(lsdir->stat->st_rdev));
		if (minormajorl[1] > align->majorl)
			align->majorl =minormajorl[1];
	}
	bytes = ft_intlen(lsdir->stat->st_size);
	if (bytes > align->bytes)
		align->bytes = bytes;
	return (align);
}

t_lsalign			*checkalign(t_lsdir *lsdir, t_lsoption *option)
{
	t_lsalign	*align;

	align = (t_lsalign*)malloc(sizeof(t_lsalign));
	align->totalblocks = 0;
	align->links = 0;
	align->user = 0;
	align->grp = 0;
	align->bytes = 0;
	align->minorl = 0;
	align->majorl = 0;
	align->alignmaj = 0;
	while (lsdir)
	{
		if (!option->optiona)
			while (lsdir && lsdir->name[0] == '.')
				lsdir = lsdir->next;
		if (lsdir)
		{
			align->totalblocks += lsdir->stat->st_blocks;
			align = checkaligncut(align, lsdir);
			lsdir = lsdir->next;
		}
	}
	return (align);
}
