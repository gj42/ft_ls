/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjensen <gjensen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/27 18:31:10 by gjensen           #+#    #+#             */
/*   Updated: 2014/12/05 20:17:13 by gjensen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_lsdir	*ft_newlst(void)
{
	t_lsdir	*ret;

	if ((ret = (t_lsdir*)malloc(sizeof(t_lsdir))) == NULL)
		return (NULL);
	ret->next = NULL;
	ret->previous = NULL;
	return (ret);
}

void	swaplist(t_lsdir *lsdir, t_lsdir *lsdirnext)
{
	t_lsdir	*tmp;
	t_lsdir *tmp_lsdir;
	t_lsdir	*tmp_lsdirprevious;

	tmp = lsdir->next;
	tmp_lsdir = lsdir;
	tmp_lsdirprevious = lsdir->previous;
	lsdir->previous->next = lsdirnext;
	lsdir->previous = lsdirnext;
	lsdir->next = lsdirnext->next;
	lsdir = tmp;
	lsdir->next = tmp_lsdir;
	lsdir->previous = tmp_lsdirprevious;
}
