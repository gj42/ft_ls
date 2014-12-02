/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjensen <gjensen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/26 10:02:20 by gjensen           #+#    #+#             */
/*   Updated: 2014/12/02 19:06:51 by gjensen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"


void	ft_addlsdir(t_lsdir **tlsdir, t_lsdir *new, char *name)
{
	t_lsdir	*temp;

	if (*tlsdir == NULL)
		*tlsdir = new;
	else
	{
		temp = *tlsdir;
		while (temp->next)
			temp = temp->next;
		new->previous = temp;
		temp->next = new;
	}
	ft_strcpy(new->name, name);
}
