/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argmanage.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjensen <gjensen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/08 23:41:21 by gjensen           #+#    #+#             */
/*   Updated: 2015/01/12 23:20:16 by gjensen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		ft_checkelsedir(char *name)
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

void	ls_show_uk(int argc, char **argv, int i)
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
}

void	ls_show_reg(int argc, char **argv, t_lsoption *option, int i)
{
	while (i < argc)
	{
		if (ft_checkelsedir(argv[i]) == 2)
			while (ft_checkelsedir(argv[i]) == 2 && i < argc)
			{
				ft_startls(NULL, option, argv[i], NULL);
				option->first = 0;
				i++;
			}
		i++;
	}
}

void	ls_show_dir(int argc, char **argv, t_lsoption *option, int i)
{
	int	n;
	DIR	*dir;

	n = i;
	while (i < argc)
	{
		if (ft_checkelsedir(argv[i]) == 1)
			while (ft_checkelsedir(argv[i]) == 1 && i < argc)
			{
				if (argc > n + 1)
				{
					if (!option->first)
						ft_putchar('\n');
					else
						option->first = 0;
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
