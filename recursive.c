/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursive.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjensen <gjensen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/29 15:50:10 by gjensen           #+#    #+#             */
/*   Updated: 2015/01/05 00:09:15 by gjensen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_start_recursive(t_lsdir *lsdir, t_lsoption *option)
{
	DIR		*dir;

	if (!option->hidden)
		ft_putchar('\n');
	if (!option->optiona)
		option->hidden = 1;
	if (lsdir->name[0] != '.' || option->optiona)
	{
		option->hidden = 0;
		ft_putstr(lsdir->path);
		ft_putendl(":");
	}
	dir = opendir(lsdir->path);
	ft_startls(dir, option, lsdir->path);
}
