/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursive.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjensen <gjensen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/29 15:50:10 by gjensen           #+#    #+#             */
/*   Updated: 2015/01/20 00:33:14 by gjensen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_start_recursive(t_lsdir *lsdir, t_lsoption *option)
{
	DIR		*dir;

	if (!option->optiona)
		option->hidden = 1;
	if (lsdir->name[0] != '.' || option->optiona)
	{
		ft_putchar('\n');
		option->hidden = 0;
		ft_putstr(lsdir->path);
		ft_putendl(":");
	}
	dir = opendir(lsdir->path);
	if (!lsdir->next && lsdir)
		free(lsdir->stat);
	if (dir != 0)
		ft_startls(dir, option, lsdir->path, NULL);
	else
	{
		ft_putstr(TITLE);
		ft_putstr(": ");
		perror(lsdir->name);
	}
	if (dir != NULL)
		closedir(dir);
}

void	ls_recursiveon(t_lsdir *lsdir, t_lsoption *option)
{
	if (!option->optionr)
	{
		while (lsdir->previous)
			lsdir = lsdir->previous;
	}
	else
	{
		while (lsdir && lsdir->next)
			lsdir = lsdir->next;
	}
	while (lsdir)
	{
		if (S_ISDIR(lsdir->stat->st_mode) && ft_strcmp(lsdir->name, ".")
				&& ft_strcmp(lsdir->name, ".."))
			ft_start_recursive(lsdir, option);
		if (!option->optionr)
			lsdir = lsdir->next;
		else
			lsdir = lsdir->previous;
	}
}
