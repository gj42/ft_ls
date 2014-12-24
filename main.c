/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjensen <gjensen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/24 16:19:54 by gjensen           #+#    #+#             */
/*   Updated: 2014/12/24 16:31:53 by gjensen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void ft_checkarg(char c)
{
	if (!(c == 'l' || c == 'R' || c == 'a' || c == 'r' || c == 't' || c == '-'))
	{
		ft_putstr(TITLE);
		ft_putstr(": ");
		ft_putstr(" illegal option -- ");
		ft_putchar(c);
		ft_putchar('\n');
		ft_putstr("usage: ");
		ft_putstr(TITLE);
		ft_putendl(" [-lRart] [file ...]");
		exit(1);
	}
}

static int	ft_checkelsedir(char *name)
{
	t_stat *file_stat;

	if (!(file_stat = (t_stat*)malloc(sizeof(t_stat))))
		exit(1);
	if (stat(name, file_stat) == -1)
		return (0);
	else if (S_ISDIR(file_stat->st_mode))
		return (1);
	else
		return (2);
	return (0);
}
int			main(int argc, char **argv)
{
	DIR				*dir;
	t_lsoption		*option;
	int			i;
	int			n;

	option = (t_lsoption*)malloc(sizeof(t_lsoption));
	n = ft_parse(option, argv);
	i = n;
	if (argc == i)
	{
		dir = opendir(".");
		ft_startls(dir, option,argv[i]);
	}
	else
	{
		while (argv[i])
		{
		if (ft_checkelsedir(argv[i]) == 2)
			while(ft_checkelsedir(argv[i]) == 2 && argv[i])
			{
				ft_startls(NULL,option,argv[i]);
				i++;
			}
		i++;
		}
		i = n;
		while (argv[i])
		{
		if (ft_checkelsedir(argv[i]) == 1)
			while (ft_checkelsedir(argv[i]) == 1 && argv[i])
			{
				dir = opendir(argv[i]);
				ft_startls(dir,option, argv[i]);
				closedir(dir);
				i++;
			}
		i++;
		}
	}
	return (0);
}



int			ft_parse(t_lsoption *option, char **argv)
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
			if (argv[i][j] == '-')
				return (i + 1);	
			ft_checkarg(argv[i][j]);
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

void		ft_startls(DIR *dir, t_lsoption *option, char *argv)
{
	struct dirent	*fichier;
	t_lsdir			*lsdir;
	t_lsdir			*elem;
	t_lsalign		*align;

	lsdir = NULL;
	if (dir == NULL)
	{
		elem = ft_newlst();
		ft_addlsdir(&lsdir, elem, argv, NULL);
	}
	else
		while ((fichier = readdir(dir)) != NULL)
		{
			elem = ft_newlst();
			ft_addlsdir(&lsdir, elem, fichier->d_name, argv);
		}
	lsdir = ft_ls_sortascii(lsdir);
	align = checkalign(lsdir, option);
	while (lsdir)
	{
		if (!option->optiona)
			if (lsdir->name[0] != '.')
				printls(lsdir, align, option);
		else
			printls(lsdir, align, option);
		lsdir = lsdir->next;
	}
}
