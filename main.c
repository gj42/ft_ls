/************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjensen <gjensen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/26 16:21:52 by gjensen           #+#    #+#             */
/*   Updated: 2014/12/02 19:06:48 by gjensen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	main(int argc, char **argv)
{
	DIR				*dir;
	struct dirent	*fichier;
	t_lsdir			*lsdir;
	int				yanael;
	t_lsdir			*elem;
	int		lol;
	t_lsdir			*tmp;

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
//	lm = lsdir;
	yanael = 1;
	while (yanael)
	{
		yanael = 0;
//		lsdir = lm;
//		ft_putendl(lsdir->name);
		while (lsdir)
		{
			ft_putendl(lsdir->name);
			if ((lol = ft_strcmp(lsdir->name, lsdir->next->name)) > 0)
			{
				ft_putendl("====");
				ft_putnbr(lol);
				ft_putendl(lsdir->next->name);
				tmp = (t_lsdir*)malloc(sizeof(t_lsdir));

				tmp = lsdir->next->next;

				swaplist(&lsdir->next->previous,&lsdir->previous);
				swaplist(&lsdir->next, &lsdir);
				lsdir->next = tmp;
				
				
				
				
				ft_putendl(lsdir->next->name);
				ft_putendl(lsdir->name);
				ft_putendl(lsdir->next->name);
				yanael = 1;
			}
			lsdir = lsdir->next;
		}
	}
//	lsdir = lm;
	while (lsdir)
	{
		if (lsdir->name[0] != '.')
			ft_putendl(lsdir->name);
		lsdir = lsdir->next;
	}
	closedir(dir);
	return (0);
}
