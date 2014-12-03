/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjensen <gjensen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/26 10:02:38 by gjensen           #+#    #+#             */
/*   Updated: 2014/12/03 15:31:06 by gjensen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H
# include <dirent.h>
# include <unistd.h>
# include "libft.h"
# include <sys/stat.h>
# include <sys/types.h>
# include <pwd.h>
# include <uuid/uuid.h>
# include <grp.h>
# include <sys/xattr.h>
# include <time.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct	s_lsdir
{
	char			name[256];
	struct s_lsdir	*next; 
	struct s_lsdir  *previous;
}				t_lsdir;

t_lsdir	*ft_newlst(void);
void	swaplist(t_lsdir *a, t_lsdir *b);
void	ft_addlsdir(t_lsdir **tlsdir, t_lsdir *new, char *name);
	











#endif
