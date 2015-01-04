/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjensen <gjensen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/24 16:19:54 by gjensen           #+#    #+#             */
/*   Updated: 2015/01/05 00:09:22 by gjensen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void ft_checkarg(char c)
{
	if (!(c == 'l' || c == 'R' || c == 'a' || c == 'r' || c == 't' || c == '-'
				|| c == '1'))
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
	int				i;
	int				n;

	option = (t_lsoption*)malloc(sizeof(t_lsoption));
	n = ft_parse(option, argv);
	i = n;
	argv = ft_argsort(argv, 2, argc - 1);
	if (argc == i)
	{
		dir = opendir(".");
		ft_startls(dir, option, argv[i]);
	}
	else
	{
		while (i < argc)
		{
			if (!ft_checkelsedir(argv[i]) && i < argc)
				while (!ft_checkelsedir(argv[i]) && i < argc)
				{
					ft_putstr(TITLE);
					ft_putstr(": ");
					perror(argv[i]);
					i++;
				}
			i++;
		}
		i = n;
		while (i < argc)
		{
			if (ft_checkelsedir(argv[i]) == 2)
				while (ft_checkelsedir(argv[i]) == 2 && i < argc)
				{
					ft_startls(NULL, option, argv[i]);
					i++;
				}
			i++;
		}
		i = n;
		while (i < argc)
		{
			if (ft_checkelsedir(argv[i]) == 1)
				while (ft_checkelsedir(argv[i]) == 1 && i < argc)
				{
					if (argc > i + 1)
					{
						ft_putchar('\n');
						ft_putstr(argv[i]);
						ft_putendl(":");
					}
					dir = opendir(argv[i]);
					ft_startls(dir, option, argv[i]);
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
	option->hidden = 0;
	if (ft_checkelsedir(argv[i]) && (argv[i][0] != '-'))
		return (i);
	while (argv[i] && (argv[i][0] == '-'))
	{
		j = 1;
		while (argv[i][j])
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
	t_lsdir			*temp;

	lsdir = NULL;
	if (dir == NULL)
	{
		elem = ft_newlst();
		ft_addlsdir(&lsdir, elem, argv, NULL);
	}
	else
	{
		while ((fichier = readdir(dir)) != NULL)
		{
			elem = ft_newlst();
			ft_addlsdir(&lsdir, elem, fichier->d_name, argv);
		}
	}
	if (option->optiont)
		lsdir = ft_ls_sorttime(lsdir);
	else
		lsdir = ft_ls_sortascii(lsdir);
	align = checkalign(lsdir, option);
	temp = lsdir;
	if (dir && option->optionl)		
	{
		if (!option->optiona)
		{

			while (lsdir->next && (lsdir->name[0] == '.' && lsdir->stat->st_mode))
					lsdir = lsdir->next;
			if (lsdir->name[0] != '.')
			{
				ft_putstr("total ");
				ft_putnbr(align->totalblocks);
				ft_putchar('\n');	
			}
		}
		else
		{
			ft_putstr("total ");
			ft_putnbr(align->totalblocks);
			ft_putchar('\n');
		}
	}
	lsdir = temp;
	if (option->optionr)
	{
		while (lsdir && lsdir->next)
			lsdir = lsdir->next;
	}
	while (lsdir && !option->hidden)
	{
		if (!option->optiona)
		{
			if (lsdir->name[0] != '.' || dir == NULL)
				printls(lsdir, align, option);
		}
		else
			printls(lsdir, align, option);
		if (option->optionr)
			lsdir = lsdir->previous;
		else
			lsdir = lsdir->next;
	}
	if (option->optionrr)
	{
		lsdir = temp;
		while (lsdir)
		{
			if (S_ISDIR(lsdir->stat->st_mode) && ft_strcmp(lsdir->name,".")
					&& ft_strcmp(lsdir->name, ".."))
				ft_start_recursive(lsdir, option);
			lsdir = lsdir->next;
		}
	}
}
