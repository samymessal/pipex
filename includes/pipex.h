/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smessal <smessal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 15:54:16 by smessal           #+#    #+#             */
/*   Updated: 2022/11/24 19:05:21 by smessal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
#define PIPEX_H

# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <features.h>
# include <stdlib.h>
# include <fcntl.h>
# include "../utils/libft/libft.h"

/*----------Structures---------*/
typedef struct s_command
{
    char                *command;
    char                **options;
	int					index;
    struct s_command    *next;
}               t_command;

typedef struct s_data
{
	t_command	*com;
	int			ac;
	int			infile;
	int			outfile;
	int			old_fd;
	char		**paths;
	char		*final_path;
}				t_data;

/*----------PARSING-----------*/
char        **get_paths(char **envp);
t_command   *extract_commands(char **av);
char        *command_exists(t_command *com, char **paths);
/*----------UTILS-------------*/
int         ft_count_tab(char **tab);
t_command	*ft_lstnew_com(char *arg, int index);
void        ft_lst_addback_com(t_command **com, t_command *new);
void        fill_list(t_command *com, char *arg, int index);
int			len_list(t_command *com);
/*----------FREE---------------*/
void	free_tab(char **tab);
void	free_com(t_command **com);
void	free_data(t_data *data);

#endif