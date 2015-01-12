/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjensen <gjensen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/24 16:19:54 by gjensen           #+#    #+#             */
/*   Updated: 2015/01/12 06:59:13 by gjensen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

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
	int				first;

	option = (t_lsoption*)malloc(sizeof(t_lsoption));
	n = ft_parse(option, argv);
	i = n;
	argv = ft_argsort(argv, 2, argc - 1);
	if (argc == i)
	{
		dir = opendir(".");
		ft_startls(dir, option, argv[i], NULL);
	}
	else
	{
		first = 1;
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
					ft_startls(NULL, option, argv[i], NULL);
					first = 0;
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
					if (argc > n + 1)
					{
						if (!first)
							ft_putchar('\n');
						else
							first = 0;
						ft_putstr(argv[i]);
						ft_putendl(":");
					}
					dir = opendir(argv[i]);
					ft_startls(dir, option, argv[i], NULL);
					closedir(dir);
					i++;
				}
			i++;
		}
	}
	free(option);
	return (0);
}

int			ft_parse(t_lsoption *option, char **argv)
{
	int i;

	i = 1;
	option->optionl = 0;
	option->optionrr = 0;
	option->optiona = 0;
	option->optionr = 0;
	option->optiont = 0;
	option->hidden = 0;
	if (ft_checkelsedir(argv[i]) && (argv[i][0] != '-'))
		return (i);
	i = ft_parsecut(option, argv, i);
	return (i);
}

void		ft_startls(DIR *dir, t_lsoption *option, char *argv,
		t_lsdir *lsdir)
{
	struct dirent	*fichier;
	t_lsdir			*elem;
	t_lsalign		*align;
	t_lsdir			*temp;

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
	lsdir = ls_sort_lsdir(lsdir, option);
	align = checkalign(lsdir, option);
	temp = lsdir;
	ft_startlscut(lsdir, option, align, dir);
	free(align);
	if (option->optionrr)
		ls_recursiveon(temp, option);
}
