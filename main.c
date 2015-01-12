/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjensen <gjensen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/24 16:19:54 by gjensen           #+#    #+#             */
/*   Updated: 2015/01/12 23:17:47 by gjensen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			main(int argc, char **argv)
{
	DIR				*dir;
	t_lsoption		*option;
	int				i;

	option = (t_lsoption*)malloc(sizeof(t_lsoption));
	i = ft_parse(option, argv);
	argv = ft_argsort(argv, 2, argc - 1);
	if (argc == i)
	{
		dir = opendir(".");
		ft_startls(dir, option, argv[i], NULL);
	}
	else
	{
		option->first = 1;
		ls_show_uk(argc, argv, i);
		ls_show_reg(argc, argv, option, i);
		ls_show_dir(argc, argv, option, i);
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
