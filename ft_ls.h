/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjensen <gjensen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/26 10:02:38 by gjensen           #+#    #+#             */
/*   Updated: 2015/01/09 00:04:40 by gjensen          ###   ########.fr       */
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

# define TITLE "ft_ls"
# define MAJOR(x) ((int32_t)(((u_int32_t)(x) >> 24) & 0xff))
# define MINOR(x) ((int32_t)((x) & 0xffffff))

typedef struct stat	t_stat;

typedef struct		s_lsdir
{
	char			name[256];
	char			*path;
	char			*idn;
	char			*gn;
	struct stat		*stat;
	struct s_lsdir	*next;
	struct s_lsdir  *previous;
}				t_lsdir;

typedef struct		s_lsalign
{
	int	totalblocks;
	int	links;
	int	user;
	int	grp;
	int	bytes;
	int minorl;
	int majorl;
	int alignmaj;
}					t_lsalign;

typedef	struct		s_lsoption
{
	int	hidden;
	int	optionl;
	int	optiona;
	int	optionr;
	int	optionrr;
	int optiont;
}					t_lsoption;


t_lsdir				*ft_newlst(void);
void				swaplist(t_lsdir *lsdir, t_lsdir *lsdirnext);
void				ft_addlsdir(t_lsdir **tlsdir, t_lsdir *new, char *name, char *path);
t_lsdir				*ft_ls_sortascii(t_lsdir *lsdir);
void				checkmode(t_lsdir *lsdir);
void				show_id(t_lsdir *lsdir, t_lsalign *align);
void				printls(t_lsdir *lsdir, t_lsalign *align, t_lsoption *option);
void				showtime(time_t *clock);
t_lsalign			*checkalign(t_lsdir *lsdir, t_lsoption *option);
void				showlinks(t_lsdir *lsdir, t_lsalign *align);
void				showbytes(t_lsdir *lsdir, t_lsalign *align);
int 				ft_parse(t_lsoption *option, char **argv);
void				ft_startls(DIR *dir, t_lsoption *option, char *argv);
char				**ft_argsort(char **argv, int start, int end);
t_lsdir				*ft_ls_sorttime(t_lsdir *lsdir);
void				ft_start_recursive(t_lsdir *lsdir, t_lsoption *option);
t_lsalign			*checkaligncut2(t_lsalign *align, t_lsdir *lsdir);









#endif
