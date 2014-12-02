/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjensen <gjensen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/27 18:31:10 by gjensen           #+#    #+#             */
/*   Updated: 2014/12/01 19:19:01 by gjensen          ###   ########.fr       */
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

void	swaplist(t_lsdir **a, t_lsdir **b)
{
	t_lsdir **i;

	i = (t_lsdir**)malloc(sizeof(t_lsdir));
	*i = *b;
	*b = *a;
	*a = *i;
}
