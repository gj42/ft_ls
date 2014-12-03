/************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjensen <gjensen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/26 16:21:52 by gjensen           #+#    #+#             */
/*   Updated: 2014/12/03 17:54:10 by gjensen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	main(int argc, char **argv)
{
	DIR				*dir;
	struct dirent	*fichier;
	t_lsdir			*lsdir;
	int				exchange;
	t_lsdir			*elem;
	t_lsdir			*tmp;
//	t_lsdir			*temp;

	lsdir = NULL;
	if (argc == 1)
		dir = opendir(".");
	else
		dir = opendir(argv[1]);
	if (dir == NULL)
		return (-1);
	while ((fichier = readdir(dir)) != NULL)
	{
		elem = ft_newlst();
		ft_addlsdir(&lsdir, elem, fichier->d_name);
	}
	exchange = 1;
	tmp = lsdir;
	while (exchange)
	{
		exchange = 0;
		lsdir = tmp;
//		ft_putendl(lsdir->name);
		while (lsdir)
		{
			ft_putendl(lsdir->name);
			if (ft_strcmp(lsdir->name, lsdir->next->name) > 0)
			{
				swaplist(lsdir, lsdir->next);
				

				exchange = 1;
			}
			if (lsdir->next)
				lsdir = lsdir->next;
		}
	}
	lsdir = tmp;
	while (lsdir)
	{
		if (lsdir->name[0] != '.')
			ft_putendl(lsdir->name);
		lsdir = lsdir->next;
	}
	closedir(dir);
	return (0);
}