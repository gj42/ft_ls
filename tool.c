/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjensen <gjensen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/27 18:31:10 by gjensen           #+#    #+#             */
/*   Updated: 2014/12/27 18:39:23 by gjensen          ###   ########.fr       */
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
	if (option->optionl)
	{
		checkmode(lsdir);
		showlinks(lsdir, align);
		show_id(lsdir, align);
		showbytes(lsdir, align);
		showtime(&lsdir->stat->st_mtime);
	}
	ft_putendl(lsdir->name);
}

static t_lsalign	*checkaligncut(t_lsalign *align, t_lsdir *lsdir)
{
	int links;
	int	user;
	int grp;
	int	bytes;

	links = ft_intlen(lsdir->stat->st_nlink);
	if (links > align->links)
		align->links = links;
	user = ft_strlen(lsdir->id->pw_name);
	if (user > align->user)
		align->user = user;
	grp = ft_strlen(lsdir->grp->gr_name);
	if (grp > align->grp)
		align->grp = grp;
	bytes = ft_intlen(lsdir->stat->st_size);
	if (bytes > align->bytes)
		align->bytes = bytes;
	lsdir = lsdir->next;
	return (align);
}

t_lsalign			*checkalign(t_lsdir *lsdir, t_lsoption *option)
{
	t_lsalign	*align;

	align = (t_lsalign*)malloc(sizeof(t_lsalign));
	align->links = 0;
	align->user = 0;
	align->grp = 0;
	align->bytes = 0;
	while (lsdir)
	{
		if (!option->optiona)
			while (lsdir->name[0] == '.')
				lsdir = lsdir->next;
		align = checkaligncut(align, lsdir);
		lsdir = lsdir->next;
	}
	return (align);
}
