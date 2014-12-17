/************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjensen <gjensen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/26 16:21:52 by gjensen           #+#    #+#             */
/*   Updated: 2014/12/17 19:12:52 by gjensen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	main(int argc, char **argv)
{
	DIR				*dir;
	t_lsoption		*option;
	int				i;

	option = (t_lsoption*)malloc(sizeof(t_lsoption));
	i = ft_parse(option, argv);
	if (argc == i)
	{
		dir = opendir(".");
		ft_startls(dir, option,argv[i]);
	}
	else
		while (argv[i])
		{
			dir = opendir(argv[i]);
			ft_startls(dir,option, argv[i]);
			closedir(dir);
			i++;
		}
	return (0);
}



int	ft_parse(t_lsoption *option, char **argv)
{
	int i;
	int j;

	i = 1;
	option->optionl = 0;
	option->optionrr = 0;
	option->optiona = 0;
	option->optionr = 0;
	option->optiont = 0;
	while (argv[i] && (argv[i][0] == '-'))
	{
		j = 1;
		while(argv[i][j])
		{
			//			ft_checkarg(argv[i][j]);
			if (argv[i][j] == 'l')
				option->optionl = 1;
			if (argv[i][j] == 'R')
				option->optionrr = 1;
			if (argv[i][j] == 'a')
				option->optiona = 1;
			if (argv[i][j] == 'r')
				option->optionr = 1;
			if (argv[i][j] == 't')
				option->optiont = 1;
			j++;
		}
		i++;
	}
	return (i);
}

void	ft_startls(DIR *dir, t_lsoption *option, char *argv)
{
	struct dirent	*fichier;
	t_lsdir			*lsdir;
	t_lsdir			*elem;
	t_lsalign		*align;
	
	while ((fichier = readdir(dir)) != NULL)
	{
		elem = ft_newlst();
		ft_addlsdir(&lsdir, elem, fichier->d_name, argv);
	}
	lsdir = ft_ls_sortascii(lsdir);
	align = checkalign(lsdir);
	while (lsdir)
	{
		if (!option->optiona)
		{
			if (lsdir->name[0] != '.')
				printls(lsdir, align, option);
		}
		else
			printls(lsdir, align, option);
		lsdir = lsdir->next;
	}
}
