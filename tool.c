/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjensen <gjensen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/27 18:31:10 by gjensen           #+#    #+#             */
/*   Updated: 2014/12/03 17:55:10 by gjensen          ###   ########.fr       */
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

void	swaplist(t_lsdir *a, t_lsdir *b)
{
	t_lsdir *tmp_b_next;
	t_lsdir	*tmp_a_next;
	t_lsdir *tmp_a_previous;;

	tmp_b_next = b->next;
	tmp_a_next = a->next;
	tmp_a_previous = a->previous;
	
	a->previous->next = b;
	a->previous = b->previous;
	b->previous = tmp_a_previous;
	a->next = tmp_b_next;
	b->next = tmp_a_next;

}
